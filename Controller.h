#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"
#include "State.h"

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
    bool RxActive;  // receiving state
    
    Stream *Com;    // serial port
    
    Controller();
    
    void Init(Stream *Com, byte Channel);
    
    void Update();
    void Reset();
    bool Done();
    
    void OnSend();
    
    virtual void OnReceiveCC() {};
    virtual void OnReceivePC() {};
    virtual void OnResetCtrl() {};
};

typedef byte(*_customMsg)(Controller*, byte, byte, byte);

#endif
