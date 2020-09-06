#include "Arduino.h"
// #include "IEventHandler.h"
#include "MultistompController.h"
#include "Controller.h"
#include "MidiBuffer.h"

Controller::Controller() {
  this->Reset();
}

void Controller::Init(Stream *Com, byte Channel)
{
  this->Com = Com;
  this->Channel = Channel;
}

void Controller::Update() {  
  if (MidiBuffer::CCTerm(Channel))
    RxTermCC = true;
  
  if (MidiBuffer::CCNorm(Channel)) {
    RxNormCC = true;
    CN = MidiBuffer::Data[1];
    CV = MidiBuffer::Data[2];
  }
  
  if (!RxPC) {
    PN = MidiBuffer::PC(Channel);
    if (PN < CONTROL_BYTE)
      RxPC = true;
    }
  
}

void Controller::Reset() {
  this->OnResetCtrl();
  
  PN = 0;
  CN = 0;
  CV = 0;

  RxPC = 0;
  RxNormCC = 0;
  RxTermCC = 0;
  
  RxActive = true;
}

bool Controller::Done() {
  return (RxNormCC || RxTermCC) ? true : false;
}

void Controller::OnSend() {
  if (RxNormCC) this->OnReceiveCC();
  if (RxPC)     this->OnReceivePC();
}
