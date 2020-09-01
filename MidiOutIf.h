#ifndef MIDIOUTIF_H
#define MIDIOUTIF_H

#include "Arduino.h"

class MidiOutIf
{
  public:
    static void PC(Stream *Com, byte Channel, byte PN);
    static void CC(Stream *Com, byte Channel, byte CN, byte CV);
  
  private:
    MidiOutIf();
};

#endif