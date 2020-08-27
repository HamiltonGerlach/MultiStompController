#include "Arduino.h"
#include "MultistompController.h"
#include "Controller.h"
#include "Buffer.h"

Controller::Controller() {
  this->Reset();
}

void Controller::Update(Buffer *Mem) {  
  if (Mem->CCTerm(Channel))
    RxTermCC = true;
  
  if (Mem->CCNorm(Channel)) {
    RxNormCC = true;
    CN = Mem->Data[1];
    CV = Mem->Data[2];
  }
  
  if (!RxPC) {
    PN = Mem->PC(Channel);
    if (PN < CONTROL_BYTE)
      RxPC = true;
    }
  
}

void Controller::Reset() {
  PN = 0;
  CN = 0;
  CV = 0;

  RxPC = 0;
  RxNormCC = 0;
  RxTermCC = 0;
}

bool Controller::IsTerminated() {
  return (RxNormCC || RxTermCC) ? true : false;
}

void Controller::OnSend() {
  //if (RxNormCC) OnReceiveCC(Com, Channel, CN, CV);
  //if (RxPC)     OnReceivePC(Com, Channel, PN);
}