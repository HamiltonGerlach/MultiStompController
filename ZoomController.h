#ifndef ZOOMCTRL_H
#define ZOOMCTRL_H

#include "Controller.h"
#include "MultistompController.h"

class ZoomController : public Controller
{
public:
    int Param = CONTROL_BYTE;
    int ParamSlot = CONTROL_BYTE;
    
    void OnReceiveCC();
    void OnReceivePC();
    void OnResetCtrl();
};

#endif