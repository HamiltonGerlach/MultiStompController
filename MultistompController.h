#ifndef MULTISTOMPCONTROLLER_H
#define MULTISTOMPCONTROLLER_H

#include "State.h"
#include "ZoomMsg.h"

#define DEBUG true

#define Z_ID ZOOM_DEVICE_MS50G

#define EEPROM_ENABLED false
#define EEPROM_ADDRESS 0x50
#define EEPROM_CLOCK 400000
#define EEPROM_PATCH_NO 50

#if EEPROM_ENABLED
    #define ZOOM_MEM_MODE MemMode::SRAM | MemMode::EEPROM
#else
    #define ZOOM_MEM_MODE MemMode::SRAM
#endif

#define ZOOM_SRAM_PATCHES 4

#define SWITCH_DEB 1000
#define SWITCH_TUNER 14
#define SWITCH_UPDATE 15

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

#endif