// SEND EVENTS

// Zoom/USB receive PC
void Zoom_OnReceivePC(Stream *Com, byte Channel, byte PN) {
  #if DEBUG
    LogPC('R', Channel, PN)
  #endif

  //if (PN < 50) MidiOutPC(Com, Channel, PN);
  //else {
    // TODO
  //}
}

// Zoom/USB receive CC
void Zoom_OnReceiveCC(Stream *Com, byte Channel, byte CN, byte CV) {
  #if DEBUG
    LogCC('R', Channel, CN, CV);
  #endif
  
  MidiOutCC(Com, Channel, CN, CV);
}