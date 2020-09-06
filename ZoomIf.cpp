// ZOOM SYSTEM MESSAGES
#include "Arduino.h"
#include "Array.h"
#include "MidiOutIf.h"
#include "MultistompController.h"
#include "ZoomIf.h"
#include "ZoomMsg.h"

static Stream           *ZoomIf::Com;
static byte             ZoomIf::Channel;
static bool             ZoomIf::TunerState = false;
static byte             ZoomIf::CurrentPatch = CONTROL_BYTE;
static byte             ZoomIf::CurrentFocus = CONTROL_BYTE;
static byte             ZoomIf::CurrentEffects = 0;
static _zoomPatchType   ZoomIf::Buffer;

#if ZOOM_SRAM_MEM
  static _zoomPatchType ZoomIf::PatchMem[ZOOM_SRAM_PATCHES];
  static bool           ZoomIf::PatchModified[ZOOM_SRAM_PATCHES];
  static byte           ZoomIf::EffectStates[ZOOM_SRAM_PATCHES];
#endif

static byte             PatchFxOffsets[ZOOM_EFF_NO] =
                                            {ZOOM_MSG_OFFSET_EFF_ON_1,
                                             ZOOM_MSG_OFFSET_EFF_ON_2,
                                             ZOOM_MSG_OFFSET_EFF_ON_3,
                                             ZOOM_MSG_OFFSET_EFF_ON_4,
                                             ZOOM_MSG_OFFSET_EFF_ON_5,
                                             ZOOM_MSG_OFFSET_EFF_ON_6};


void ZoomIf::Init(Stream *Com, byte Channel) {
  ZoomIf::Com = Com;
  ZoomIf::Channel = Channel;
  
  delay(ZOOM_INI_DELAY);
  
  bool IniDone = false;
  while (!IniDone)
  {
    #if DEBUG
      Serial.println("Init...");
    #endif
    
    IniDone = ZoomIf::IdentityRequest();
    if (IniDone) break;
    
    delay(ZOOM_INI_WAIT);
  }
  
  ZoomIf::ParamEnable();
  ZoomIf::CachePatches();
  ZoomIf::Patch(0);
  
  #if ZOOM_SRAM_MEM
    ARRAY_FILL(PatchModified, ZOOM_SRAM_PATCHES, false);
  #endif
  
  #if DEBUG
    Serial.println("Init done.");
  #endif
}


bool ZoomIf::IdentityRequest() {
  _zoomIdType IdBuffer;
  
  byte Msg[] = ZOOM_MSG_IDENTITY_REQUEST;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
  Com->readBytes(IdBuffer.data, ZOOM_IDENTITY_LENGTH);  // Receive patch data
  while(Com->read() >= 0);                              // Flush input buffer
  
  _zoomIdType IdReturn = ZOOM_MSG_IDENTITY_RETURN;      // Reference message
  
  return (IdBuffer == IdReturn);
}


void ZoomIf::Tuner(bool State) {
  byte Value = State ? 0x7F : 0x00;
  
  if (State) ParamDisable();
  
  MidiOutIf::CC(Com, Channel, 0x4A, Value);
  
  if (!State) ParamEnable();
  
  TunerState = State;
}


void ZoomIf::ParamEnable() {
  byte Msg[] = ZOOM_MSG_PRM_ENA;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}


void ZoomIf::ParamDisable() {
  byte Msg[] = ZOOM_MSG_PRM_DEA;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}


void ZoomIf::ParamEdit(byte Slot, byte Param, int Value) {
  byte Msg[] = ZOOM_MSG_PRM_EDIT;
  
  Msg[5] = Slot - 1;
  Msg[6] = Param + 0x01;
  Msg[7] = Value & 0x7F;      // 7 bit LSB
  Msg[8] = (Value>>7) & 0x7F; // 7 bit MSB
  
  Com->write(Msg, ARRAY_SIZE(Msg));
  
  ZoomIf::SetModified(CurrentPatch);
}


void ZoomIf::SwitchOn(byte PN, byte Slot) {
  byte Msg[] = ZOOM_MSG_EFF_ON;
  
  if (Slot > 3) return;
  
  Msg[5] = Slot - 1;
  
  ZoomIf::Patch(PN);
  Com->write(Msg, ARRAY_SIZE(Msg));
  
  ZoomIf::SetModified(CurrentPatch);
  
  BIT_SET(CurrentEffects, Slot - 1);
}


void ZoomIf::SwitchOff(byte PN, byte Slot) {
  byte Msg[] = ZOOM_MSG_EFF_OFF;
  
  if (Slot > 3) return;
  
  Msg[5] = Slot - 1;
  
  ZoomIf::Patch(PN);
  Com->write(Msg, ARRAY_SIZE(Msg));
  
  ZoomIf::SetModified(CurrentPatch);
  
  BIT_CLR(CurrentEffects, Slot - 1);
}


