**MultiStompController** - a compact MIDI converter that receives MIDI data from the MOEN GEC5 loop switcher (or other MIDI sources) and translates it into separate MIDI outputs for the Zoom MS-50G Multistomp (via MIDI-USB) and the Strymon Iridium or any other MIDI device (via MIDI-EXP).


Resources used:

- Arduino Nano v4 compatible
    https://www.hobbytronics.co.uk/arduino-compatable-nano-v4


- USBHost v2.4 (preloaded with MIDI Device firmware)
    https://www.hobbytronics.co.uk/usb-host-board-v24


- MIDI breakout board
    https://www.hobbytronics.co.uk/audio-midi/midi-breakout


- DPDT momentary switch for tuner control


Wiring instructions:

- Connect [VIN, GND] of Arduino to 9V DC (careful, center negative).

- Connect [5V, GND] on USBHost and MIDI breakout board to [5V, GND] on Arduino.

- Connect TX of Arduino to RX on USBHost (HardwareSerial).

- Connect MIDI In on MIDI breakout board to D09 (Pin 12) on Arduino (AltSoftSerial RX).

- Connect MIDI Out on MIDI breakout board to D08 (Pin 11) on Arduino (AltSoftSerial TX).

- Connect DPDT switch to [A0, GND] on Arduino.



Connection instructions:

- Connect MIDI In to the MOEN GEC5 loop switcher (or other).

- Connect MIDI Out to the Strymon Iridium (or other).

- Connect USBHost to the Zoom Multistomp.


Prototype images:

![Overview 1](https://github.com/HamiltonGerlach/MultiStompController/blob/master/doc/images/Overview1.jpg)
![Overview 2](https://github.com/HamiltonGerlach/MultiStompController/blob/master/doc/images/Overview2.jpg)


