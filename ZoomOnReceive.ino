// SEND EVENTS
#include "MultistompController.h"
#include "MidiOutIf.h"
#include "Log.h"
#include "ZoomIf.h"
#include "ZoomOnReceive.h"

/////// MAKE EVENTHANDLER INTERFACE / ABSTRACT CLASS
StateMode ZoomMode = None;

int Zoom_PN = CONTROL_BYTE,
    Zoom_CN = CONTROL_BYTE,
    Zoom_CV = CONTROL_BYTE,
    Zoom_Param = CONTROL_BYTE,
    Zoom_PrmSlot = CONTROL_BYTE;

// Zoom/USB receive PC
void Zoom_OnReceivePC(Stream *Com, byte Channel, byte PN) {
  #if DEBUG
    LogPC('R', Channel, PN);
  #endif
  
  Zoom_PN = PN;

  if (PN < 50)                          // Patch change
  {
    ADD_STATE(ZoomMode, PatchChange);
    
    ZoomIf::Patch(PN);
  }
  else if ((PN >= 51) && (PN <= 56))    // Effect focus 1-6
  {
    ADD_STATE(ZoomMode, FocusChange);
    
    ZoomIf::CurrentFocus = PN - 50;
  }
  else if ((PN >= 61) && (PN <= 119))   // Param edit 1-9 (Slot = PN mod 10)
  {
    Zoom_Param = PN % 10;
    Zoom_PrmSlot = (PN - 50) / 10;
    
    ADD_STATE(ZoomMode, SetParams);
  }
}

// Zoom/USB receive CC
void Zoom_OnReceiveCC(Stream *Com, byte Channel, byte CN, byte CV) {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif
  
  Zoom_CN = CN;
  Zoom_CV = CV;
  
  if ((CN >= 1) && (CN <= 6)) {         // Toggle effects (CV -> bitmask)
    ADD_STATE(ZoomMode, SetEffects);
  }
}

// Zoom/USB reset
void Zoom_OnReset(Stream *Com) {
  // Send all pending messages
  
  
  // Reset
  ZoomMode = None;
  
  Zoom_PN = CONTROL_BYTE;
  Zoom_CN = CONTROL_BYTE;
  Zoom_CV = CONTROL_BYTE;
  Zoom_Param = CONTROL_BYTE;
  Zoom_PrmSlot = CONTROL_BYTE;
}