void ZoomIf::OnManualSwitch(byte Slot, bool State) {
  if (State)
    BIT_SET(CurrentEffects, Slot - 1);
  else
    BIT_CLR(CurrentEffects, Slot - 1);
}


_zoomPatchType ZoomIf::RequestPatch(byte PN) {
  byte Msg[] = ZOOM_MSG_PATCH_REQUEST;
  
  ARRAY_FILL(Buffer.data, ZOOM_PATCH_LENGTH, 0x00); // Reset buffer
  
  ZoomIf::Patch(PN);                         // Select patch
  
  Com->write(Msg, ARRAY_SIZE(Msg));                 // Send patch request
  Com->readBytes(Buffer.data, ZOOM_PATCH_LENGTH);   // Receive patch data
  while(Com->read() >= 0);                          // Flush input buffer
  
  return Buffer;
}


void ZoomIf::MemStore(byte PN) {
  #if ZOOM_SRAM_MEM
    if (PN < ZOOM_SRAM_PATCHES)
      PatchMem[PN] = Buffer;
  #endif
}


void ZoomIf::CachePatches() {
  #if ZOOM_SRAM_MEM
    for (int n = 0; n < ZOOM_SRAM_PATCHES; n++)
    {
      ZoomIf::Buffer = ZoomIf::RequestPatch(n);
      ZoomIf::GetPatchEffects(n);
      ZoomIf::MemStore(n);
      
      #if DEBUG
        Serial.write(ZoomIf::Buffer.data, ZOOM_PATCH_LENGTH);
      #endif
    }
  #endif
}


void ZoomIf::UpdatePatches() {
  byte PreviousPatch = CurrentPatch;
  
  #if ZOOM_SRAM_MEM
    for (int n = 0; n < ZOOM_SRAM_PATCHES; n++)
    {
      ZoomIf::Buffer = ZoomIf::RequestPatch(n);
      ZoomIf::GetPatchEffects(n);
      ZoomIf::MemStore(n);
      
      #if DEBUG
        Serial.write(ZoomIf::Buffer.data, ZOOM_PATCH_LENGTH);
      #endif
    }
    
    ZoomIf::Patch(PreviousPatch);
  #endif
}


void ZoomIf::RestorePatch(byte PN) {
  #if ZOOM_SRAM_MEM
    if (PN < ZOOM_SRAM_PATCHES)
    {
      if (PatchModified[PN])
      {
        #if DEBUG
          Serial.print("Restoring... ");
          Serial.println(PN);
        #endif
        
        Buffer = ZoomIf::PatchMem[PN];
        Com->write(Buffer.data, ZOOM_PATCH_LENGTH);
        
        PatchModified[PN] = false;
        
        CurrentFocus = CONTROL_BYTE;
      }
    }
  #endif
}


void ZoomIf::SetModified(byte PN) {
  #if ZOOM_SRAM_MEM
    if (PN < ZOOM_SRAM_PATCHES) PatchModified[PN] = true;
  #endif
}


byte ZoomIf::GetPatchEffects(byte PN) {
  byte State = 0;
  // ZoomIf::Patch(PN); // Select patch

  Serial.print("GetPatchEffects PN ");
  Serial.println(PN);

  // Prepare effect states
  #if ZOOM_SRAM_MEM
    if (PN < ZOOM_SRAM_PATCHES)
    {      
      for (int i = 0; i < ZOOM_EFF_NO; i++)
      {
        byte TypeByte = Buffer.data[PatchFxOffsets[i]];

        if BIT_CHECK(TypeByte, ZOOM_EFF_ON_BIT)
        {
          BIT_SET(State, i);

          #if DEBUG
            Serial.print("Effect ");
            Serial.print(i + 1);
            Serial.println(" is on.");
          #endif
        }
        else
        {
          #if DEBUG
            Serial.print("Effect ");
            Serial.print(i + 1);
            Serial.println(" is off.");
          #endif
        }
      }

      ZoomIf::EffectStates[PN] = State;
    }
  #endif

  return State;
}


