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