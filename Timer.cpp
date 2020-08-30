#include "Arduino.h"
#include "Timer.h"

static unsigned long Timer::TimerStart, Timer::TimerCurrent;

Timer::Timer() {
  TimerStart = millis();
}

bool Timer::Check(unsigned long DeltaT) {
  TimerCurrent = millis();
  return (TimerCurrent - TimerStart) > DeltaT ? true : false;
}

void Timer::Reset() {
  TimerStart = millis();
}