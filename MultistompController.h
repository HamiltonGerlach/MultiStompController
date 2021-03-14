#ifndef MULTISTOMPCONTROLLER_H
#define MULTISTOMPCONTROLLER_H

#include <AltSoftSerial.h>
#include <SoftwareSerial.h>

#include "State.h"
#include "ZoomMsg.h"

// MAIN CONFIG
#define DEBUG true                  // serial debug flag, set to false for normal operation
#define Z_ID ZOOM_DEVICE_MS50G      // set to ZOOM_DEVICE_MS70CDR
                                          // (ZOOM_DEVICE_MS60B not implemented yet)
#define EEPROM_ENABLED true         // set to false if only using internal RAM
//

#if EEPROM_ENABLED
    #define EEPROM_ADDRESS 0x50
    #define EEPROM_CLOCK 400000
    #define EEPROM_PATCH_NUM 10
    #define MEM_PATCH_NUM EEPROM_PATCH_NUM
#else
    #define SRAM_PATCH_NUM 4
    #define MEM_PATCH_NUM SRAM_PATCH_NUM
#endif

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
#define MIDI_SERIAL AltSoftSerial

#define ZOOM_STREAM ZOOM_S
#define ZOOM_CHANNEL 1
#define ZOOM_SERIAL SoftwareSerial

#define ZOOM_SERIAL_RX 3
#define ZOOM_SERIAL_TX 2

#define MIDI_SERIAL_RX 12
#define MIDI_SERIAL_TX 11

#define ZOOM_INIT_TIMEOUT 1

#endif