# 🛠️ STM32CubeIDE Setup Guide for PWM Output (TIM1 → PA8)

This guide explains how to configure STM32F103C8T6 (Blue Pill) to output a PWM signal using Timer 1 on PA8.

---

## 🔧 1. Create or Open a Project

- Open **STM32CubeIDE**
- Create a new project:
  - MCU: STM32F103C8T6
  - Project name: `pwm_output`
  - Finish

---

## 📍 2. Configure PWM Pin

### ➤ Set PA8 as TIM1 Channel 1 Output:
- In **Pinout view**, click on **PA8**
- Select **TIM1_CH1**
- This enables TIM1 for PWM

---

## ⚙️ 3. Configure Timer for PWM

### ➤ Go to **Timers > TIM1 > Mode** tab:
- Enable **PWM Generation CH1**

### ➤ Go to **Configuration** tab:
- **Prescaler**: `72 - 1`  
  → 72 MHz / 72 = 1 MHz Timer Clock
- **Counter Period**: `1000 - 1`  
  → PWM frequency = 1 MHz / 1000 = **1 kHz**
- **PWM Mode**: PWM Mode 1
- **Pulse**: `500` (default 50% duty)
- **Polarity**: High

---

## 📡 4. Enable Clock & GPIO (Auto-handled)

- When you select TIM1 and PA8 in CubeIDE, the following is auto-enabled:
  - TIM1 clock
  - GPIOA clock
  - PA8 pin alternate function (AF-PP)

Nothing extra to do here ✅

---

## 💾 5. Generate Code

- Save project (`Ctrl + S`)
- Click **Yes** to generate initialization code
- Cube will generate:
  - `MX_TIM1_Init()`
  - `MX_GPIO_Init()`
  - And all required HAL structs

---

## 🔌 6. Connect Hardware (If Needed)

| Pin   | Function            | Connect to                  |
|--------|---------------------|-----------------------------|
| PA8   | PWM Output (TIM1_CH1) | Oscilloscope, motor driver, or LED (with resistor) |
| GND   | Ground               | Common ground              |

🧠 **TIP**: For LED test, use a 330Ω resistor in series.

---

## ✅ 7. Replace `main.c` Logic

- Open `main.c`
- Keep the
