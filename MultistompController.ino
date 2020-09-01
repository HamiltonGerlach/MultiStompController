#define DEBUG true

#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

#include "MultistompController.h"

#include "Array.h"
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

  Serial.begin(DEBUG_BAUDRATE);

  // Setup controller streams and callbacks
  CtrlMIDI.Init(&MIDI_STREAM, MIDI_CHANNEL, &Midi_OnReceiveCC, &Midi_OnReceivePC);
  CtrlZoom.Init(&ZOOM_STREAM, ZOOM_CHANNEL, &Zoom_OnReceiveCC, &Zoom_OnReceivePC);
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
    ZoomIf::Tuner(false);   // Tuner off message

    CtrlMIDI.OnSend(); CtrlZoom.OnSend();
    CtrlMIDI.Reset();  CtrlZoom.Reset();

    MidiBuffer::Flush();
  }

  // Tuner switch handling
  if ((digitalRead(SWITCH_TUNER) != HIGH) && Timer::Check(SWITCH_DEB)) {
    ZoomIf::Tuner(true);   // Tuner on message

    #if DEBUG
      Array<byte, ZOOM_PATCH_LENGTH> PatchTmp;

      //// DEBUG PATCH REQUEST
      
      for (int i = 0; i < 50; i++)
      {
        PatchTmp = ZoomIf::RequestPatch(i);
        
        #if ZOOM_SRAM_MEM
          if (i < ZOOM_SRAM_PATCHES)
          {
            for (int j = 0; j < ZOOM_PATCH_LENGTH; j++)
              ZoomIf::PatchMem[i][j] = PatchTmp[j];
          }
        #endif
        
        #if DEBUG
          Serial.write(PatchTmp.data, ZOOM_PATCH_LENGTH);
          Serial.println("");
        #endif
      }
  
      for (int i = 0; i < ZOOM_SRAM_PATCHES; i++)
      {
        Serial.write(ZoomIf::PatchMem[i], ZOOM_PATCH_LENGTH);
        Serial.println("");
      }
    #endif

    //// DEBUG PATCH REQUEST
    
    Timer::Reset();
  }
}
