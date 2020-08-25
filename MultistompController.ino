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
#define CONTROL_FLUSH true


// CLASSES
class Buffer3 {
  public:
    byte Data[3];
    
    void Push(byte In) {
      Data[0] = Data[1];
      Data[1] = Data[2];
      Data[2] = In;
    }

    bool CCBank(byte Channel) { 
      if ((Data[0] == (0xB0 + Channel - 1)) && (Data[1] == 0x00) && (Data[2] == 0x00))
        return true;
      else
        return false;
    }
    
    bool CCNorm(byte Channel) { 
      if ((Data[0] == (0xB0 + Channel - 1)) && (Data[1] <= 0x7F) && (Data[2] <= 0x7F) && (Data[1] > 0x00))
        return true;
      else
        return false;
    }
    
    bool CCTerm(byte Channel) { 
      if ((Data[0] == (0xB0 + Channel - 1)) && (Data[1] == 0x80) && (Data[2] == 0x80))
        return true;
      else
        return false;
    }
    
    byte PC(byte Channel) {
      byte Out = CONTROL_BYTE;
      
      if (  ((Data[0] == (0xC0 + Channel - 1)) && (Data[1] <= 0x7F)) ||
            ((Data[1] == (0xC0 + Channel - 1)) && (Data[2] <= 0x7F))   ) {
          if (Data[0] == (0xC0 + Channel - 1)) {
            Out = Data[1];
            Data[0] = CONTROL_BYTE;
            Data[1] = CONTROL_BYTE;
          }
          else {
            Out = Data[2];
            Data[1] = CONTROL_BYTE;
            Data[2] = CONTROL_BYTE;
          }
      }
      
      return Out;
    }

    void Flush() {
      byte B = CONTROL_FLUSH ? CONTROL_BYTE : 0;
      Data[0] = B; Data[1] = B; Data[2] = B;
    }
};


// GLOBALS
Buffer3 Mem3;

unsigned long TimerStart, TimerCurrent;

byte PN1, PN2, CN1, CV1, CN2, CV2;
bool RxNormCC1, RxNormCC2, RxTermCC1, RxTermCC2;
bool RxBankCC1, RxBankCC2, RxPC1, RxPC2, RxActive;

AltSoftSerial MIDI_S = AltSoftSerial(MIDI_SERIAL_RX, MIDI_SERIAL_TX);



// MAIN INIT FUNCTION
void setup() {
  MIDI_S.setTimeout(MIDI_IN_TIMEOUT);   // MIDI In Timeout
  MIDI_S.begin(MIDI_BAUDRATE);          // MIDI In/Out

  MIDI_S.flush(); Serial.flush();
  
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
    Mem3.Push(MIDI_S.read());
    
    if (Mem3.CCBank(1)) RxBankCC1 = true;
    if (Mem3.CCTerm(1)) RxTermCC1 = true;
    if (Mem3.CCNorm(1)) { RxNormCC1 = true; CN1 = Mem3.Data[1]; CV1 = Mem3.Data[2]; }
      
    if (Mem3.CCBank(2)) RxBankCC2 = true;
    if (Mem3.CCTerm(2)) RxTermCC2 = true;
    if (Mem3.CCNorm(2)) { RxNormCC2 = true; CN2 = Mem3.Data[1]; CV2 = Mem3.Data[2]; }

    if (!RxPC1)
    {
      PN1 = Mem3.PC(1);
      if (PN1 < CONTROL_BYTE) RxPC1 = true;
    }

    if (!RxPC2)
    {
      PN2 = Mem3.PC(2);
      if (PN2 < CONTROL_BYTE) RxPC2 = true;
    }
  }


  // STATE CHECK & SENDING ROUTINE
  if (StateMachine()) {
    MidiOutCC2(0x4A, 0x00);   // Tuner off message

    if (RxNormCC1) OnReceiveCC1(CN1, CV1);
    if (RxPC1)     OnReceivePC1(PN1);
    
    if (RxNormCC2) OnReceiveCC2(CN2, CV2);
    if (RxPC2)     OnReceivePC2(PN2);

    ResetMessageData();
    
    // TODO: start RxActive timer
    // --> disable RX temporarily after receiving complete message
  }
  
  
  // TUNER SWITCH HANDLING
  TimerCurrent = millis();
  if ((digitalRead(SWITCH_TUNER) != HIGH) && (TimerCurrent - TimerStart > SWITCH_DEB)) {
    MidiOutCC2(0x4A, 0x7F);   // Tuner on message
    TimerStart = TimerCurrent;
  }

}


// AUXILIARY FUNCTIONS
bool StateMachine() {
  if ((RxNormCC1 || RxTermCC1) && (RxNormCC2 || RxTermCC2))
    return true;
  else
    return false;
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
  RxActive  = true;
  
  Mem3.Flush();
}


// SEND EVENTS
void OnReceivePC1(byte PN) {
  #if DEBUG
    Serial.println("");
    Serial.print("TX: Channel 1 PC ");
    Serial.println(PN, HEX);
  #endif
  
  MidiOutPC1(PN);
}
void OnReceivePC2(byte PN) {
  #if DEBUG
    Serial.println("");
    Serial.print("TX: Channel 2 PC ");
    Serial.println(PN, HEX);
  #endif
  
  MidiOutPC2(PN);
}

void OnReceiveCC1(byte CN, byte CV) {
  #if DEBUG
    Serial.println("");
    Serial.print("TX: Channel 1 CC ");
    Serial.print(CN, HEX);
    Serial.print(" ");
    Serial.println(CV, HEX);
  #endif
  
  MidiOutCC1(CN, CV);
}
void OnReceiveCC2(byte CN, byte CV) {
  #if DEBUG
    Serial.println("");
    Serial.print("TX: Channel 2 CC ");
    Serial.print(CN, HEX);
    Serial.print(" ");
    Serial.println(CV, HEX);
  #endif
  
  MidiOutCC2(CN, CV);
}


// MIDI OUT FUNCTIONS
void MidiOutPC1(byte pn) {
  MIDI_S.write(0xC0);
  MIDI_S.write(pn);
}
void MidiOutPC2(byte pn) {
  Serial.write(0xC0);
  Serial.write(pn);
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
void Log(byte x)    { Serial.write(x); }
void Log(int x)     { Serial.write(x); }
