
# 📐 STM32CubeIDE Setup: UART DMA + Timer Interrupt

---

## 🧰 Tools Used

* STM32CubeIDE
* STM32F103C8T6 (Blue Pill)
* USART1 (TX: PA9)
* TIM2 (Timer interrupt every 3s)
* DMA Channel (for USART1 TX)
* PC13 (LED Blink)

---

## ✅ 1. **Create a New STM32 Project**

1. `File → New STM32 Project`
2. Select **STM32F103C8Tx** (Blue Pill)
3. Name it `uart_dma_timer`
4. Click **Finish**

---

## ✅ 2. **Configure USART1 (TX Only)**

### 🔌 Enable TX Pin:

1. Click pin **PA9** → Select **USART1\_TX**

### ⚙️ USART Settings:

1. Go to **Peripherals → USART1**
2. Set Mode: `Asynchronous`
3. Baud rate: `9600`
4. Enable `USART1 global interrupt` (NVIC tab)

---

## ✅ 3. **Enable DMA for USART1 TX**

### 🔁 DMA Settings:

1. Go to **Peripherals → USART1**
2. Enable **DMA Settings** tab
3. Under `USART1_TX`, click **Add**

   * Select: `DMA1 Channel 4` *(default for USART1\_TX)*
   * Direction: `Memory to Peripheral`
   * Mode: `Normal` *(or Circular if repeating forever)*
4. Leave `Increment` and `Priority` default

---

## ✅ 4. **Configure Timer TIM2**

### ⏱️ Basic Configuration:

1. Go to **Peripherals → TIM2**
2. Set:

   * **Prescaler**: `7200 - 1`  → (72 MHz / 7200 = 10 KHz)
   * **Counter Period**: `30000 - 1` → (1 overflow every 3 seconds)
3. Enable TIM2 interrupt in **NVIC**

---

## ✅ 5. **Configure PC13 as Output (LED)**

### 🔦 LED Pin:

1. Click **PC13** → Set as `GPIO_Output`
2. GPIO Settings:

   * Mode: Output Push-Pull
   * Speed: Low

---

## ✅ 6. **Clock Configuration**

(optional if default is fine)

* Confirm:

  * SYSCLK = 72 MHz
  * APB1 = 36 MHz
  * TIM2 is sourced from APB1 (×2 = 72 MHz effective)

---

## ✅ 7. **Generate Code**

1. Click **Project → Generate Code**
2. Open `main.c`
3. Add application logic for:

   * LED blink
   * Timer interrupt
   * UART DMA transfer

---

## ✅ 8. **Final Pinout & DMA Summary**

| Function       | Pin        | Remarks               |
| -------------- | ---------- | --------------------- |
| USART1\_TX     | PA9        | Data sent to PC       |
| LED (GPIO)     | PC13       | Blinks in main loop   |
| TIM2 Interrupt | —          | Triggers every 3 sec  |
| DMA1\_Channel4 | USART1\_TX | Handles UART transfer |

---

## ✅ 9. **Serial Terminal Setup**

* Use USB-to-Serial module:

  | STM32F103 | USB-Serial |
  | --------- | ---------- |
  | PA9 (TX)  | RX         |
  | GND       | GND        |
* Open PuTTY or TeraTerm:

  * Baud rate: `9600`
  * Format: `8-N-1`

---

## ✅ 10. **Expected Behavior**

* PC13 LED blinks every 500ms
* Every 3 seconds:

  * `Timer interrupt` triggers
  * `HAL_UART_Transmit_DMA()` sends a message
  * You see:

    ```
    Timer DMA UART: Hello STM32!
    ```

---
