#ifndef MULTISTOMPCONTROLLER_H
#define MULTISTOMPCONTROLLER_H

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

#define MIDI_SERIAL_RX 12
#define MIDI_SERIAL_TX 11

#define MIDI_BAUDRATE 31250
#define DEBUG_BAUDRATE 9600

#if DEBUG
  #define ZOOM_BAUDRATE DEBUG_BAUDRATE
#else
  #define ZOOM_BAUDRATE MIDI_BAUDRATE
#endif

#define SWITCH_DEB 1000
#define SWITCH_TUNER 14

#define CONTROL_BYTE 0xFF
#define CONTROL_FLUSH true

#define MIDI_STREAM MIDI_S
#define MIDI_CHANNEL 2

#define ZOOM_STREAM Serial
#define ZOOM_CHANNEL 1

#define ZOOM_MSG_50G_BEGIN  {0xF0, 0x52, 0x00, 0x58}
#define ZOOM_MSG_50G_END    {0xF7}
#define ZOOM_MSG_PC         {0xC0, 0x00}
#define ZOOM_MSG_TUNER_ON   {0xB0, 0x4A, 0x7F}
#define ZOOM_MSG_TUNER_OFF  {0xB0, 0x4A, 0x00}
#define ZOOM_MSG_PRM_ENA    {0xF0, 0x52, 0x00, 0x58, 0x50, 0xF7}
#define ZOOM_MSG_PRM_DEA    {0xF0, 0x52, 0x00, 0x58, 0x51, 0xF7}
#define ZOOM_MSG_EFF_ON     {0xF0, 0x52, 0x00, 0x58, 0x31, 0x00, 0x00, 0x01, 0x00, 0xF7}
#define ZOOM_MSG_EFF_OFF    {0xF0, 0x52, 0x00, 0x58, 0x31, 0x00, 0x00, 0x00, 0x00, 0xF7}
#define ZOOM_MSG_PRM_EDIT   {0xF0, 0x52, 0x00, 0x58, 0x31, 0x00, 0x00, 0x00, 0x00, 0xF7}

#endif