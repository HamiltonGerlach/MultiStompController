#include "Log.h"
#include "MultistompController.h"
#include "State.h"
#include "ZoomController.h"
#include "ZoomIf.h"


void ZoomController::OnReceiveCC() {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif
  
  
  if (CN == ZOOM_CN_EFFECT_SET) {      // Toggle effects on (CV -> bitmask)
    ADD_STATE(State, Zoom::StateMode::SetEffects);
  }
  else if (CN == ZOOM_CN_EFFECT_ON) {  // Toggle effects on (CV -> bitmask)
    ADD_STATE(State, Zoom::StateMode::SwitchOn);
  }
  else if (CN == ZOOM_CN_EFFECT_OFF) { // Toggle effects off (CV -> bitmask)
    ADD_STATE(State, Zoom::StateMode::SwitchOff);
  }
}


void ZoomController::OnReceivePC() {
  #if DEBUG
    LogPC('R', Channel, PN);
  #endif
  
  
  if (PN < ZOOM_PN_PATCH_TH) {          // Patch change
    ADD_STATE(State, Zoom::StateMode::PatchChange);
  }
  else if ((PN >= 51) &&
           (PN <= 56)) {                // Effect focus 1-6
    ZoomIf::CurrentFocus = PN - 50;
  
    ADD_STATE(State, Zoom::StateMode::FocusChange);
  }
  else if ((PN >= 61) &&
           (PN <= 119)) {               // Param edit 1-9 (Slot = PN mod 10)
    Param = PN % 10;
    ParamSlot = floor((PN - 60) / 10);
  
    ADD_STATE(State, Zoom::StateMode::SetParams);
  }
  else if ((PN >= 120) && (PN <= 127)) { // Custom messages / Reserved  
    CustomMsgIdx = PN - 120;
    
    ADD_STATE(State, Zoom::StateMode::CustomMsg);
  }
}


void ZoomController::OnResetCtrl() {
  byte Patch = ZoomIf::CurrentPatch;
  byte Effects = ZoomIf::CurrentEffects;
  
  DPRINTF("CV In: ");
  DPRINTLN(CV, BIN);
  
  
  if (State & Zoom::StateMode::PatchChange) {
    if (PN != Patch)
    {
      Patch = PN;
      ZoomIf::Patch(PN, true);
      
      DPRINTLNF("PatchChange");
    }
  }  
  
  
  
  if (State & Zoom::StateMode::FocusChange) {
    //not_implemented();
    
    DPRINTLNF("FocusChange");
  }
  
  
  
  if (State & Zoom::StateMode::SetEffects) {
    DPRINTLNF("SetEffects");
    DPRINTF("Current Effects: ");
    DPRINTLN(Effects, BIN);
    
    byte EffectsShared = Effects & CV;
    byte EffectsDelta = Effects ^ CV;
    
    DPRINTF("Common Effects: ");
    DPRINTLN(EffectsShared, BIN);
    DPRINTF("Diff Effects: ");
    DPRINTLN(EffectsDelta, BIN);
  
    if (BIT_CHECK(EffectsDelta, 3) ||
        BIT_CHECK(EffectsDelta, 4) ||
        BIT_CHECK(EffectsDelta, 5))
    {
      ZoomIf::SetPatchEffects(Patch, CV, true);
      
      DPRINTLNF("SetPatchEffects");
    }
    else {
      if (EffectsDelta != 0)
      {
        for (int i = 0; i < 3; i++) {
          if (BIT_CHECK(EffectsDelta, i)) {
            if (BIT_CHECK(CV, i))
              ZoomIf::SwitchOn(Patch, i + 1);
            else
              ZoomIf::SwitchOff(Patch, i + 1);
          }
        }
      }
      
      DPRINTLNF("Incremental");
    }
  }
  
  
  
  if (State & Zoom::StateMode::SwitchOn) {
    DPRINTLNF("SwitchOn");
    
    if (BIT_CHECK(CV, 3) || BIT_CHECK(CV, 4) || BIT_CHECK(CV, 5)) {
      BITMASK_SET(Effects, CV);
      ZoomIf::SetPatchEffects(Patch, Effects, true);
      
      DPRINTLNF("SetPatchEffects");
    }
    else {
      for (int i = 0; i < 3; i++) {
        if (BIT_CHECK(CV, i))
          ZoomIf::SwitchOn(Patch, i + 1);
      }
      
      DPRINTLNF("Incremental");
    }
  }
  
  
  
  if (State & Zoom::StateMode::SwitchOff) {
    DPRINTLNF("SwitchOff");
    
    if (BIT_CHECK(CV, 3) || BIT_CHECK(CV, 4) || BIT_CHECK(CV, 5)) {
      BITMASK_CLEAR(Effects, CV);
      ZoomIf::SetPatchEffects(Patch, Effects, true);
      
      DPRINTLNF("SetPatchEffects");
    }
    else {
      for (int i = 0; i < 3; i++) {
        if (BIT_CHECK(CV, i))
          ZoomIf::SwitchOff(Patch, i + 1);
      }
      
      DPRINTLNF("Incremental");
    }
  }
  
  
  
  if (State & Zoom::StateMode::CustomMsg) {
    if (CustomMessage[CustomMsgIdx] != NULL)
      CustomMessage[CustomMsgIdx](this, PN, CN, CV);
  
    DPRINTLNF("CustomMsg");
  }
  
  
  
  // Reset
  RST_STATE(State);
  
  Param = CONTROL_BYTE;
  ParamSlot = CONTROL_BYTE;
}
