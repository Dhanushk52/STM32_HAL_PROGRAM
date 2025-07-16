# 🛠️ STM32CubeIDE Configuration Guide: I2C LCD with DMA

This guide shows you how to configure STM32F103C8T6 (Blue Pill) using STM32CubeIDE to send data to a 16x2 I2C LCD using DMA.

---

## ✅ 1. Create New STM32 Project

- Open **STM32CubeIDE**
- File → New STM32 Project
- Select MCU: `STM32F103C8Tx`
- Project Name: `i2c_lcd_dma`
- Click **Finish**

---

## 📍 2. Pin Configuration (Pinout View)

### 🟦 I2C1 Configuration
- **PB6** → Click and select `I2C1_SCL`
- **PB7** → Click and select `I2C1_SDA`

### 🟩 Enable I2C DMA
- Go to **Peripherals → I2C1 → DMA Settings**
  - Click **Add**
  - Select:  
    - Request: `I2C1_TX`
    - DMA Channel: `DMA1 Channel6`
    - Mode: `Normal`
    - Priority: `Low`

💡 This links I2C transmit to DMA.

---

## 🟨 3. Enable DMA Controller

- Go to **System Core → DMA**
  - Make sure **DMA1** is enabled
  - DMA1 Channel6 is assigned to I2C1 Transmit

---

## 🟥 4. Enable Required Clocks

STM32Cube will auto-enable:
- GPIOB (PB6, PB7)
- I2C1
- DMA1

Just verify under **System Core → RCC**:
- High Speed Clock (HSE): Crystal/Ceramic Resonator
- SYSCLK Source: HSE or PLL (your choice)

---

## 💡 5. Code Generator Settings

Go to **Project Manager → Code Generator**:
- ✅ [x] Generate peripheral initialization as a pair of `.c/.h` files
- ✅ [x] Keep user code when re-generating

---

## ⚙️ 6. Generate Code

- Save (`Ctrl+S`)
- Click **GENERATE CODE**

CubeIDE will now generate:
- `MX_I2C1_Init()`
- `MX_DMA_Init()`
- Code for enabling I2C1 + DMA1 clocks
- `.ioc` file with correct settings

---

## 🔌 7. Hardware Connection Table

| LCD Pin   | STM32 Pin | Description         |
|-----------|-----------|---------------------|
| VCC       | 5V/3.3V   | Power supply         |
| GND       | GND       | Ground               |
| SDA       | PB7       | I2C1 SDA             |
| SCL       | PB6       | I2C1 SCL             |

📌 PCF8574T uses I2C address `0x27` → 8-bit shifted = `0x4E`

---

## 🧪 8. Optional Test Code

In your `main.c`, after initializing peripherals:
```c
lcd_init();
lcd_send_string_dma("DMA LCD Hello!");
