#ifndef ZOOMCTRL_H
#define ZOOMCTRL_H

#include "Controller.h"
#include "MultistompController.h"

#define ZOOM_CN_EFFECT_SET  1
#define ZOOM_CN_EFFECT_ON   2
#define ZOOM_CN_EFFECT_OFF  3

#define ZOOM_PN_PATCH_TH    50

#define ZOOM_CUSTOM_MSG_NUM 8


namespace Zoom {
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
}


class ZoomController : public Controller
{
public:
    int Param = CONTROL_BYTE;
    int ParamSlot = CONTROL_BYTE;
    byte CustomMsgIdx;
    
    _customMsg CustomMessage[ZOOM_CUSTOM_MSG_NUM] =
        { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
    
    Zoom::StateMode State = Zoom::StateMode::None;
    
    void OnReceiveCC();
    void OnReceivePC();
    void OnResetCtrl();
};

#endif