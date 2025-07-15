# 🛠️ STM32CubeIDE Setup Guide for ADC (Analog to Digital Conversion)

This guide shows how to configure the STM32F103C8T6 (Blue Pill) in STM32CubeIDE to read analog voltage through the ADC peripheral (using PA0).

---

## 🔧 1. Create or Open STM32 Project

- Open **STM32CubeIDE**
- Create a new STM32 project:
  - MCU: `STM32F103C8T6`
  - Name: `adc_read`
  - Click Finish

---

## 📍 2. Configure ADC Pin (PA0)

### ➤ Enable Analog Input:
- In the **Pinout view**, click on **PA0**
- Select **ADC1_IN0** (automatically enables ADC1)
- This configures PA0 as **analog input**

---

## 🧰 3. ADC1 Peripheral Settings

### ➤ Go to **"Peripherals > ADC1 > Configuration"**:
- **Scan Conversion Mode**: **Disabled**
- **Continuous Conversion Mode**: **Disabled**
- **Discontinuous Mode**: **Disabled**
- **DMA Continuous Requests**: **Disabled**
- **End of Conversion Selection**: **End of Single Conversion**
- **Data Alignment**: **Right**
- **Resolution**: 12-bit
- **External Trigger**: **Software Start**

✅ This ensures we read ADC only when we want (on-demand with HAL).

---

## 📡 4. (Optional) UART for Serial Print

> If you're using `HAL_UART_Transmit()` to print ADC value on serial monitor:

### ➤ Enable USART1:
- In Pinout view, click **PA9** → choose **USART1_TX**
- (Optional: PA10 for RX)
- Go to **USART1 Configuration**:
  - Baud Rate: **9600**
  - Word Length: 8 Bits
