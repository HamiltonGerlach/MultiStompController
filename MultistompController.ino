#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

#include "MultistompController.h"
#include "MidiController.h"
#include "MidiBuffer.h"
#include "Timer.h"
#include "ZoomController.h"
#include "ZoomIf.h"


// GLOBALS
MidiController CtrlMIDI;
ZoomController CtrlZoom;

AltSoftSerial  MIDI_STREAM = AltSoftSerial (MIDI_SERIAL_RX, MIDI_SERIAL_TX);
SoftwareSerial ZOOM_STREAM = SoftwareSerial(ZOOM_SERIAL_RX, ZOOM_SERIAL_TX);


// MAIN INIT FUNCTION
void setup() {
  pinMode(SWITCH_TUNER, INPUT_PULLUP); // Tuner switch
  pinMode(SWITCH_UPDATE, INPUT_PULLUP); // Update switch
  
  MIDI_STREAM.begin(MIDI_BAUDRATE);    // MIDI In/Out
  MIDI_STREAM.flush();
  
  ZOOM_STREAM.begin(ZOOM_BAUDRATE);    // USB Host MIDI Out
  ZOOM_STREAM.flush();

  #if DEBUG
    Serial.begin(DEBUG_BAUDRATE);        // Debug Out
  #endif
  
  // Setup controller streams and callbacks
  CtrlMIDI.Init(&MIDI_STREAM, MIDI_CHANNEL);
  CtrlZoom.Init(&ZOOM_STREAM, ZOOM_CHANNEL);
  ZoomIf::Init(&ZOOM_STREAM, ZOOM_CHANNEL);
}


// MAIN LOOP FUNCTION
void loop() {
  // Update buffer
  while ((MIDI_STREAM.available() > 0) && CtrlMIDI.RxActive) {
    MidiBuffer::Push(MIDI_STREAM.read());
    
    CtrlMIDI.Update();
    CtrlZoom.Update();
  }


  // State check and sending routine
  if (CtrlMIDI.Done() && CtrlZoom.Done()) {
    ZoomIf::Tuner(false);     // Tuner off message
    
    CtrlMIDI.OnSend(); CtrlZoom.OnSend();
    CtrlMIDI.Reset();  CtrlZoom.Reset();
    
    MidiBuffer::Flush();
  }

  
  // Tuner switch handling
  if ((digitalRead(SWITCH_TUNER) != HIGH) && Timer::Check(SWITCH_DEB)) {
    bool TunerState = ZoomIf::TunerState ? false : true;
    
    ZoomIf::Tuner(TunerState);
    Timer::Reset();
  }
  

  // Update switch handling
  if ((digitalRead(SWITCH_UPDATE) != HIGH) && Timer::Check(SWITCH_DEB)) {
    ZoomIf::UpdatePatches();
    Timer::Reset();
  }
  
  // Handle input from Zoom
  ZoomIf::HandleInput();
}
