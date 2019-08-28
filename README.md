# ArduinoSerialInstrumentSimulator
> Using Arduino and ESP32 for serial instrument integration

## Table of Contents

- [Installation](#installation)
- [Features](#features)
- [Contributing](#contributing)
- [FAQ](#faq)
- [Support](#support)

## Instalation

### Clone

- Clone this repo to your local machine using `https://github.com/kanekomarcel/ArduinoSerialInstrumentSimulator` or copy the desired files directly from this portal 

### Setup

- Open the desired .ino file on Arduino IDE and upload it to your thing.

## Features

This project contains folders for: 

### <a href="https://github.com/kanekomarcel/ArduinoSerialInstrumentSimulator/tree/master/SerialInstrumentWithLCD">Arduino Serial Instrument Simulator
</a>

Tested on an Arduino Uno with a <a href="https://www.filipeflop.com/produto/display-lcd-shield-com-teclado-para-arduino/" target="blank">LCD Shield</a>

Simulates one instrument that can communicate via serial port and receive the following commands:
- Get Value (send "5"): Arduino responds with the current number being shown on the display

The LCD display has the following inputs:
- SELECT: randomizes current value
- LEFT: sets current value to 0.0
- RIGHT: sends current value to serial port

### <a href="https://github.com/kanekomarcel/ArduinoSerialInstrumentSimulator/tree/master/sketchSimpleWebServerESP32">ESP32 Simple Web Server </a>

Tested on a standard ESP32 Dev Module. 

Edit WIFI SSID and password to connect ESP32 to your network. 

Upload program using 115200 speed. Open Serial Monitor and start the ESP32. It will plot its IP.

Connect to the simulated instrument on Arduino via RX/TX 2 ports (16 and 17).

ESP32 will continuously send "5" to serial ports to get current value.

Access http://<ESP32_IP>/ to view current value.

## Contributing

Branch it!

## FAQ

- Under Construction

## Support

Leave a message at: https://github.com/kanekomarcel/ArduinoSerialInstrumentSimulator/issues
