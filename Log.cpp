#include "Arduino.h"
#include "Log.h"

void Log(byte x)    { Serial.write(x); }
void Log(int x)     { Serial.write(x); }

void LogCC(char Direction, byte Channel, byte CN, byte CV) {
  Serial.println("");
  Serial.print(Direction);
  Serial.print(F("X: Channel "));
  Serial.print(Channel, DEC);
  Serial.print(F(" CC "));
  Serial.print(CN, DEC);
  Serial.print(" ");
  Serial.println(CV, DEC);
}

void LogPC(char Direction, byte Channel, byte PN) {
  Serial.println("");
  Serial.print(Direction);
  Serial.print(F("X: Channel "));
  Serial.print(Channel, DEC);
  Serial.print(F(" PC "));
  Serial.println(PN, DEC);
}