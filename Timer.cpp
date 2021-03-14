#include "Arduino.h"
#include "Timer.h"

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