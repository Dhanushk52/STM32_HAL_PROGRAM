# 🔌 STM32F103C8T6 Blue Pill USB DFU Bootloader Installation

This guide explains how to flash a USB DFU bootloader (like **Maple DFU**) to your **STM32F103C8T6 (Blue Pill)** so you can update firmware using USB instead of FTDI or ST-Link.

---

## 📦 Prerequisites

- ✅ STM32F103C8T6 Blue Pill board  
- ✅ USB Mini-B cable  
- ✅ STM32CubeProgrammer (installed)  
- ✅ `generic_boot20_pc13.bin` (Maple DFU bootloader)  
- ✅ (Optional) Zadig USB driver tool for Windows  

---

## 🛠️ Step 1: Flash the DFU Bootloader

> You'll need an ST-Link or USB-to-Serial converter for this **one-time** setup.

1. Set the boot pins:
   - `BOOT0 = 1`
   - `BOOT1 = 0` (usually pulled low by default)

2. Connect your programmer:
   - ST-Link: Connect SWDIO, SWCLK, GND, 3.3V
   - FTDI: Connect PA9 → RX, PA10 → TX

3. Launch **STM32CubeProgrammer**

4. Connect to the board (`ST-Link` or `UART`)

5. Flash the bootloader:
   - File: `generic_boot20_pc13.bin`
   - Start address: `0x08000000`
   - Click **Download**

6. Set `BOOT0 = 0` and **reset** the board

---

## 🔌 Step 2: Enable USB DFU Detection

1. Plug the USB cable directly into the Blue Pill  
2. Check **Device Manager**:
   - You should see `STM32 BOOTLOADER` under USB devices
   - If there’s a yellow warning, use **Zadig** to install **WinUSB driver**

> 💡 Use Zadig: Select `STM32 Bootloader` → Install Driver → Choose `WinUSB`

---

## 💻 Step 3: Flash Firmware via USB (DFU)

1. Open **STM32CubeProgrammer**

2. Select `USB` from the interface list  
   - Baudrate not needed  
   - Click **Connect**

3. Select your `.hex` or `.bin` firmware file

4. Set **Start Address**: `0x08000000`

5. Click **Download**

6. Once complete, **reset** the board — your app will start!

---

## ✅ Summary Table

| Scenario                  | Connection Type | Bootloader        | How to Upload        |
|---------------------------|------------------|--------------------|-----------------------|
| First Bootloader Flash    | ST-Link / UART   | `generic_boot20...`| STM32CubeProgrammer   |
| Firmware Update Later     | USB (DFU mode)   | Already installed  | STM32CubeProgrammer   |

---

## ⚠️ Pro Tips

- **1.5kΩ resistor** must pull **PA12 (USB D+)** to **3.3V**
- PA11 = USB D− (white), PA12 = USB D+ (green)
- Use `.hex` output from STM32CubeIDE (`Project → Properties → C/C++ Build → Settings → Tool Settings → MCU Post-build Outputs → Convert to HEX`)
- Always reset with `BOOT0 = 0` to boot into user code

---

## 🧠 Optional Improvements

- Add USB reconnect circuit using pull-up transistor on PA12
- Modify bootloader to auto-jump to user code after timeout
- Use STM32CubeIDE to build firmware in `.hex` format

---

## 📺 Reference Video

> 📹 Watch the tutorial:  
[![Phil’s Lab - Install STM32 DFU Bootloader](https://img.youtube.com/vi/ReSaV4y2XSA/0.jpg)](https://www.youtube.com/watch?v=ReSaV4y2XSA)

---

## 🧾 License

MIT License — free to use, modify, and distribute.

---

## 🙌 Credits

- Video by [Phil’s Lab](https://www.youtube.com/@PhilsLab)
- STM32 open-source DFU bootloader by Leaflabs/Maple
- STM32CubeProgrammer by STMicroelectronics

