#ifndef WIRE_H
#define WIRE_H

#include "Arduino.h"
#include "Array.h"
#include <Wire.h>
#include <extEEPROM.h>

#define BUFFER_SIZE 10

typedef Array<byte, BUFFER_SIZE> _bufferType;

class FlashMem {
    public:
        static extEEPROM Mem;
        
        static void Init();
        
        static _bufferType Read(unsigned int MemAddress);
        static void Write(unsigned int MemAddress, _bufferType Data);
};

#endif