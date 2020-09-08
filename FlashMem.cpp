#include "Arduino.h"
#include "Array.h"
#include "FlashMem.h"
#include <Wire.h>

static int FlashMem::DeviceAddress = 0x50;
static unsigned long FlashMem::Clock = 100000;


void FlashMem::Init(int DeviceAddress, unsigned long Clock) {
  Wire.begin();
  
  FlashMem::DeviceAddress = DeviceAddress;
  FlashMem::Clock = Clock;
  
  Wire.setClock(Clock);
}

byte FlashMem::ReadByte(unsigned int MemAddress) {
  byte Data = 0xFF;
 
  Wire.beginTransmission(DeviceAddress);
  Wire.write((int)(MemAddress >> 8));   // MSB
  Wire.write((int)(MemAddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(DeviceAddress, 1);
 
  if (Wire.available()) Data = Wire.read();
 
  return Data;
}


void FlashMem::WriteByte(unsigned int MemAddress, byte Data) {
  Wire.beginTransmission(DeviceAddress);
  Wire.write((int)(MemAddress >> 8));   // MSB
  Wire.write((int)(MemAddress & 0xFF)); // LSB
  Wire.write(Data);
  Wire.endTransmission();
  
  delay(5);
}


_bufferType FlashMem::ReadBuffer(unsigned int MemAddress) {
  _bufferType Out;
  byte Index = 0;
  
  ARRAY_FILL(Out, BUFFER_SIZE, 0xFF);
  
  unsigned long t = micros();
  
  Wire.beginTransmission(DeviceAddress);
  Wire.write((int)(MemAddress >> 8));   // MSB
  Wire.write((int)(MemAddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(DeviceAddress, BUFFER_SIZE);
 
  while (Index < BUFFER_SIZE)
  {
    if (Wire.available()) Out[Index++] = Wire.read();
  }
  
  Serial.println(micros() - t);
  
  return Out;
}


void FlashMem::WriteBuffer(unsigned int MemAddress, _bufferType Data) {
  unsigned long t = micros();
  
  Wire.beginTransmission(DeviceAddress);
  Wire.write((int)(MemAddress >> 8));   // MSB
  Wire.write((int)(MemAddress & 0xFF)); // LSB
  Wire.write(Data.data, BUFFER_SIZE);
  Wire.endTransmission();
  
  Serial.println(micros() - t);
  
  delay(5);
}


