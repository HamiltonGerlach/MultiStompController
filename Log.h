#ifndef LOG_H
#define LOG_H

void Log(byte x);
void Log(int x);

void LogCC(char Direction, byte Channel, byte CN, byte CV);
void LogPC(char Direction, byte Channel, byte PN);

#endif