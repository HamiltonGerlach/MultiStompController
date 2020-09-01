// ZOOM SYSTEM MESSAGES
#include "Arduino.h"
#include "Array.h"
#include "MidiOutIf.h"
#include "MultistompController.h"
#include "ZoomIf.h"
#include "ZoomMsg.h"

static Stream    *ZoomIf::Com;
static byte       ZoomIf::Channel;

#if ZOOM_SRAM_MEM
  static byte     ZoomIf::PatchMem[ZOOM_SRAM_PATCHES][ZOOM_PATCH_LENGTH];
#endif


void ZoomIf::Init(Stream *Com, byte Channel) {
  ZoomIf::Com = Com;
  ZoomIf::Channel = Channel;
  ZoomIf::ParamEnable();
}


bool ZoomIf::IdentityRequest() {
  return true;
}


void ZoomIf::ParamEnable() {
  byte Msg[] = ZOOM_MSG_PRM_ENA;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}


void ZoomIf::ParamDisable() {
  byte Msg[] = ZOOM_MSG_PRM_DEA;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}


void ZoomIf::SwitchOn(byte PN, byte Slot) {
  byte Msg[] = ZOOM_MSG_EFF_ON;
  
  Msg[5] = Slot - 1;  
  
  ZoomIf::Patch(PN);
  Com->write(Msg, ARRAY_SIZE(Msg));
}


void ZoomIf::SwitchOff(byte PN, byte Slot) {
  byte Msg[] = ZOOM_MSG_EFF_OFF;
  
  Msg[5] = Slot - 1;
  
  ZoomIf::Patch(PN);
  Com->write(Msg, ARRAY_SIZE(Msg));
}


void ZoomIf::ParamEdit(byte Slot, byte Param, int Value) {
  byte Msg[] = ZOOM_MSG_PRM_EDIT;
  
  Msg[5] = Slot - 1;
  Msg[6] = Param + 0x01;
  Msg[7] = Value & 0x7F;      // 7 bit LSB
  Msg[8] = (Value>>7) & 0x7F; // 7 bit MSB
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}


void ZoomIf::SetEffects(byte PN, bool *StateVector) {
  byte Msg[] = ZOOM_MSG_EFF_ON;
  
  ZoomIf::Patch(PN);
  
  for (int i = 0; i < 6; i++) {
    bool State = StateVector[i];
    
    Msg[5] = i;
    Msg[7] = State ? 0x01 : 0x00;
    
    Com->write(Msg, ARRAY_SIZE(Msg));
  }
}


Array<byte, ZOOM_PATCH_LENGTH> ZoomIf::RequestPatch(byte PN) {
  byte Msg[] = ZOOM_MSG_PATCH_REQUEST;
  byte PatchData[ZOOM_PATCH_LENGTH];
  Array<byte, ZOOM_PATCH_LENGTH> PatchOut;
  
  ZoomIf::Patch(PN);                            // Select patch
  
  Com->write(Msg, ARRAY_SIZE(Msg));             // Send patch request
  Com->readBytes(PatchData, ZOOM_PATCH_LENGTH); // Receive patch data
  
  while(Com->read() >= 0);                      // Flush input buffer
  
  for (int i = 0; i < ZOOM_PATCH_LENGTH; i++)
    PatchOut[i] = PatchData[i];
  
  return PatchOut;
}


void ZoomIf::Tuner(bool State) {
  byte Value = State ? 0x7F : 0x00;
  
  if (!State) ParamDisable();
  
  MidiOutIf::CC(Com, Channel, 0x4A, Value);
  
  if (State) ParamEnable();
}


void ZoomIf::Patch(byte PN) {
  MidiOutIf::PC(Com, Channel, PN);
}