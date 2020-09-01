#include "Arduino.h"
#include "MultistompController.h"
#include "Controller.h"
#include "MidiBuffer.h"

Controller::Controller() {
  this->Reset();
}

void Controller::Init(Stream *Com, byte Channel,
                      _onReceiveCC OnReceiveCC,
                      _onReceivePC OnReceivePC)
{
  this->Com = Com;
  this->Channel = Channel;
  this->OnReceiveCC = OnReceiveCC;
  this->OnReceivePC = OnReceivePC;
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
  if (RxNormCC) this->OnReceiveCC(Com, Channel, CN, CV);
  if (RxPC)     this->OnReceivePC(Com, Channel, PN);
}
