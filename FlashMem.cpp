#include "Arduino.h"
#include "Array.h"
#include "FlashMem.h"
#include <Wire.h>
#include <extEEPROM.h>

static extEEPROM FlashMem::Mem(kbits_256, 1, 64);

void FlashMem::Init() {
  Mem.begin(extEEPROM::twiClock400kHz);
}


_bufferType FlashMem::Read(unsigned int MemAddress) {
  _bufferType Out;
  ARRAY_FILL(Out, BUFFER_SIZE, 0x00);
  Mem.read(MemAddress, Out.data, BUFFER_SIZE);
  
  return Out;
}


void FlashMem::Write(unsigned int MemAddress, _bufferType Buffer) {
  Mem.write(MemAddress, Buffer.data, BUFFER_SIZE);
}
