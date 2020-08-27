#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"
#include "MultistompController.h"
#include "Buffer.h"

// Controller struct
class Controller {
  public:
    byte Channel; // channel number
    
    byte PN; // program number
    byte CN; // controller number
    byte CV; // controller value
    
    bool RxPC;  // received program change
    bool RxNormCC;  // received normal CC
    bool RxTermCC;  // received termination CC (B0 80 80)
    
    Stream *Com;    // serial port
    
    Controller();
    void Update(Buffer *Mem);
    void Reset();
    bool IsTerminated();
    
    void OnSend();
};

#endif