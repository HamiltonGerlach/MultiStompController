#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

// Midi buffer
class Timer {
  public:
    unsigned long TimerStart, TimerCurrent;

    bool Check(unsigned long DeltaT);
    void Reset();
    
    Timer();
};

#endif
