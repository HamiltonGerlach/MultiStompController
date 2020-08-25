///////////////////////////////////////
#define DEBUG true     // DEBUG MODE //
///////////////////////////////////////

#include <AltSoftSerial.h>

#define MIDI_SERIAL_RX 12
#define MIDI_SERIAL_TX 11

#define MIDI_IN_TIMEOUT 99999999
#define MIDI_BAUDRATE 31250
#define DEBUG_BAUDRATE 9600

#define SWITCH_DEB 1000
#define SWITCH_TUNER 14

#define BUFFER_LENGTH 16

#define CONTROL_BYTE 0xFF


// CLASSES
class List {
public:
    byte length = 0;
    byte data[BUFFER_LENGTH];
    
    void Append(byte item) {
      if (length < BUFFER_LENGTH) data[length++] = item;
    }
    
    void Remove(byte index) {
      if (index >= length) return;
      memmove(&data[index], &data[index+1], length - index - 1);
      length--;
    }
    
    byte Get(byte index) {
      if (index >= length) index = length; // clamp index
      return data[index];
    }

    byte GetLast() { return data[length]; }
    
    byte GetLast(byte index) {
      byte pos = length - index;
      if (pos < 0) pos = 0; // clamp index
      return data[pos];
    }
    
    void Flush(bool Control) {
      byte B = Control ? CONTROL_BYTE : 0;
      for (int i = 0; i < BUFFER_LENGTH; i++) data[i] = B;
      length = 0;
    }
};


// GLOBALS
List Buffer;

unsigned long TimerStart, TimerCurrent;

byte FlowBuffer[3] = {0, 0, 0}, FlowBufferPos = 0;

byte PN1, PN2, CN1, CV1, CN2, CV2;

bool Receiving, Sending, RxBankCC1, RxBankCC2;
bool RxNormCC1, RxNormCC2, RxTermCC1, RxTermCC2;
bool RxPC1, RxPC2, RxActive; // disable RX temporarily after receiving complete message

AltSoftSerial MIDI_S = AltSoftSerial(MIDI_SERIAL_RX, MIDI_SERIAL_TX);





// MAIN INIT FUNCTION
void setup() {
  MIDI_S.setTimeout(MIDI_IN_TIMEOUT);   // MIDI In Timeout
  MIDI_S.begin(MIDI_BAUDRATE);          // MIDI In/Out

  #if DEBUG
    Serial.begin(DEBUG_BAUDRATE);         // Debug Out
  #else
    Serial.begin(MIDI_BAUDRATE);        // USB Host MIDI Out
  #endif
  
  pinMode(SWITCH_TUNER, INPUT_PULLUP);  // Tuner switch

  ResetMessageData();
  TimerStart = millis();
}


// MAIN LOOP FUNCTION
void loop() {
  while ((MIDI_S.available() > 0) && RxActive) {
    Buffer.Append(MIDI_S.read()); Receiving = true;
  }

  Sending = CheckBuffer();
  
  if (Sending) {
    #if DEBUG
      // DEBUG
    #else
      MidiOutCC2(0x4A, 0x00);   // Tuner off message

      if (RxNormCC1) OnReceiveCC1(CN1, V1);
      if (RxPC1)     OnReceivePC1(PN1);
      
      if (RxNormCC2) OnReceiveCC2(CN2, V2);
      if (RxPC2)     OnReceivePC2(PN2);
    #endif
    
    Sending = false;
  }

  TimerCurrent = millis();
  
  
  #if DEBUG
    if (Receiving) {
      Serial.println(micros());
      for (int i = 0; i < Buffer.length; i++)
        Serial.println(Buffer.Get(i), HEX);
      Receiving = false;
    }
  #endif
  
  
  // TUNER SWITCH HANDLING
  if ((digitalRead(SWITCH_TUNER) != HIGH) && (TimerCurrent - TimerStart > SWITCH_DEB)) {
    #if DEBUG
      Log(Buffer.GetLast());
    #else
      MidiOutCC2(0x4A, 0x7F);   // Tuner on message
    #endif
    
    TimerStart = TimerCurrent;
  }

}


// AUXILIARY FUNCTIONS
bool CheckBuffer() {
  
}


void ResetMessageData() {
  PN1 = 0; PN2 = 0;
  CN1 = 0; CN2 = 0;
  CV1 = 0; CV2 = 0;
  
  RxBankCC1 = false;
  RxNormCC1 = false;
  RxTermCC1 = false;
  RxPC1     = false;
  
  RxBankCC2 = false;
  RxNormCC2 = false;
  RxTermCC2 = false;
  RxPC2     = false;

  Receiving = false;
  Sending   = false;
  
  RxActive  = true;

  Buffer.Flush(false);
}


// SEND EVENTS
void OnReceivePC1(byte PN) {
  MidiOutPC1(PN);
}
void OnReceivePC2(byte PN) {
  MidiOutPC2(PN);
}

void OnReceiveCC1(byte CN, byte CV) {
  MidiOutCC1(CN, CV);
}
void OnReceiveCC2(byte CN, byte CV) {
  MidiOutCC2(CN, CV);
}


// MIDI OUT FUNCTIONS
void MidiOutPC1(byte pc) {
  MIDI_S.write(0xC0);
  MIDI_S.write(pc);
}
void MidiOutPC2(byte pc) {
  Serial.write(0xC0);
  Serial.write(pc);
}

void MidiOutCC1(byte cn, byte cv) {
  MIDI_S.write(0xB0);
  MIDI_S.write(cn);
  MIDI_S.write(cv);
}
void MidiOutCC2(byte cn, byte cv) {
  Serial.write(0xB0);
  Serial.write(cn);
  Serial.write(cv);
}


// DEBUG FUNCTIONS
void Log(byte x) { Serial.write(x); }
void Log(int x)  { Serial.write(x); }
