# ESP32 Microarchitecture Projects

This repository contains various projects developed using the ESP32 microcontroller for a university course on microarchitecture. The projects are built using PlatformIO, a professional collaborative platform for embedded development.

## Table of Contents
- Introduction
- Prerequisites
- Projects
  - Project 1: Control LED via MQTT
  - Project 2: Light Control System

## Introduction
This repository showcases different microarchitecture projects implemented on the ESP32 development board. The projects demonstrate various functionalities such as GPIO control, sensor integration, and communication protocols.

## Prerequisites
- [PlatformIO](https://platformio.org/install)
- [Visual Studio Code](https://code.visualstudio.com/)
- [IoT MQTT Panel Android](https://play.google.com/store/apps/details?id=snr.lab.iotmqttpanel.prod&hl=en)
- [IoT MQTT Panel ios](https://apps.apple.com/pl/app/iot-mqtt-panel/id6466780124)
  
## Projects
### Project 1: Control LED via MQTT
This project demonstrates how to control an LED connected to the ESP32 using MQTT messages. 

<img src="https://github.com/khakestari/ESP32-Microarchitecture/assets/77167918/a53657d9-9d22-4b30-bb02-47f0ab23bd4f" alt="IoT MQTT Panel" width="200">
<img src="https://github.com/khakestari/ESP32-Microarchitecture/assets/77167918/6d05f700-1b7e-445c-a82d-5934e0dc2bec" alt="Off" width="200">
<img src="https://github.com/khakestari/ESP32-Microarchitecture/assets/77167918/a8734991-100f-4ac1-af6d-8455fb86229d" alt="On" width="200">

### Project 2: Light Control System with LDR
This project demonstrates a light control system using an ESP32 microcontroller, an LED, and a Light Dependent Resistor (LDR). The system can operate in two modes: manual and automatic. In manual mode, the LED can be turned on or off via MQTT messages. In automatic mode, the LED brightness is adjusted based on the LDR readings. Additionally, the LDR value is published to an MQTT broker for real-time monitoring on a phone app.

<img src="https://github.com/khakestari/ESP32-Microarchitecture/assets/77167918/9f49af14-9031-41a4-a64b-27f086b12cdf" alt="IoT MQTT Panel" width="200">
<img src="https://github.com/khakestari/ESP32-Microarchitecture/assets/77167918/41d607fe-7245-4ed8-a4de-15d1bc9f11e6" alt="Off" width="200">
<img src="https://github.com/khakestari/ESP32-Microarchitecture/assets/77167918/2cdea1c0-1b46-4a8f-ab15-a833cddd4f81" alt="On" width="200">

This project controls an LED connected to an ESP32 microcontroller. The system operates in two modes:
1. **Manual Mode:** The LED can be turned on or off via MQTT messages.
2. **Automatic Mode:** The LED brightness is adjusted based on the LDR readings, and the LDR value is published to the MQTT broker for monitoring.
