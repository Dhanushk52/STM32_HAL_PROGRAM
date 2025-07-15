# 🛠️ STM32CubeIDE Setup Guide for Digital Output (LED Blink)

This guide shows how to set up the STM32F103C8T6 (Blue Pill) to blink an LED using a digital output pin (PC13).

---

## 🔧 1. Open or Create a Project

- Open STM32CubeIDE
- Create a new STM32 project:
  - MCU: STM32F103C8T6
  - Name: digital_output
  - Finish

---

## 📍 2. Configure Output Pin

### ➤ Set **PC13** as Output:
- Click on PC13 in the **Pinout view**
- Select **GPIO_Output**
- Go to "Pin Configuration" tab and verify:
  - **Mode**: Output Push Pull
  - **Speed**: Low Frequency
  - **User Label** (Optional): `LED_Pin`

🧠 Note: PC13 is connected to the on-board LED on most Blue Pill boards. It is **active LOW**.

---

## ⚙️ 3. Clock Configuration

- No need to change anything
- Leave default (HSI internal clock)

---

## 💾 4. Save and Generate Code

- Press **Ctrl + S** to save
- STM32CubeIDE will ask: "Do you want to generate code?"
  - Click **Yes**
- You’ll now have files like:
  - `main.c`
  - `gpio.c`
  - `gpio.h`

✍️ **Important**: Replace `main.c` and `main.h` with your **own handwritten version** (from the `program/` folder).

---

## 🔌 5. Connect Hardware (if using external LED)

| Pin   | Function           |
|--------|--------------------|
| PC13  | Output to LED Anode |
| GND   | LED Cathode (via resistor, ~220Ω) |

- Internal on-board LED uses PC13, so no external circuit is required if using that.

---

## ✅ 6. Flash and Run

- Build the project: `Ctrl + B`
- Flash to board using ST-Link / USB UART
- LED should blink ON/OFF every 500ms as coded

---

# 🔚 Done! You’ve completed the pin setup for Digital Output 💡
