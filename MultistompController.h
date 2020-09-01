#ifndef MULTISTOMPCONTROLLER_H
#define MULTISTOMPCONTROLLER_H

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

#define SWITCH_DEB 1000
#define SWITCH_TUNER 14

#define CONTROL_BYTE 0xFF
#define CONTROL_FLUSH true

#define MIDI_BAUDRATE 31250
#define ZOOM_BAUDRATE 31250
#define DEBUG_BAUDRATE 115200

#define MIDI_STREAM MIDI_S
#define MIDI_CHANNEL 2

#define MIDI_SERIAL_RX 12
#define MIDI_SERIAL_TX 11

#define ZOOM_STREAM ZOOM_S
#define ZOOM_CHANNEL 1

#define ZOOM_SERIAL_RX 3
#define ZOOM_SERIAL_TX 2

#define ZOOM_SRAM_MEM true
#define ZOOM_SRAM_PATCHES 5

#endif