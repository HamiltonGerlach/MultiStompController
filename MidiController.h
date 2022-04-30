#ifndef MIDICTRL_H
#define MIDICTRL_H

#include "Controller.h"
#include "MultistompController.h"
#include "Timer.h"

#define IRIDIUM_CN_TBL_LEN      8
#define IRIDIUM_CN_VOLUME       7
#define IRIDIUM_CN_LEVEL        12
#define IRIDIUM_CN_DRIVE        13
#define IRIDIUM_CN_BASS         14
#define IRIDIUM_CN_MID          15
#define IRIDIUM_CN_TREBLE       16
#define IRIDIUM_CN_ROOM         17
#define IRIDIUM_CN_EXPRESSION   100

#define IRIDIUM_PN_FORCE_PATCH  126
#define IRIDIUM_PN_MANUAL_MODE  127

#define IRIDIUM_CUSTOM_MSG_NUM  10

#define IRIDIUM_RAMP_GRAD_MS    100
#define IRIDIUM_RAMP_GATE_MS    10


namespace Iridium {
    const PROGMEM byte ParamTable[] =
        {   IRIDIUM_CN_VOLUME, IRIDIUM_CN_LEVEL, IRIDIUM_CN_DRIVE,
            IRIDIUM_CN_BASS, IRIDIUM_CN_MID, IRIDIUM_CN_TREBLE,
            IRIDIUM_CN_ROOM, IRIDIUM_CN_EXPRESSION  };
    
    enum StateMode {
        None        = 0,
        PatchChange = BIT(0),
        ParamChange = BIT(1),
        ManualMode  = BIT(2),
        CustomMsg   = BIT(3),
        ForcePatch  = BIT(4)
    };
    
    typedef struct Parameters {
        byte Patch      = CONTROL_BYTE;
        byte Level      = CONTROL_BYTE;
        byte Drive      = CONTROL_BYTE;
        byte Bass       = CONTROL_BYTE;
        byte Mid        = CONTROL_BYTE;
        byte Treble     = CONTROL_BYTE;
        byte Room       = CONTROL_BYTE;
        byte Expression = CONTROL_BYTE;
        byte Volume     = CONTROL_BYTE;
        
        Parameters() :
            Patch(CONTROL_BYTE),
            Volume(CONTROL_BYTE),
            Level(CONTROL_BYTE),
            Drive(CONTROL_BYTE),
            Bass(CONTROL_BYTE),
            Mid(CONTROL_BYTE),
            Treble(CONTROL_BYTE),
            Room(CONTROL_BYTE),
            Expression(CONTROL_BYTE) {}
    };
}


class MidiController : public Controller
{
private:
    Timer Clock, Gate;
    
    byte ValueStart, ValueEnd, ValueCurrent, ValuePrev;
    byte RampParameter, RampDirection;
    bool IsRamping;
        
public:
    byte CustomMsgIdx;
    
    _customMsg CustomMessage[IRIDIUM_CUSTOM_MSG_NUM] =
        { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    
    Iridium::Parameters Param;    
    Iridium::StateMode State = Iridium::StateMode::None;
    
    void OnReceiveCC();
    void OnReceivePC();
    void OnResetCtrl();
    
    void Invoke();
    
    MidiController();
};

#endif
