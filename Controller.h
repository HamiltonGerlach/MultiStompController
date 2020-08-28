#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"
#include "MultistompController.h"
#include "Buffer.h"

typedef void (*_onReceiveCC) (Stream *, byte, byte, byte);
typedef void (*_onReceivePC) (Stream *, byte, byte);

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
    
    _onReceiveCC OnReceiveCC;
    _onReceivePC OnReceivePC;
    
    Controller();
    
    void Init(Stream *Com, byte Channel,
              _onReceiveCC OnReceiveCC, _onReceivePC OnReceivePC);
    
    void Update(Buffer *Mem);
    void Reset();
    bool Done();
    
    void OnSend();
};

#endif
