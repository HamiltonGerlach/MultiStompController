#define DEBUG false

#include "MultistompController.h"

#include <AltSoftSerial.h>
#include "Buffer.h"
#include "Controller.h"


// GLOBALS
Buffer Mem;
Controller CtrlMIDI, CtrlZoom;
unsigned long TimerStart, TimerCurrent;
AltSoftSerial MIDI_STREAM = AltSoftSerial(MIDI_SERIAL_RX, MIDI_SERIAL_TX);


// MAIN INIT FUNCTION
void setup() {
  pinMode(SWITCH_TUNER, INPUT_PULLUP); // Tuner switch
  
  MIDI_STREAM.begin(MIDI_BAUDRATE);    // MIDI In/Out
  MIDI_STREAM.flush();
    
  ZOOM_STREAM.begin(ZOOM_BAUDRATE);    // USB Host MIDI Out
  ZOOM_STREAM.flush();

  // Setup controller streams and callbacks
  CtrlMIDI.Init(&MIDI_STREAM, MIDI_CHANNEL, &Midi_OnReceiveCC, &Midi_OnReceivePC);
  CtrlZoom.Init(&ZOOM_STREAM, ZOOM_CHANNEL, &Zoom_OnReceiveCC, &Zoom_OnReceivePC);
  
  TimerStart = millis();
}


// MAIN LOOP FUNCTION
void loop() {
  // Update buffer
  while ((MIDI_STREAM.available() > 0) && CtrlMIDI.RxActive) {
    Mem.Push(MIDI_STREAM.read());
    
    CtrlMIDI.Update(&Mem);
    CtrlZoom.Update(&Mem);
  }
  
  // State check and sending routine
  if (CtrlMIDI.Done() && CtrlZoom.Done()) {
    Zoom_Tuner(&ZOOM_STREAM, ZOOM_CHANNEL, false);   // Tuner off message
    
    CtrlMIDI.OnSend(); CtrlZoom.OnSend();
    CtrlMIDI.Reset();  CtrlZoom.Reset();
    
    Mem.Flush();
  }

  // Tuner switch handling
  TimerCurrent = millis();
  if ((digitalRead(SWITCH_TUNER) != HIGH) && (TimerCurrent - TimerStart > SWITCH_DEB)) {
    Zoom_Tuner(&ZOOM_STREAM, ZOOM_CHANNEL, true);   // Tuner on message
    
    TimerStart = TimerCurrent;
  }
}
