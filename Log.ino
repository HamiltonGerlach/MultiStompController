// DEBUG FUNCTIONS

void Log(byte x)    { Serial.write(x); }
void Log(int x)     { Serial.write(x); }

void LogCC(char Direction, byte Channel, byte CN, byte CV) {
  Serial.println("");
  Serial.print(Direction);
  Serial.print("X: Channel ");
  Serial.print(Channel, DEC);
  Serial.print(" CC ");
  Serial.print(CN, HEX);
  Serial.print(" ");
  Serial.println(CV, HEX);
}

void LogPC(char Direction, byte Channel, byte PN) {
  Serial.println("");
  Serial.print(Direction);
  Serial.print("X: Channel ");
  Serial.print(Channel, DEC);
  Serial.print(" PC ");
  Serial.println(PN, HEX);
}