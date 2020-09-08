#ifndef WIRE_H
#define WIRE_H

#include "Arduino.h"
#include "Array.h"
#include <Wire.h>

#define BUFFER_SIZE 30

typedef Array<byte, BUFFER_SIZE> _bufferType;

class FlashMem {
    public:
        static int DeviceAddress;
        static unsigned long Clock;
        
        static void Init(int DeviceAddress, unsigned long Clock);
        
        static byte ReadByte(unsigned int MemAddress);
        static void WriteByte(unsigned int MemAddress, byte Data);
        
        static _bufferType ReadBuffer(unsigned int MemAddress);
        static void WriteBuffer(unsigned int MemAddress, _bufferType Data);
};

#endif