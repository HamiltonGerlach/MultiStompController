#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

#include "MultistompController.h"

#include "Controller.h"
#include "MidiBuffer.h"
#include "Timer.h"
#include "ZoomIf.h"


// GLOBALS
Controller CtrlMIDI, CtrlZoom;
AltSoftSerial  MIDI_STREAM = AltSoftSerial (MIDI_SERIAL_RX, MIDI_SERIAL_TX);
SoftwareSerial ZOOM_STREAM = SoftwareSerial(ZOOM_SERIAL_RX, ZOOM_SERIAL_TX);


// MAIN INIT FUNCTION
void setup() {
  pinMode(SWITCH_TUNER, INPUT_PULLUP); // Tuner switch
  
  MIDI_STREAM.begin(MIDI_BAUDRATE);    // MIDI In/Out
  MIDI_STREAM.flush();
  
  ZOOM_STREAM.begin(ZOOM_BAUDRATE);    // USB Host MIDI Out
  ZOOM_STREAM.flush();

  #if DEBUG
  Serial.begin(DEBUG_BAUDRATE);        // Debug Out
  #endif
  
  // Setup controller streams and callbacks
  CtrlMIDI.Init(&MIDI_STREAM, MIDI_CHANNEL, &Midi_OnReceiveCC, &Midi_OnReceivePC);
  CtrlZoom.Init(&ZOOM_STREAM, ZOOM_CHANNEL, &Zoom_OnReceiveCC, &Zoom_OnReceivePC);
  ZoomIf::Init(&ZOOM_STREAM, ZOOM_CHANNEL);
}

int Slot = 0;
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
    //ZoomIf::Tuner(true);    // Tuner on message
    
    //// DEBUG
    #if DEBUG
      bool Vector[6] = {rndbool(), rndbool(), rndbool(), rndbool(), rndbool(), rndbool()};
      byte Mask = ZoomIf::StateMask(Vector);
      Serial.println(Slot);
      Serial.println(Slot, BIN);
      ZoomIf::SetPatchEffects(0, Mask, Slot++);
      if (Slot > 5) Slot = 0;
      //Serial.println(Slot);
      //ZoomIf::SwitchOn(0, 4, Slot);
      //Slot++;
      //ZoomIf::SwitchOff(0, 4);
    #endif
    //// DEBUG
    
    Timer::Reset();
  }

  
  #if DEBUG
    while (ZOOM_STREAM.available() > 0) Serial.write(ZOOM_STREAM.read());
  #endif
}
