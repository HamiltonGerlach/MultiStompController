#ifndef BUFFER_H
#define BUFFER_H

#include "Arduino.h"
#include "MultistompController.h"

// Midi buffer
class Buffer {
  public:
    byte Data[3];
    
    Buffer();
    void Push(byte In);
    bool CCBank(byte Channel);
    bool CCNorm(byte Channel);
    bool CCTerm(byte Channel);
    byte PC(byte Channel);
    void Flush();
};

#endif