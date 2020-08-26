///////////////////////////////////////
#define DEBUG false

#include <AltSoftSerial.h>

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

#define MIDI_SERIAL_RX 12
#define MIDI_SERIAL_TX 11

#define MIDI_BAUDRATE 31250
#define DEBUG_BAUDRATE 9600

#define SWITCH_DEB 1000
#define SWITCH_TUNER 14

#define CONTROL_BYTE 0xFF
#define CONTROL_FLUSH true

#define MIDI_STREAM MIDI_S
#define MIDI_CHANNEL 2

#define USB_STREAM Serial
#define USB_CHANNEL 1


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
bool RxPC1, RxPC2, RxActive;

AltSoftSerial MIDI_S = AltSoftSerial(MIDI_SERIAL_RX, MIDI_SERIAL_TX);


// MAIN INIT FUNCTION
void setup() {
  MIDI_S.begin(MIDI_BAUDRATE);          // MIDI In/Out
  MIDI_S.flush(); Serial.flush();
  
  #if DEBUG
    Serial.begin(DEBUG_BAUDRATE);       // Debug Out
  #else
    Serial.begin(MIDI_BAUDRATE);        // USB Host MIDI Out
  #endif
  
  pinMode(SWITCH_TUNER, INPUT_PULLUP);  // Tuner switch

  ResetState();
  TimerStart = millis();
}


// MAIN LOOP FUNCTION
void loop() {
  while ((MIDI_STREAM.available() > 0) && RxActive) {
    Mem3.Push(MIDI_STREAM.read());
    
    if (Mem3.CCTerm(1))   RxTermCC1 = true;
    if (Mem3.CCNorm(1)) { RxNormCC1 = true; CN1 = Mem3.Data[1]; CV1 = Mem3.Data[2]; }
    
    if (Mem3.CCTerm(2))   RxTermCC2 = true;
    if (Mem3.CCNorm(2)) { RxNormCC2 = true; CN2 = Mem3.Data[1]; CV2 = Mem3.Data[2]; }

    if (!RxPC1) {
      PN1 = Mem3.PC(1);
      if (PN1 < CONTROL_BYTE) RxPC1 = true; }
    
    if (!RxPC2) {
      PN2 = Mem3.PC(2);
      if (PN2 < CONTROL_BYTE) RxPC2 = true; }
  }
  

  // STATE CHECK & SENDING ROUTINE
  if (StateMachine()) {
    MidiOutCC(&USB_STREAM, 1, 0x4A, 0x00);   // Tuner off message

    if (RxNormCC1) OnReceiveCC(&USB_STREAM, USB_CHANNEL, CN1, CV1);
    if (RxPC1)     OnReceivePC(&USB_STREAM, USB_CHANNEL, PN1);
    
    if (RxNormCC2) OnReceiveCC(&MIDI_STREAM, MIDI_CHANNEL, CN2, CV2);
    if (RxPC2)     OnReceivePC(&MIDI_STREAM, MIDI_CHANNEL, PN2);

    ResetState();
    // TODO: start RxActive timer
  }
  
  
  // TUNER SWITCH HANDLING
  TimerCurrent = millis();
  if ((digitalRead(SWITCH_TUNER) != HIGH) && (TimerCurrent - TimerStart > SWITCH_DEB)) {
    MidiOutCC(&USB_STREAM, USB_CHANNEL, 0x4A, 0x7F);   // Tuner on message
    
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

void ResetState() {
  PN1 = 0; PN2 = 0;
  CN1 = 0; CN2 = 0;
  CV1 = 0; CV2 = 0;
  
  RxNormCC1 = false; RxTermCC1 = false; RxPC1 = false;
  RxNormCC2 = false; RxTermCC2 = false; RxPC2 = false;
  RxActive  = true;
  
  Mem3.Flush();
}


// SEND EVENTS
void OnReceivePC(Stream *Com, byte Channel, byte PN) {
  #if DEBUG
    Serial.println("");
    Serial.print("RX: Channel "); Serial.print(Channel, DEC); Serial.print(" PC ");
    Serial.println(PN, HEX);
  #endif

  if (PN < 50) MidiOutPC(Com, Channel, PN);
  else {
    MidiOutPC(Com, Channel, PN); // TODO
  }
}

void OnReceiveCC(Stream *Com, byte Channel, byte CN, byte CV) {
  #if DEBUG
    Serial.println("");
    Serial.print("RX: Channel "); Serial.print(Channel, DEC); Serial.print(" CC ");
    Serial.print(CN, HEX);
    Serial.print(" ");
    Serial.println(CV, HEX);
  #endif
  
  MidiOutCC(Com, Channel, CN, CV);
}

// MIDI OUT FUNCTIONS
void MidiOutPC(Stream *Com, byte Channel, byte PN) {
  #if DEBUG
    Serial.println("");
    Serial.print("TX: Channel "); Serial.print(Channel, DEC); Serial.print(" PC ");
    Serial.println(PN, HEX);
  #endif
  
  Com->write(0xC0 + Channel - 1);
  Com->write(PN);
}

void MidiOutCC(Stream *Com, byte Channel, byte CN, byte CV) {
  #if DEBUG
    Serial.println("");
    Serial.print("TX: Channel "); Serial.print(Channel, DEC); Serial.print(" CC ");
    Serial.print(CN, HEX);
    Serial.print(" ");
    Serial.println(CV, HEX);
  #endif
  
  Com->write(0xB0 + Channel - 1);
  Com->write(CN);
  Com->write(CV);
}

void ZoomParamEnable() {
  Serial.write(0xF0);
  Serial.write(0x52);
  Serial.write(0x00);
  Serial.write(0x58);
  Serial.write(0x50);
  Serial.write(0xF7);
}
void ZoomParamDisable() {
  Serial.write(0xF0);
  Serial.write(0x52);
  Serial.write(0x00);
  Serial.write(0x58);
  Serial.write(0x51);
  Serial.write(0xF7);
}
void ZoomSwitchOn(byte Slot)
{
  unsigned char v = 1;
  
  Serial.write(0xF0);
  Serial.write(0x52);
  Serial.write(0x00);
  Serial.write(0x58);
  Serial.write(0x31);
  Serial.write(Slot - 1);
  Serial.write(0x00);
  Serial.write(0x01); // Serial.write(v & 0x7F);
  Serial.write(0x00); // Serial.write((v>>7) & 0x7F);
  Serial.write(0xF7);
}
void ZoomSwitchOff(byte Slot)
{
  unsigned char v = 0;
  
  Serial.write(0xF0);
  Serial.write(0x52);
  Serial.write(0x00);
  Serial.write(0x58);
  Serial.write(0x31);
  Serial.write(Slot - 1);
  Serial.write(0x00);
  Serial.write(0x00); // Serial.write(v & 0x7F);
  Serial.write(0x00); // Serial.write((v>>7) & 0x7F);
  Serial.write(0xF7);
}

// DEBUG FUNCTIONS
void Log(byte x)    { Serial.write(x); }
void Log(int x)     { Serial.write(x); }
