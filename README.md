**MultiStompController** - a compact MIDI converter that receives MIDI data from the MOEN GEC5 loop switcher (or other MIDI sources) and translates it into separate MIDI outputs for the Zoom MS-50G Multistomp (via MIDI-USB) and the Strymon Iridium or any other MIDI device (via MIDI-EXP).



Resources used:

- Arduino Nano v4 compatible
    https://www.hobbytronics.co.uk/arduino-compatable-nano-v4


- USBHost v2.4 (preloaded with MIDI Device firmware)
    https://www.hobbytronics.co.uk/usb-host-board-v24


- MIDI breakout board
    https://www.hobbytronics.co.uk/audio-midi/midi-breakout


- DPDT momentary switches for "Tuner" and "Update Patch" functions


- 24LC256 (32kb EEPROM) - optional, for flash memory storage of patches


Arduino libraries used:
- AltSoftSerial (https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html)

- SoftwareSerial

- EEPROMext (optional, for flash memory storage of patches)


Wiring instructions:

- Connect [VIN, GND] of Arduino to 9V DC (careful, center negative).

- Connect [5V, GND] on USBHost and MIDI breakout board to [5V, GND] on Arduino.

- Connect RX on USBHost to D02 (Pin 5) on Arduino (SoftwareSerial TX).

- Connect TX on USBHost to D03 (Pin 6) on Arduino (SoftwareSerial RX).

- Connect MIDI In on MIDI breakout board to D09 (Pin 12) on Arduino (AltSoftSerial RX).

- Connect MIDI Out on MIDI breakout board to D08 (Pin 11) on Arduino (AltSoftSerial TX).

- Connect DPDT "Tuner" switch to [A0, GND] on Arduino.

- Connect DPDT "Update Patch" switch to [A1, GND] on Arduino.

Optional, for flash memory storage of patches: 

- Connect [5V, GND] on 24LC256 to [5V, GND] on Arduino.

- Connect [SDA, SCL] on 24LC256 to [SDA, SCL] on Arduino (see https://www.lehelmatyus.com/691/sda-scl-arduino-nano-connecting-i2c-devices-arduino-nano and further https://www.hobbytronics.co.uk/tutorials-code/arduino-tutorials/arduino-external-eeprom).


Connection instructions:

- Connect MIDI In to the MOEN GEC5 loop switcher (or other).

- Connect MIDI Out to the Strymon Iridium (or other).

- Connect USBHost to the Zoom Multistomp.






Customization / adaptation notes for other setups:

- MultistompController.ino contains the main program flow.

- MIDI In is collected via a static MidiBuffer, which feeds input to the Controllers.

- The main controller classes MidiController and ZoomController derive from the Controller class and define the output/through logic of the corresponding devices (i.e. how inputs are converted to outputs or passed through).

- These controllers must implement the events OnReceiveCC, OnReceivePC and OnResetCtrl. They may also override the default methods Update, OnSend and Reset.



Prototype images:

![Overview 1](https://github.com/HamiltonGerlach/MultiStompController/blob/master/doc/images/Overview1.jpg)
![Overview 2](https://github.com/HamiltonGerlach/MultiStompController/blob/master/doc/images/Overview2.jpg)

**Function table:**

![Functions](https://github.com/HamiltonGerlach/MultiStompController/blob/master/doc/images/Functions.png)


Thanks to g200kg whose work on https://github.com/g200kg/zoom-ms-utility inspired this project.
