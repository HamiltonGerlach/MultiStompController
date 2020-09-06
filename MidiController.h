#ifndef MIDICTRL_H
#define MIDICTRL_H

#include "Controller.h"

class MidiController : public Controller
{
public:    
    void OnReceiveCC();
    void OnReceivePC();
    void OnResetCtrl();
};

#endif