# Firework_Ignition_System
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/enput/Firework_Ignition_System)

[![Setup Guide EN](https://img.shields.io/badge/Setup%20Guide-English-blue)](https://github.com/enput/Firework_Ignition_System/blob/main/docs/Setup-Guide.en.md)
[![Setup Guide DA](https://img.shields.io/badge/Setup%20Guide-Danish-blue)](https://github.com/enput/Firework_Ignition_System/blob/main/docs/Setup-Guide.da.md)
[![Setup Guide DE](https://img.shields.io/badge/Setup%20Guide-German-blue)](https://github.com/enput/Firework_Ignition_System/blob/main/docs/Setup-Guide.de.md)

Welcome to the **Firework Ignition System** project! This is an innovative system designed to safely and wirelessly control firework ignitions using an ESP32 microcontroller. The system allows users to connect via Wi-Fi and execute commands for firing individual channels. It's built with user safety and functionality in mind, featuring test modes, connection monitoring, and a responsive web interface.

## Features

- **Wi-Fi Connectivity**: Connect to the ESP32 via a dedicated Wi-Fi network for seamless control.
- **User Interface**: A modern and intuitive web-based interface for managing firework ignition channels.
- **Test Mode**: Enable/disable test mode for safe and controlled testing of the system.
- **Status Monitoring**: Real-time connection status updates, Wi-Fi signal strength indicator, and delay measurements.
- **Multiple Channels**: Fire multiple channels individually for precise ignition control.
- **Responsive Design**: A web interface optimized for both desktop and mobile devices.

## How It Works

1. The ESP32 hosts a Wi-Fi network to which the user can connect.
2. Once connected, users access a web interface to monitor the system status and send commands.
3. Commands are sent via HTTP requests to the ESP32, which processes them to execute specific tasks (e.g., firing a channel or toggling test mode).
4. Safety features ensure controlled operation, including real-time feedback and test mode functionality.

## Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/enput/Firework_Ignition_System.git
   ```
2. Upload the firmware to your ESP32 and ensure your hardware setup matches the project's specifications.
3. Open the `index.html` file in your browser or serve it via a local server.
4. Connect to the ESP32 via the provided Wi-Fi network and start controlling your firework system!

## Future Improvements

- Integration with Bluetooth for dual communication options.
- Enhanced security measures such as password protection.
- Advanced scheduling for automatic firework sequences.

