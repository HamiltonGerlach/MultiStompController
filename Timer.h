#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

// Midi buffer
class Timer {
  public:
    static unsigned long TimerStart, TimerCurrent;

    static bool Check(unsigned long DeltaT);
    static void Reset();

  private:
    Timer();
};

#endif
