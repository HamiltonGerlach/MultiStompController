#include "Arduino.h"
#include "MidiOutIf.h"
#include "MultistompController.h"
#include "Log.h"

void MidiOutIf::PC(Stream *Com, byte Channel, byte PN) {
  #if DEBUG
    LogPC('T', Channel, PN);
  #endif
  
  Com->write(0xC0 + Channel - 1);
  Com->write(PN);
}

void MidiOutIf::CC(Stream *Com, byte Channel, byte CN, byte CV) {
  #if DEBUG
    LogCC('T', Channel, CN, CV);
  #endif
  
  Com->write(0xB0 + Channel - 1);
  Com->write(CN);
  Com->write(CV);
}
