// ZOOM SYSTEM MESSAGES
void Zoom_ParamEnable(Stream *Com) {
  byte Msg[] = ZOOM_MSG_PRM_ENA;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_ParamDisable(Stream *Com) {
  byte Msg[] = ZOOM_MSG_PRM_DEA;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_SwitchOn(Stream *Com, byte Slot)
{
  byte Msg[] = ZOOM_MSG_EFF_ON;
  
  Msg[5] = Slot - 1;  
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_SwitchOff(Stream *Com, byte Slot)
{
  byte Msg[] = ZOOM_MSG_EFF_OFF;
  
  Msg[5] = Slot - 1;
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_ParamEdit(Stream *Com, byte Slot, byte Param, int Value)
{
  byte Msg[] = ZOOM_MSG_PRM_EDIT;
  
  Msg[5] = Slot - 1;
  Msg[6] = Param + 0x01;
  Msg[7] = Value & 0x7F;      // 7 bit LSB
  Msg[8] = (Value>>7) & 0x7F; // 7 bit MSB
  
  Com->write(Msg, ARRAY_SIZE(Msg));
}

void Zoom_Tuner(Stream *Com, byte Channel, bool State) {
  byte Value = State ? 0x7F : 0x00;
  MidiOutCC(Com, Channel, 0x4A, Value);
}