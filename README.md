# Incremental Conductance MPPT – Buck Converter using TI MSPM0L1306

A real-time Maximum Power Point Tracking (MPPT) firmware implementation using the **Incremental Conductance** algorithm for a **buck converter**

---

## System Overview

- **DC-DC Converter**: Buck

- **MCU**: STM32, TI C2000 or any other MCUs

- **Switching Frequency**: 40 kHz

- **Algorithm**: Incremental Conductance MPPT

- **Battery**: 12V Lead-Acid / Li-ion (configurable)

---

## Firmware Features

- Accurate tracking of maximum power point under dynamic irradiance

- Adjustable step size for voltage control

- Modular structure for MPPT control and converter tuning

---

## Project Structure

```bash

src/          → Source code (MPPT logic and main control)

include/      → TI MCU configurations and definitions

docs/         → Flowcharts and system diagrams

README.md     → This documentation
 
