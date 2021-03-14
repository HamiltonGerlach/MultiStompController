#include "MultistompController.h"

#include "Log.h"
#include "MidiController.h"
#include "MidiBuffer.h"
#include "Timer.h"
#include "ZoomController.h"
#include "ZoomIf.h"


// GLOBALS
Timer Clock;

MidiController CtrlMIDI;
ZoomController CtrlZoom;

MIDI_SERIAL MIDI_STREAM = MIDI_SERIAL(MIDI_SERIAL_RX, MIDI_SERIAL_TX);
ZOOM_SERIAL ZOOM_STREAM = ZOOM_SERIAL(ZOOM_SERIAL_RX, ZOOM_SERIAL_TX);


// MAIN INIT FUNCTION
void setup() {
  pinMode(SWITCH_TUNER, INPUT_PULLUP); // Tuner switch
  pinMode(SWITCH_UPDATE, INPUT_PULLUP); // Update switch
  
  MIDI_STREAM.begin(MIDI_BAUDRATE);    // MIDI In/Out
  MIDI_STREAM.flush();
  
  ZOOM_STREAM.begin(ZOOM_BAUDRATE);    // USB Host MIDI Out
  ZOOM_STREAM.flush();

  DBEGIN(DEBUG_BAUDRATE);              // Debug Out
  
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
    
    CtrlMIDI.Update();   CtrlZoom.Update();
  }


  // State check and sending routine
  if (CtrlMIDI.Done() && CtrlZoom.Done()) {
    ZoomIf::Tuner(false);     // Tuner off message
    
    CtrlMIDI.OnSend();   CtrlZoom.OnSend();
    CtrlMIDI.Reset();    CtrlZoom.Reset();
    
    MidiBuffer::Flush();
  }

  
  // Tuner switch handling
  if ((digitalRead(SWITCH_TUNER) != HIGH) && Clock.Check(SWITCH_DEB)) {
    ZoomIf::Tuner(ZoomIf::TunerState ? false : true);
    Clock.Reset();
  }
  

  // Update switch handling
  if ((digitalRead(SWITCH_UPDATE) != HIGH) && Clock.Check(SWITCH_DEB)) {
    ZoomIf::UpdateCurrentPatch();
    Clock.Reset();
  }
  
  // Handle input from Zoom
  ZoomIf::HandleInput();
  
  // Invoke Iridium custom messages
  CtrlMIDI.Invoke();
}
