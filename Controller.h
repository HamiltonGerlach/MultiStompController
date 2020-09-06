#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Arduino.h"
#include "MultistompController.h"
#include "MidiBuffer.h"

enum StateMode {
    None = 0,
    PatchChange = BIT(0),
    FocusChange = BIT(1),
    SetEffects  = BIT(2),
    SwitchOn    = BIT(3),
    SwitchOff   = BIT(4),
    SetParams   = BIT(5),
    CustomMsg   = BIT(6)
};

#define ADD_STATE(state, s) state |= s
#define RST_STATE(state) state = StateMode::None


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
    StateMode State = StateMode::None; // controller state
    
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

#endif
