#include "Controller.h"
#include "MidiController.h"
#include "MidiOutIf.h"
#include "Log.h"


void MidiController::OnReceiveCC() {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif
  
  if (CN == 127) {
    ADD_STATE(State, Iridium::StateMode::ManualMode);
  }
  else if (CN <= IRIDIUM_CN_TBL_LEN) {
    ADD_STATE(State, Iridium::StateMode::ParamChange);
  }
}


void MidiController::OnReceivePC() {
  #if DEBUG
    LogPC('R', Channel, PN);
  #endif
  
  if (PN < 10) {
    ADD_STATE(State, Iridium::StateMode::PatchChange);
  }
  else if ((PN >= 10) && (PN < 20))
  {
    CustomMsgIdx = PN - 10;
    
    ADD_STATE(State, Iridium::StateMode::CustomMsg);
  }
}


void MidiController::OnResetCtrl() {
  if (State & Iridium::StateMode::PatchChange) {
    if (PN != Param.Patch)
    {
      Param.Patch = PN;
      MidiOutIf::PC(Com, Channel, PN);
      
      DPRINTLNF("PatchChange");
    }
  }
  
  
  if (State & Iridium::StateMode::ParamChange) {
    byte ParamCN = pgm_read_byte_near(Iridium::ParamTable + CN - 1);
    
    MidiOutIf::CC(Com, Channel, ParamCN, CV);
    
    DPRINTLNF("ParamChange");
  }
  
  
  if (State & Iridium::StateMode::ManualMode) {
    MidiOutIf::PC(Com, Channel, IRIDIUM_PN_MANUAL_MODE);
    
    DPRINTLNF("ManualMode");
  }
  
  
  if (State & Iridium::StateMode::CustomMsg) {
    if (CustomMessage[CustomMsgIdx] != NULL)
      CustomMessage[CustomMsgIdx](this, PN, CN, CV);
  
    DPRINTLNF("CustomMsg");
  }
  
  
  // RESET STATE
  RST_STATE(State);
}