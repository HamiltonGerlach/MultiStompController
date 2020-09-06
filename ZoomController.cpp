#include "Controller.h"
#include "Log.h"
#include "MultistompController.h"
#include "ZoomController.h"
#include "ZoomIf.h"


void ZoomController::OnReceiveCC() {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif  
  
  if (CN == 1) {        // Toggle effects on (CV -> bitmask)
    ADD_STATE(State, StateMode::SetEffects);
  }
  else if (CN == 2) {   // Toggle effects on (CV -> bitmask)
    ADD_STATE(State, StateMode::SwitchOn);
  }
  else if (CN == 3) {   // Toggle effects off (CV -> bitmask)
    ADD_STATE(State, StateMode::SwitchOff);
  }
}


void ZoomController::OnReceivePC() {
  #if DEBUG
    LogPC('R', Channel, PN);
  #endif
  
  if (PN < 50) {                        // Patch change
    ADD_STATE(State, StateMode::PatchChange);
  }
  else if ((PN >= 51) && (PN <= 56)) {  // Effect focus 1-6
    ZoomIf::CurrentFocus = PN - 50;
  
    ADD_STATE(State, StateMode::FocusChange);
  }
  else if ((PN >= 61) && (PN <= 119)) { // Param edit 1-9 (Slot = PN mod 10)
    Param = PN % 10;
    ParamSlot = floor((PN - 60) / 10);
  
    ADD_STATE(State, StateMode::SetParams);
  }
  else {                                // Custom messages / Reserved  
    ADD_STATE(State, StateMode::CustomMsg);
  }
}


void ZoomController::OnResetCtrl() {
  byte Patch = ZoomIf::CurrentPatch;
  byte Effects = ZoomIf::CurrentEffects;
  
  #if DEBUG
    Serial.println(CV, BIN);
  #endif
  
  
  if (State & StateMode::PatchChange) {
    if (PN != Patch)
    {
      Patch = PN;
      ZoomIf::Patch(PN, true);
      
      #if DEBUG
        Serial.println("PatchChange");
      #endif
    }
  }  
  
  
  
  if (State & StateMode::FocusChange) {
    //not_implemented();
    
    #if DEBUG
      Serial.println("FocusChange");
    #endif
  }
  
  
  
  if (State & StateMode::SetEffects) {
    #if DEBUG
      Serial.println("SetEffects");
    #endif
    
    Serial.println(Effects, BIN);
    
    byte EffectsCommon = Effects & CV;
    byte EffectsDiff = !EffectsCommon;
    
    Serial.println(EffectsCommon, BIN);
    Serial.println(EffectsDiff, BIN);
    
    
    if (BIT_CHECK(EffectsDiff, 3) ||
        BIT_CHECK(EffectsDiff, 4) ||
        BIT_CHECK(EffectsDiff, 5))
    {
      ZoomIf::SetPatchEffects(Patch, CV);
      
      #if DEBUG
        Serial.println("SetPatchEffects");
      #endif
    }
    else {
      if (EffectsDiff != 0)
      {
        for (int i = 0; i < 3; i++) {
          if (BIT_SET(EffectsDiff, i))
            ZoomIf::SwitchOn(Patch, i + 1);
          else
            ZoomIf::SwitchOff(Patch, i + 1);
        }
      }
      
      #if DEBUG
        Serial.println("Incremental");
      #endif
    }
  }
  
  
  
  if (State & StateMode::SwitchOn) {
    #if DEBUG
      Serial.println("SwitchOn");
    #endif
    
    if (BIT_CHECK(CV, 3) || BIT_CHECK(CV, 4) || BIT_CHECK(CV, 5)) {
      BITMASK_SET(Effects, CV);
      ZoomIf::SetPatchEffects(Patch, Effects);
      
      #if DEBUG
        Serial.println("SetPatchEffects");
      #endif
    }
    else {
      for (int i = 0; i < 3; i++) {
        if (BIT_SET(Effects, i))
          ZoomIf::SwitchOn(Patch, i + 1);
      }
      
      #if DEBUG
        Serial.println("Incremental");
      #endif
    }
  }
  
  
  
  if (State & StateMode::SwitchOff) {
    #if DEBUG
      Serial.println("SwitchOff");
    #endif
    
    if (BIT_CHECK(CV, 3) || BIT_CHECK(CV, 4) || BIT_CHECK(CV, 5)) {
      BITMASK_CLEAR(Effects, CV);
      ZoomIf::SetPatchEffects(Patch, Effects);
      
      #if DEBUG
        Serial.println("SetPatchEffects");
      #endif
    }
    else {
      for (int i = 0; i < 3; i++) {
        if (BIT_SET(Effects, i))
          ZoomIf::SwitchOff(Patch, i + 1);
      }
      
      #if DEBUG
        Serial.println("Incremental");
      #endif
    }
  }
  
  
  
  if (State & StateMode::CustomMsg) // Set effects via bitmask CV
  {
    //not_implemented();
    
    #if DEBUG
      Serial.println("CustomMsg");
    #endif
  }
  
  
  
  // Reset
  RST_STATE(State);
  
  Param = CONTROL_BYTE;
  ParamSlot = CONTROL_BYTE;
}
