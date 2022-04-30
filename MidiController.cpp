#include "Arduino.h"
#include "Controller.h"
#include "MidiController.h"
#include "MidiOutIf.h"
#include "Log.h"
#include "Timer.h"


MidiController::MidiController() {
  ValueStart = 0;
  ValueEnd = 0;
  ValueCurrent = 0;
  ValuePrev = 0;
  
  RampParameter = IRIDIUM_CN_EXPRESSION;
  IsRamping = false;
}

void MidiController::OnReceiveCC() {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif
  
  if (CN == IRIDIUM_PN_MANUAL_MODE) {
    ADD_STATE(State, Iridium::StateMode::ManualMode);
  }
  
  if (CN <= IRIDIUM_CN_TBL_LEN) {
    ADD_STATE(State, Iridium::StateMode::ParamChange);
  }
  
  if (CN == IRIDIUM_PN_FORCE_PATCH) {
    ADD_STATE(State, Iridium::StateMode::ForcePatch);
    DPRINTLNF("ForcePatch");
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
    if ((PN != Param.Patch) || (State & Iridium::StateMode::ForcePatch))
    {
      Param.Patch = PN;
      MidiOutIf::PC(Com, Channel, PN);
      
      DPRINTLNF("PatchChange");
    }
  }
  
  if (State & Iridium::StateMode::ParamChange) {
    byte ParamCN = pgm_read_byte_near(Iridium::ParamTable + CN - 1);
    
    ValueStart = ValueCurrent;
    ValueEnd = CV;
    
    if (ValueStart != ValueEnd)
    {
      RampParameter = ParamCN;
      IsRamping = true;
      
      RampDirection = (ValueCurrent < ValueEnd) ? 1 : -1;
      
      Clock.Reset();
    }
    else
    {
      MidiOutIf::CC(Com, Channel, ParamCN, CV);
    }
    
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


void MidiController::Invoke() {
  if (IsRamping)
  {    
    if (Gate.Check(IRIDIUM_RAMP_GATE_MS))
    {
      unsigned long DeltaT = millis() - Clock.TimerStart;
      float FacT = ((float)DeltaT / (float)IRIDIUM_RAMP_GRAD_MS);
      float CV = ValueStart + FacT * (ValueEnd - ValueStart);
      
      ValueCurrent = CV;
      
      if (((RampDirection == 1) && (ValueCurrent >= ValueEnd)) || 
         ((RampDirection == -1) && (ValueCurrent <= ValueEnd)) ||
         (ValueCurrent < 0) || (ValueCurrent > 127))
      {
        ValueCurrent = ValueEnd;
        IsRamping = false;
      }
      
      if ((ValueCurrent != ValueStart) && (ValueCurrent != ValuePrev))
      {
        MidiOutIf::CC(Com, Channel, RampParameter, ValueCurrent);
        ValuePrev = ValueCurrent;
      }
      
      Gate.Reset();
    }
    
  }
}
