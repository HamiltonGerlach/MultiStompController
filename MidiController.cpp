#include "Controller.h"
#include "MidiController.h"
#include "MidiOutIf.h"
#include "Log.h"

void MidiController::OnReceiveCC() {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif
  
  MidiOutIf::CC(Com, Channel, CN, CV);
}

void MidiController::OnReceivePC() {
  #if DEBUG
    LogPC('R', Channel, PN);
  #endif
  
  MidiOutIf::PC(Com, Channel, PN);
}

void MidiController::OnResetCtrl() {}