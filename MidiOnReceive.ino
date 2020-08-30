// SEND EVENTS

// Midi receive PC
void Midi_OnReceivePC(Stream *Com, byte Channel, byte PN) {
  #if DEBUG
    LogPC('R', Channel, PN)
  #endif
  
  MidiOutPC(Com, Channel, PN);
}

// Midi receive CC
void Midi_OnReceiveCC(Stream *Com, byte Channel, byte CN, byte CV) {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif
  
  MidiOutCC(Com, Channel, CN, CV);
}




