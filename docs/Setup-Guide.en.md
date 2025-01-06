# ESP32 Wireless Fireworks Ignition System 

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/brugernavn/repository)

## Introduction

This manual provides a step-by-step guide to building a wireless fireworks ignition system using an ESP32, a relay module, nichrome wire, and other necessary components. **WiFiFyr** is open source and designed to be user-friendly, even for those with limited knowledge of electronics. Follow the instructions carefully to ensure a safe and functional setup.

## Table of Contents

1. [Materials](#materials)
2. [Preparation](#preparation)
3. [Hardware Setup](#hardware-setup)
    - [Connecting the Relay Module](#connecting-the-relay-module)
    - [Setting Up Nichrome Wire](#setting-up-nichrome-wire)
    - [Connecting the LED (Optional)](#connecting-the-led-optional)
4. [Software Configuration](#software-configuration)
    - [Installing Arduino IDE and ESP32 Board](#installing-arduino-ide-and-esp32-board)
    - [Uploading the Code](#uploading-the-code)
5. [Wi-Fi Setup](#wifi-setup)
6. [Testing and Validation](#testing-and-validation)
    - [Test Mode](#test-mode)
    - [Firing Channels](#firing-channels)
    - [Monitoring Signal Strength and Delay](#monitoring-signal-strength-and-delay)
7. [Safety Tips](#safety-tips)
8. [Troubleshooting](#troubleshooting)
    - [Connection Issues](#connection-issues)
    - [Code Upload Errors](#code-upload-errors)
    - [Relays Not Activating](#relays-not-activating)
    - [LED Not Blinking](#led-not-blinking)
9. [Material Links](#material-links)
10. [Contributing and License](#contributing-and-license)

---

## Materials

### Main Components

| Component                 | Description                                     | Link                  |
|---------------------------|-------------------------------------------------|-----------------------|
| **ESP32 Development Board** | Wi-Fi and Bluetooth capable microcontroller    | [Buy here](#)           |
| **Relay Module**             | 4-channel relay module recommended              | [Buy here](#)           |
| **Nichrome Wire**          | 0.1mm for E-matches                              | [Buy here](#)           |
| **E-match Wires**     | Connection to E-matches                        | [Buy here](#)           |
| **12V Battery**           | At least 6A capacity to power the system        | [Buy here](#)           |
| **LED with Resistor**      | Indicator LED (if necessary)                    | [Buy here](#)           |
| **Jumper Wires**           | Male-to-male and male-to-female jumper wires    | [Buy here](#)           |
| **Breadboard**            | For prototyping and connections                  | [Buy here](#)           |
| **DC-DC Stepdown Module**  | To ensure correct voltage for components         | [Buy here](#)           |

---

## Preparation

Before you begin, ensure you have all the materials ready and a workspace that is well-ventilated and free of flammable materials.

---

## Hardware Setup

### Connecting the Relay Module

1. **Connect the Relay Module to the ESP32:**
    - **IN1** → GPIO 4
    - **IN2** → GPIO 5
    - **IN3** → GPIO 18
    - **IN4** → GPIO 19

2. **Connect the Relay Module to the 12V Battery:**
    - **VCC** → **+12V** terminal on the battery
    - **GND** → **Common GND** terminal

3. **Connect the ESP32 to the Common GND:**
    - **ESP32 GND** → Common GND terminal

    **Note:** It is crucial that the ESP32’s GND is connected to the same common GND terminal used by the battery and relay module to ensure that control signals from the ESP32 are correctly interpreted by the relay module.

### Setting Up Nichrome Wire

1. Cut appropriate lengths of nichrome wire (3-5 cm recommended per E-match).
2. Connect the nichrome wire to the E-match wires.
3. Secure the E-match wires to the relay module's output terminals.
4. **Safety:** Ensure that the relay circuit is powered by your 12V battery, which can deliver at least 6A.

### Connecting the LED (Optional)

1. If your ESP32 does not have an onboard LED, you can connect an external LED:
    - **GPIO 2** → LED with an appropriate resistor.

    This provides a visual indication of the system's status, such as test mode.

---

## Software Configuration

### Installing Arduino IDE and ESP32 Board

1. **Download and Install Arduino IDE:** [Arduino IDE Download](https://www.arduino.cc/en/software)
2. **Add ESP32 Board to Arduino IDE:**
    - Open Arduino IDE.
    - Go to **File > Preferences**.
    - Add the following URL to **Additional Board Manager URLs**:
      ```
      https://dl.espressif.com/dl/package_esp32_index.json
      ```
    - Go to **Tools > Board > Board Manager**.
    - Search for **ESP32** and install the package.

### Uploading the Code

1. **Copy the Code:**
    - Copy the code from this manual into a new Arduino sketch in Arduino IDE.
2. **Select the Correct Board and Port:**
    - Go to **Tools > Board** and select your ESP32 board.
    - Go to **Tools > Port** and select the correct COM port.
3. **Upload the Code:**
    - Click the **Upload** button and wait for the code to be flashed to the ESP32.
4. **Open Serial Monitor:**
    - Go to **Tools > Serial Monitor**.
    - Select baud rate **115200**.
    - You should see the following messages:
      ```
      Wi-Fi started
      Access Point IP: 192.168.4.1
      HTTP server started
      ```

---

## Wi-Fi Setup

1. **Connect to ESP32's Wi-Fi:**
    - On your phone or computer, find the Wi-Fi network **WiFiFyr**.
    - Enter the password **password123**.

2. **Customize Network Name and Password:**
    - Open your Arduino sketch and find the following lines:
      ```cpp
      const char* ssid = "WiFiFyr";
      const char* password = "password123";
      ```
    - Change **"WiFiFyr"** to your desired network name.
    - Change **"password123"** to a secure password to prevent unauthorized access to your Wi-Fi.

3. **Open the Web Interface:**
    - Open a browser and navigate to: [http://192.168.4.1](http://192.168.4.1)

---

## Testing and Validation

### Test Mode

1. **Enable Test Mode:**
    - In the web interface, check the **"Enable Test Mode"** checkbox.
2. **Test the LED:**
    - Click the firing buttons for channels **1, 2, 3, 4** to make the LED blink.

### Firing Channels

1. **Disable Test Mode:**
    - Uncheck the **"Enable Test Mode"** checkbox.
2. **Fire E-matches:**
    - Click the desired firing buttons to activate the relays and ignite the E-matches.

### Monitoring Signal Strength and Delay

- The web interface displays **RSSI** (signal strength) and **delay** (ms) in real-time, helping to optimize the system's performance.

---

## Safety Tips

1. **Use a Proper Power Supply:**
    - A **12V battery** with at least **6A** current is recommended for stable operation of the relay module and nichrome wire.
2. **Handle Nichrome Wire Carefully:**
    - Nichrome wire becomes very hot during use. Ensure it does not come into contact with flammable materials.
3. **Test the System Before Using Fireworks:**
    - Use test mode to ensure everything functions correctly before connecting and firing fireworks.
4. **Safe Setup of Fireworks:**
    - Place E-matches and fireworks securely away from people and flammable surfaces.
5. **Monitor the System During Firing:**
    - Stay present and monitor the system's operation during firing to quickly respond to any issues.

---

## Troubleshooting

### Connection Issues

- **WiFiFyr Does Not Connect to Wi-Fi:**
  - Check that WiFiFyr is properly connected to power and the relay module.
  - Ensure that the SSID and password are correctly set in the code.

### Code Upload Errors

- **Errors During Upload:**
  - Ensure the correct board and port are selected in Arduino IDE.
  - Restart WiFiFyr and try again.

### Relays Not Activating

- **Relays Are Not Activating:**
  - Check all connections between WiFiFyr and the relay module.
  - Ensure that the battery is supplying sufficient power.

### LED Not Blinking

- **LED Does Not Blink in Test Mode:**
  - Check the connection between WiFiFyr’s GPIO 2 and the LED.
  - Ensure the resistor is correctly connected.

---

## Material Links

- **ESP32 Development Board (Wi-Fi):** [Buy here](#)
- **Relay Module (4 channels or more):** [Buy here](#)
- **Nichrome Wire (0.1mm):** [Buy here](#)
- **E-match Wires (minimum 20AWG):** [Buy here](#)
- **DC-DC Stepdown Module (3-12V):** [Buy here](#)
- **Breadboard:** [Buy here](#)
- **Male-to-Male Jumper Wires (10 pcs):** [Buy here](#)
- **Male-to-Female Jumper Wires (10 pcs):** [Buy here](#)

---

## Contributing and License

This project is open source and welcomes contributions from the community. If you wish to contribute, follow these steps:

1. Fork the project on GitHub.
2. Make your changes in a new branch.
3. Open a pull request with a description of your changes.

The project is licensed under the **MIT License**, which means you are free to use, modify, and distribute it.

---

**Note:** Always work safely and responsibly when handling electronics and fireworks. Follow local laws and regulations regarding the use of fireworks.
