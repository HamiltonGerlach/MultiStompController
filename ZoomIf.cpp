// ZOOM SYSTEM MESSAGES
#include "Arduino.h"
#include "Array.h"
#include "MidiOutIf.h"
#include "MultistompController.h"
#include "PatchMap.h"
#include "ParamMap.h"
#include "State.h"
#include "Timer.h"
#include "ZoomIf.h"
#include "ZoomMsg.h"

static Stream           *ZoomIf::Com;
static byte             ZoomIf::Channel;
static bool             ZoomIf::TunerState = false;
static byte             ZoomIf::CurrentPatch = CONTROL_BYTE;
static byte             ZoomIf::CurrentFocus = CONTROL_BYTE;
static byte             ZoomIf::CurrentEffects = 0;
static _zoomPatchType   ZoomIf::Buffer;

#if EEPROM_ENABLED
  #include "FlashMem.h"
  #include "MemMap.h"
#else
  static _zoomPatchType ZoomIf::PatchMem[SRAM_PATCH_NUM];
#endif

static bool             ZoomIf::PatchModified[MEM_PATCH_NUM];
static byte             ZoomIf::EffectStates[MEM_PATCH_NUM];


void ZoomIf::Init(Stream *Com, byte Channel) {
  #if EEPROM_ENABLED
    FlashMem::Init();
  #endif
  
  ZoomIf::Com = Com;
  ZoomIf::Channel = Channel;
  
  delay(ZOOM_INI_DELAY);
  
  bool IniDone = false;
  while (!IniDone)
  {
    #if DEBUG
      Serial.println(F("Init..."));
    #endif
    
    IniDone = ZoomIf::IdentityRequest();
    if (IniDone) break;
    
    delay(ZOOM_INI_WAIT);
  }
  
  ZoomIf::ParamEnable();
  ZoomIf::CachePatches();
  ZoomIf::Patch(0);
  
  #if DEBUG
    Serial.println(F("Init done."));
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


void ZoomIf::RequestPatch(byte PN) {
  byte Msg[] = ZOOM_MSG_PATCH_REQUEST;
  
  ARRAY_FILL(Buffer.data, ZOOM_PATCH_LENGTH, 0x00); // Reset buffer
  
  ZoomIf::Patch(PN);                         // Select patch
  
  Com->write(Msg, ARRAY_SIZE(Msg));                 // Send patch request
  Com->readBytes(Buffer.data, ZOOM_PATCH_LENGTH);   // Receive patch data
  while(Com->read() >= 0);                          // Flush input buffer
}


void ZoomIf::MemStore(byte PN) {
  #if EEPROM_ENABLED
    if (PN < EEPROM_PATCH_NUM) {
      unsigned int Address = FlashPatchAddress(PN);
      
      #if DEBUG
        Serial.print("STORE PATCH "); Serial.print(PN);
        Serial.print(" AT ADDRESS "); Serial.print(Address);
      #endif
      
      ZoomIf::FlashWrite(Address);
    }
  #else
    if (PN < SRAM_PATCH_NUM)
      PatchMem[PN] = Buffer;
  #endif
}


void ZoomIf::CachePatches() {  
  for (int n = 0; n < MEM_PATCH_NUM; n++)
  {
    ZoomIf::RequestPatch(n);
    ZoomIf::GetPatchEffects(n);
    ZoomIf::MemStore(n);
    
    #if DEBUG
      Serial.write(ZoomIf::Buffer.data, ZOOM_PATCH_LENGTH);
    #endif
  }
  
  ARRAY_FILL(PatchModified, MEM_PATCH_NUM, false);
}


void ZoomIf::UpdatePatches() {
  byte PreviousPatch = CurrentPatch;
  
  for (int n = 0; n < MEM_PATCH_NUM; n++)
  {
    ZoomIf::RequestPatch(n);
    ZoomIf::GetPatchEffects(n);
    ZoomIf::MemStore(n);
    
    #if DEBUG
      Serial.write(ZoomIf::Buffer.data, ZOOM_PATCH_LENGTH);
    #endif
  }
  
  ZoomIf::Patch(PreviousPatch);
  
  ARRAY_FILL(PatchModified, MEM_PATCH_NUM, false);
}


void ZoomIf::UpdateCurrentPatch() {
  if (CurrentPatch < MEM_PATCH_NUM)
  {
    ZoomIf::RequestPatch(CurrentPatch);
    ZoomIf::GetPatchEffects(CurrentPatch);
    ZoomIf::MemStore(CurrentPatch);
    
    #if DEBUG
      Serial.print("Updating patch ");
      Serial.println(CurrentPatch);
      Serial.write(ZoomIf::Buffer.data, ZOOM_PATCH_LENGTH);
    #endif
    
    PatchModified[CurrentPatch] = false;
  }
}


void ZoomIf::RestorePatch(byte PN) {
  if (PN < MEM_PATCH_NUM)
  {
    if (PatchModified[PN])
    {
      #if DEBUG
        Serial.print(F("Restoring... "));
        Serial.println(PN);
      #endif
      
      ZoomIf::ReadPatch(PN);
      ZoomIf::SendPatch();
      
      PatchModified[PN] = false;
      
      CurrentFocus = CONTROL_BYTE;
    }
  }
}


void ZoomIf::SetModified(byte PN) {
  if (PN < MEM_PATCH_NUM) PatchModified[PN] = true;
}


byte ZoomIf::GetPatchEffects(byte PN) {
  byte State = 0;
  // ZoomIf::Patch(PN); // Select patch
  
  #if DEBUG
    Serial.print(F("GetPatchEffects PN "));
    Serial.println(PN);
  #endif
  
  // Prepare effect states
  if (PN < MEM_PATCH_NUM)
  {      
    for (int i = 0; i < ZOOM_EFF_NO; i++)
    {
      byte TypeByte = Buffer.data[PatchFxOffsets[i]];

      if BIT_CHECK(TypeByte, ZOOM_EFF_ON_BIT)
      {
        BIT_SET(State, i);

        #if DEBUG
          Serial.print(F("Effect "));
          Serial.print(i + 1);
          Serial.println(F(" is on."));
        #endif
      }
      else
      {
        #if DEBUG
          Serial.print(F("Effect "));
          Serial.print(i + 1);
          Serial.println(F(" is off."));
        #endif
      }
    }

    ZoomIf::EffectStates[PN] = State;
  }

  return State;
}


void ZoomIf::SetPatchEffects(byte PN, byte Mask, bool Send = false) {
  bool State[ZOOM_EFF_NO];
  
  ZoomIf::Patch(PN); // Select patch
  
  // Prepare effect states
  if (PN < MEM_PATCH_NUM)
  {
    ZoomIf::ReadPatch(PN);
    
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
    if (Send) SendPatch();
    
    CurrentEffects = Mask;
    
    ZoomIf::SetModified(CurrentPatch);
  }
}


void ZoomIf::FocusEffect(byte Effect) {
  byte Focus = FocusTable[Effect];
  byte b0, b1, b2;
  
  b0 = Buffer.data[ZOOM_PATCH_OFFSET_FOCUS_BIT_0];
  b1 = Buffer.data[ZOOM_PATCH_OFFSET_FOCUS_BIT_1];
  b2 = Buffer.data[ZOOM_PATCH_OFFSET_FOCUS_BIT_2];
  
  if BIT_CHECK(Focus, 0)
    BIT_SET(b0, ZOOM_PATCH_INDEX_FOCUS_BIT_0);
  else
    BIT_CLR(b0, ZOOM_PATCH_INDEX_FOCUS_BIT_0);
    
  if BIT_CHECK(Focus, 1)
    BIT_SET(b1, ZOOM_PATCH_INDEX_FOCUS_BIT_1);
  else
    BIT_CLR(b1, ZOOM_PATCH_INDEX_FOCUS_BIT_1);
    
  if BIT_CHECK(Focus, 2)
    BIT_SET(b2, ZOOM_PATCH_INDEX_FOCUS_BIT_2);
  else
    BIT_CLR(b2, ZOOM_PATCH_INDEX_FOCUS_BIT_2);
  
  Buffer.data[ZOOM_PATCH_OFFSET_FOCUS_BIT_0] = b0;
  Buffer.data[ZOOM_PATCH_OFFSET_FOCUS_BIT_1] = b1;
  Buffer.data[ZOOM_PATCH_OFFSET_FOCUS_BIT_2] = b2;
}


void ZoomIf::Patch(byte PN, bool Restore = false, bool Force = false) {
  if ((PN != CurrentPatch) || (Force))
  {
    if (Restore) ZoomIf::RestorePatch(CurrentPatch);
    
    MidiOutIf::PC(Com, Channel, PN);
    CurrentPatch = PN;
    
    if (PN < MEM_PATCH_NUM)
      CurrentEffects = EffectStates[PN];
  }
}


void ZoomIf::LogMem() {
  #if DEBUG
    for (int n = 0; n < MEM_PATCH_NUM; n++)
    {
      ZoomIf::ReadPatch(n);
      Serial.write(Buffer.data, ZOOM_PATCH_LENGTH);
      Serial.println("");
    }
  #endif
}


void ZoomIf::LogBuffer() {
  #if DEBUG
    Serial.write(Buffer.data, ZOOM_PATCH_LENGTH);
    Serial.println("");
  #endif
}


void ZoomIf::HandleInput() {
  byte Index = 0;
  
  if (Com->available()) {
    Timer::Reset();
    
    #if DEBUG
      Serial.println("");
      Serial.println(CurrentEffects, BIN);
    #endif
    
    while ((Index < ZOOM_PATCH_LENGTH)) {
      Buffer[Index] = Com->read();
      if (Buffer[Index] == 0xFF) continue;
      if ((Buffer[Index++] == 0xF7) ||
          (Timer::Check(ZOOM_MSG_RX_TIMEOUT))) break;
    }
    
    if (Index == ZOOM_PARAM_LENGTH) {         // Disable effect / Param edit
      if ((Buffer[ZOOM_PARAM_ID_BYTE] == ZOOM_PARAM_ID) &&
          (Buffer[ZOOM_PARAM_NUMBER_BYTE] == 0x00)      &&
          (Buffer[ZOOM_PARAM_VALUE_BYTE] == 0x00))
      {
        BIT_CLR(CurrentEffects, Buffer[ZOOM_PARAM_SLOT_BYTE]);
      }
      
      #if DEBUG
        Serial.println(F("Received parameter data."));
      #endif
    }
    else if (Index == ZOOM_PATCH_LENGTH) {   // Enable effect / Send patch
      CurrentEffects = ZoomIf::GetPatchEffects(CurrentPatch);
      
      #if DEBUG
        Serial.println(F("Received patch data."));
      #endif
    }
    
    #if DEBUG
      Serial.println(Index, DEC);
      Serial.write(Buffer.data, Index);
      
      Serial.println("");
      Serial.println(CurrentEffects, BIN);
    #endif
    
    while (Com->read() >= 0); // Flush input buffer
  }
}


#if EEPROM_ENABLED
  void ZoomIf::FlashWrite(unsigned int Address) {
    byte Data, Counter = 0;
    unsigned int MemAddress;
    
    for (int i = 0; i < ZOOM_PATCH_LENGTH; i++) {
      MemAddress = Address + i;
      
      FlashMem::Mem.read(MemAddress, &Data, 1);
      
      if (Data != Buffer[i]) {
        Data = Buffer[i];
        FlashMem::Mem.write(MemAddress, &Data, 1);
        Counter++;
      }
    }
    
    #if DEBUG
      Serial.println("");
      Serial.print("TOTAL BYTES WRITTEN: ");
      Serial.println(Counter, DEC);
      Serial.print("ADDRESS: ");
      Serial.println(Address, DEC);
    #endif
  }


  void ZoomIf::FlashRead(unsigned int Address) {
    ARRAY_FILL(Buffer.data, ZOOM_PATCH_LENGTH, 0x00);
    FlashMem::Mem.read(Address, Buffer.data, ZOOM_PATCH_LENGTH);
  }
  
  
  unsigned int ZoomIf::FlashPatchAddress(byte PN) {
    return (unsigned int)pgm_read_word_near(MEM_ADDR_PATCH + PN);
  }
#endif


void ZoomIf::EmptyPatch() {
  ARRAY_FILL(Buffer.data, ZOOM_PATCH_LENGTH, 0x00);
  
  for (int i = 0; i < ZOOM_PATCH_LENGTH; i++) {
    Buffer[i] = pgm_read_byte_near(_EmptyPatch + i);
  }
}


void ZoomIf::ReadPatch(byte PN) {
  #if EEPROM_ENABLED
    unsigned int Address = FlashPatchAddress(PN);
    
    #if DEBUG
      Serial.print("READ PATCH "); Serial.print(PN);
      Serial.print(" FROM ADDRESS "); Serial.print(Address);
    #endif
    
    ZoomIf::FlashRead(Address);
  #else
    Buffer = ZoomIf::PatchMem[PN];
  #endif
}


void ZoomIf::SendPatch() {
  Com->write(Buffer.data, ZOOM_PATCH_LENGTH);
}


int ZoomIf::GetParam(byte Effect, byte Parameter) {
  int Out = 0, Offset, Index;
  
  Effect -= 1; Parameter -=1;
  
  for (int i = 0; i < ParamLength[Parameter]; i++)
  {
    Offset = pgm_read_byte_near(&ParamMap[Effect][Parameter][i][0]);
    Index  = pgm_read_byte_near(&ParamMap[Effect][Parameter][i][1]);
    
    byte PatchByte = Buffer[Offset];
    
    if (BIT_CHECK(PatchByte, Index)) BIT_SET(Out, i);
  }
  
  return Out;
}


void ZoomIf::SetParam(byte Effect, byte Parameter, int Value) {
  int Offset, Index;
  
  Effect -= 1; Parameter -=1;
  
  for (int i = 0; i < ParamLength[Parameter]; i++)
  {
    Offset = pgm_read_byte_near(&ParamMap[Effect][Parameter][i][0]);
    Index  = pgm_read_byte_near(&ParamMap[Effect][Parameter][i][1]);
    
    byte PatchByte = Buffer[Offset];
    
    if (BIT_CHECK(Value, i))
      BIT_SET(PatchByte, Index);
    else
      BIT_CLR(PatchByte, Index);
    
    Buffer[Offset] = PatchByte; 
  }
}