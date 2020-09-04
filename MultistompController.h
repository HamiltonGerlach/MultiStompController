#ifndef MULTISTOMPCONTROLLER_H
#define MULTISTOMPCONTROLLER_H

#include "ZoomMsg.h"

#define DEBUG false

#define Z_ID ZOOM_DEVICE_MS50G

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

// Array / bit helper macros
#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))
#define ARRAY_FILL(array, len, in) for (int i = 0; i < len; i++) array[i] = in

#define BIT_SET(arg, bit) arg |= (1 << bit)
#define BIT_CLR(arg, bit) arg &= ~(1 << bit)
#define BIT_FLIP(arg, bit) arg ^= (1 << bit)
#define BIT_CHECK(arg, bit) ((!!((arg) & (1 << (bit)))) == 1)

#define BITMASK_SET(arg, mask) arg |= mask
#define BITMASK_CLEAR(arg, mask) arg &= (~mask)
#define BITMASK_FLIP(arg, mask) arg ^= mask
#define BITMASK_CHECK_ALL(arg, mask) !~((~(mask)) | (arg))
#define BITMASK_CHECK_ANY(arg, mask) ((arg) & (mask))

#define rndbool() (((byte)random(0, 2) == 1) ? true : false)

#endif