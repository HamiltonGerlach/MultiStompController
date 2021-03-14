#include "Arduino.h"
#include "Log.h"

void Log(byte x)    { DWRITE(x); }
void Log(int x)     { DWRITE(x); }

void LogCC(char Direction, byte Channel, byte CN, byte CV) {
  DPRINTLN("");
  DPRINT(Direction);
  DPRINTF("X: Channel ");
  DPRINT(Channel, DEC);
  DPRINTF(" CC ");
  DPRINT(CN, DEC);
  DPRINT(" ");
  DPRINTLN(CV, DEC);
}

void LogPC(char Direction, byte Channel, byte PN) {
  DPRINTLN("");
  DPRINT(Direction);
  DPRINTF("X: Channel ");
  DPRINT(Channel, DEC);
  DPRINTF(" PC ");
  DPRINTLN(PN, DEC);
}