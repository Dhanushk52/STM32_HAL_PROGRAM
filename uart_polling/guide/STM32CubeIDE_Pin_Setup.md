# 🔧 STM32CubeIDE Guide: UART Polling (USART1) – STM32F103C8T6

This guide helps configure UART communication on STM32F103C8T6 (Blue Pill) using **polling method** via `HAL_UART_Transmit()`.

---

## ✅ 1. Project Setup

- Open **STM32CubeIDE**
- File → New STM32 Project
- Select Board/MCU: `STM32F103C8Tx`
- Project Name: `uart_polling`
- Finish

---

## 🧭 2. Pin Configuration

### USART1 (TX/RX)
- Click on **PA9** → Select `USART1_TX`
- Click on **PA10** → Select `USART1_RX` *(optional – only if you want to receive data)*

📌 These are the default UART1 pins:
| Function | Pin |
|----------|-----|
| TX       | PA9 |
| RX       | PA10 |

---

## ⚙️ 3. USART1 Settings

- Go to **Peripherals → USART1**
- Enable **Mode**:
  - Select `Asynchronous`
  - Tick `TX` *(and RX if needed)*

### Basic Settings:
- Baud Rate: `9600` or `115200`
- Word Length: `8 Bits`
- Parity: `None`
- Stop Bits: `1`
- Hardware Flow Control: `None`

---

## 🔌 4. RCC Configuration (Clock)

- Go to **System Core → RCC**
  - HSE: `Crystal/Ceramic Resonator` *(if using external crystal)*
  - SYSCLK Source: HSE or PLL (recommended)

---

## 🧰 5. Code Generator Settings

- Go to **Project Manager → Code Generator**
- ✅ Check:
  - [x] Generate peripheral initialization as a pair of `.c/.h` files
  - [x] Keep user code when re-generating

---

## 🛠️ 6. Generate Code

- Save (`Ctrl + S`)
- Click **GENERATE CODE**
- It will generate:
  - `MX_USART1_UART_Init()`
  - USART1 init settings in `usart.c`

---

## 🧪 7. Test Code (Polling Transmit)

Inside `main()`:

```c
char msg[] = "UART Polling Hello\r\n";
HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

⚡ 8. UART Output via USB-to-Serial
Connect USB-to-Serial adapter:

Adapter TX → STM32 PA10 (RX)

Adapter RX → STM32 PA9 (TX)

GND → GND

Software to View UART Output:
Use PuTTY, TeraTerm, or Arduino Serial Monitor

Set correct COM port

Baud: 9600 or 115200 (match code)

✅ Final Checklist
Task	Status
USART1 TX (PA9) Configured	✅
Baud Rate 9600 / 115200	✅
UART Mode Asynchronous	✅
HAL_UART_Transmit() Used	✅
Output visible in PuTTY	✅

🎯 Outcome
You will see UART Polling Hello printed repeatedly in the serial terminal every second — fully using STM32 HAL polling method 💬

