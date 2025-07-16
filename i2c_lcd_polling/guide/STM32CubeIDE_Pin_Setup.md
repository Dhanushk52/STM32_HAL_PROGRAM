# 📟 STM32CubeIDE Setup Guide for 16x2 LCD via I2C (PCF8574T @ 0x27)

This guide walks you through configuring STM32F103C8T6 (Blue Pill) to interface with a 16x2 LCD using I2C (PCF8574T backpack) and HAL polling method.

---

## 🛠️ 1. Create a New Project

- Open STM32CubeIDE
- Create a new project:
  - MCU: STM32F103C8T6
  - Name: `i2c_lcd_display`
- Click **Finish**

---

## 📍 2. Configure I2C1 Peripheral

### ➤ Set up I2C pins:
- In **Pinout View**:
  - Click on **PB6** → Select `I2C1_SCL`
  - Click on **PB7** → Select `I2C1_SDA`

🧠 These are hardware I2C pins of I2C1.

---

## ⚙️ 3. Configure I2C Settings

- Go to **Peripherals > I2C1 > Configuration**
- Set:
  - **Timing**: Leave default (or use `0x2000090E`)
  - **Mode**: I2C
  - **Clock Speed**: 100 kHz (Standard Mode)

✅ HAL automatically manages ACK, stop/start conditions.

---

## 💡 4. Enable GPIO (if needed)

- Cube will automatically enable GPIOB and I2C1 clocks
- You can verify in **System Core > RCC**

---

## 🚀 5. Enable Debug UART (Optional for Debug Print)

- (Optional) Click on **PA9** = `USART1_TX` and **PA10** = `USART1_RX`
- Enable USART1 for debugging if desired

---

## 🧾 6. Save and Generate Code

- Save the project (`Ctrl + S`)
- Click **GENERATE CODE**
- STM32CubeIDE will:
  - Create `MX_I2C1_Init()` function
  - Define `hi2c1` handle

---

## 🧪 7. Connect Hardware

| LCD Pin     | Connect to Blue Pill |
|-------------|----------------------|
| GND         | GND                  |
| VCC         | 5V or 3.3V (check LCD module specs) |
| SDA         | PB7 (I2C1_SDA)       |
| SCL         | PB6 (I2C1_SCL)       |

✅ Default address is `0x27`, but in HAL it must be left-shifted:
```c
#define LCD_ADDR  (0x27 << 1)  // = 0x4E
