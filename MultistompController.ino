#define DEBUG false

#include <AltSoftSerial.h>
#include "MultistompController.h"
#include "Buffer.h"
#include "Controller.h"


// GLOBALS
Buffer Mem;
Controller CtrlMIDI, CtrlZoom;

unsigned long TimerStart, TimerCurrent;
bool RxActive;

AltSoftSerial MIDI_STREAM = AltSoftSerial(MIDI_SERIAL_RX, MIDI_SERIAL_TX);


// MAIN INIT FUNCTION
void setup() {
  MIDI_STREAM.begin(MIDI_BAUDRATE);    // MIDI In/Out
  MIDI_STREAM.flush();
  
  USB_STREAM.begin(USB_BAUDRATE);      // USB Host MIDI Out
  USB_STREAM.flush();
  
  pinMode(SWITCH_TUNER, INPUT_PULLUP); // Tuner switch
  
  TimerStart = millis();
}


// MAIN LOOP FUNCTION
void loop() {
  while ((MIDI_STREAM.available() > 0) && RxActive) {
    Mem.Push(MIDI_STREAM.read());
    CtrlMIDI.Update(&Mem);
    CtrlZoom.Update(&Mem);
  }
  
  // STATE CHECK & SENDING ROUTINE
  if (CtrlMIDI.IsTerminated() && CtrlZoom.IsTerminated()) {
    MidiOutCC(&USB_STREAM, 1, 0x4A, 0x00);   // Tuner off message

    if (CtrlZoom.RxNormCC)
      OnReceiveCC(&USB_STREAM, USB_CHANNEL, CtrlZoom.CN, CtrlZoom.CV);
    if (CtrlZoom.RxPC)
      OnReceivePC(&USB_STREAM, USB_CHANNEL, CtrlZoom.PN);
    
    if (CtrlMIDI.RxNormCC)
      OnReceiveCC(&MIDI_STREAM, MIDI_CHANNEL, CtrlMIDI.CN, CtrlMIDI.CV);
    if (CtrlMIDI.RxPC)
      OnReceivePC(&MIDI_STREAM, MIDI_CHANNEL, CtrlMIDI.PN);
    
    CtrlMIDI.Reset();
    CtrlZoom.Reset();
    
    Mem.Flush(); RxActive = true; // TODO: start RxActive timer
  }
  
  // TUNER SWITCH HANDLING
  TimerCurrent = millis();
  if ((digitalRead(SWITCH_TUNER) != HIGH) && (TimerCurrent - TimerStart > SWITCH_DEB)) {
    // MidiOutCC(&USB_STREAM, USB_CHANNEL, 0x4A, 0x7F);   // Tuner on message
    
//    Zoom_ParamEnable();
  //  Zoom_SwitchOn(1);
    //Zoom_ParamDisable();
    
    TimerStart = TimerCurrent;
  }
}



// SEND EVENTS
void OnReceivePC(Stream *Com, byte Channel, byte PN) {
  #if DEBUG
    LogPC('R', Channel, PN)
  #endif

  if (PN < 50) MidiOutPC(Com, Channel, PN);
  else {
    // MidiOutPC(Com, Channel, PN); // TODO
  }
}

void OnReceiveCC(Stream *Com, byte Channel, byte CN, byte CV) {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif
  
  MidiOutCC(Com, Channel, CN, CV);
}


// MIDI OUT FUNCTIONS
void MidiOutPC(Stream *Com, byte Channel, byte PN) {
  #if DEBUG
    LogPC('T', Channel, PN)
  #endif
  
  Com->write(0xC0 + Channel - 1);
  Com->write(PN);
}

void MidiOutCC(Stream *Com, byte Channel, byte CN, byte CV) {
  #if DEBUG
    LogCC('T', Channel, CN, CV);
  #endif
  
  Com->write(0xB0 + Channel - 1);
  Com->write(CN);
  Com->write(CV);
}

void Zoom_ParamEnable(Stream *Com) {
  byte Msg[] = ZOOM_MSG_PRM_ENA;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_ParamDisable(Stream *Com) {
  byte Msg[] = ZOOM_MSG_PRM_DEA;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_SwitchOn(Stream *Com, byte Slot)
{
  byte Msg[] = ZOOM_MSG_EFF_ON;
  
  Msg[5] = Slot - 1;  
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_SwitchOff(Stream *Com, byte Slot)
{
  byte Msg[] = ZOOM_MSG_EFF_OFF;
  
  Msg[5] = Slot - 1;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_ParamEdit(Stream *Com, byte Slot, byte Param, int Value)
{
  byte Msg[] = ZOOM_MSG_PRM_EDIT;
  
  Msg[5] = Slot - 1;
  Msg[6] = Param + 0x01;
  Msg[7] = Value & 0x7F;      // 7 bit LSB
  Msg[8] = (Value>>7) & 0x7F; // 7 bit MSB
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}