void ZoomIf::SetPatchEffects(byte PN, byte Mask) {
  bool State[ZOOM_EFF_NO];
  
  ZoomIf::Patch(PN); // Select patch
  
  // Prepare effect states
  #if ZOOM_SRAM_MEM
    if (PN < ZOOM_SRAM_PATCHES)
    {
      Buffer = ZoomIf::PatchMem[PN];
      
      #if DEBUG
        Serial.write(Buffer.data, ZOOM_PATCH_LENGTH);
        Serial.println("");
      #endif
      
      for (int i = 0; i < ZOOM_EFF_NO; i++)
      {
        byte TypeByte = Buffer.data[PatchFxOffsets[i]];
        
        if (BIT_CHECK(Mask, i))
          BIT_SET(TypeByte, ZOOM_EFF_ON_BIT);
        else
          BIT_CLR(TypeByte, ZOOM_EFF_ON_BIT);
        
        Buffer.data[PatchFxOffsets[i]] = TypeByte;
      }
      
      if (!(CurrentFocus == CONTROL_BYTE)) 
        ZoomIf::FocusEffect(CurrentFocus);
      
      #if DEBUG
        Serial.write(Buffer.data, ZOOM_PATCH_LENGTH);
        Serial.println("");
      #endif
      
      // Write patch data
      Com->write(Buffer.data, ZOOM_PATCH_LENGTH);
      
      CurrentEffects = Mask;
      
      ZoomIf::SetModified(CurrentPatch);
    }
  #endif
}


void ZoomIf::FocusEffect(byte Effect) {
  byte Focus = FocusTable[Effect];
  byte b0, b1, b2;
  
  b0 = Buffer.data[ZOOM_EFF_FOCUS_BIT_0_OFFSET];
  b1 = Buffer.data[ZOOM_EFF_FOCUS_BIT_1_OFFSET];
  b2 = Buffer.data[ZOOM_EFF_FOCUS_BIT_2_OFFSET];
  
  if BIT_CHECK(Focus, 0)
    BIT_SET(b0, ZOOM_EFF_FOCUS_BIT_0_INDEX);
  else
    BIT_CLR(b0, ZOOM_EFF_FOCUS_BIT_0_INDEX);
    
  if BIT_CHECK(Focus, 1)
    BIT_SET(b1, ZOOM_EFF_FOCUS_BIT_1_INDEX);
  else
    BIT_CLR(b1, ZOOM_EFF_FOCUS_BIT_1_INDEX);
    
  if BIT_CHECK(Focus, 2)
    BIT_SET(b2, ZOOM_EFF_FOCUS_BIT_2_INDEX);
  else
    BIT_CLR(b2, ZOOM_EFF_FOCUS_BIT_2_INDEX);
  
  Buffer.data[ZOOM_EFF_FOCUS_BIT_0_OFFSET] = b0;
  Buffer.data[ZOOM_EFF_FOCUS_BIT_1_OFFSET] = b1;
  Buffer.data[ZOOM_EFF_FOCUS_BIT_2_OFFSET] = b2;
}


void ZoomIf::Patch(byte PN) {
  if (PN != CurrentPatch)
  {
    MidiOutIf::PC(Com, Channel, PN);
    CurrentPatch = PN;
    
    #if ZOOM_SRAM_MEM
      if (PN < ZOOM_SRAM_PATCHES)
        CurrentEffects = EffectStates[PN];
    #endif
  }
}


void ZoomIf::Patch(byte PN, bool Restore) {
  if (PN != CurrentPatch)
  {
    if (Restore) ZoomIf::RestorePatch(CurrentPatch);
    
    MidiOutIf::PC(Com, Channel, PN);
    CurrentPatch = PN;
    
    #if ZOOM_SRAM_MEM
      if (PN < ZOOM_SRAM_PATCHES)
        CurrentEffects = EffectStates[PN];
    #endif
  }
}


void ZoomIf::Patch(byte PN, bool Restore, bool Force) {
  if ((PN != CurrentPatch) || (Force))
  {
    if (Restore) ZoomIf::RestorePatch(CurrentPatch);
    
    MidiOutIf::PC(Com, Channel, PN);
    CurrentPatch = PN;
    
    #if ZOOM_SRAM_MEM
      if (PN < ZOOM_SRAM_PATCHES)
        CurrentEffects = EffectStates[PN];
    #endif
  }
}


byte ZoomIf::StateMask(_zoomStateVector States) {
  byte Out = 0;

  for (int i = 0; i < ZOOM_EFF_NO; i++)
  {
    if (States[i])
      BIT_SET(Out, i);
  }

  return Out;
}


_zoomStateVector ZoomIf::StateVector(byte States) {
  _zoomStateVector Out;

  ARRAY_FILL(Out.data, ZOOM_EFF_NO, false);

  for (int i = 0; i < ZOOM_EFF_NO; i++)
  {
    if (BIT_CHECK(States, i))
      Out[i] = true; 
  }

  return Out;
}


void ZoomIf::LogMem() {
  for (int n = 0; n < ZOOM_SRAM_PATCHES; n++)
  {
    _zoomPatchType PatchTmp = ZoomIf::PatchMem[n];    
    Serial.write(PatchTmp.data, ZOOM_PATCH_LENGTH);
    Serial.println("");
  }
}


void ZoomIf::LogBuffer() {
  Serial.write(Buffer.data, ZOOM_PATCH_LENGTH);
  Serial.println("");
}

