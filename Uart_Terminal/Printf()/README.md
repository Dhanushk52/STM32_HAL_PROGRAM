## 🧪 Goal

Use `printf()` to send data from STM32 (Blue Pill) to PC via UART (e.g., USART1 or USART2).

---

## 🔧 STM32CubeIDE Setup for UART `printf()`

### ✅ Step 1: Create a New Project

* Open **STM32CubeIDE**
* File → New → STM32 Project
* Select **STM32F103C8T6** (Blue Pill)
* Name the project, e.g., `UART_Printf`
* Click **Finish**

---

### ⚙️ Step 2: Configure UART in `.ioc` File

1. **Go to .ioc File**
2. **Enable UART1 or UART2**

   * Click on `PA9` (TX) and `PA10` (RX) pins
   * Set mode to **USART1\_TX** and **USART1\_RX**
3. **Enable UART1 in Peripherals > USART1**

   * Mode: Asynchronous
   * Baud rate: **9600** (or 115200, your choice)
4. **Set NVIC Interrupt (optional for later)**

   * USART1 global interrupt: Enabled (for interrupt method later)

---

### 🧾 Step 3: Generate Initialization Code

* Click **Project > Generate Code**
* Save changes when asked
* This creates `MX_USART1_UART_Init()` in `usart.c`

---

### 📄 Step 4: Redirect `printf()` to UART

#### Add to `main.c` (below includes):

```c
#include <stdio.h>  // for printf
```

#### Below `MX_USART1_UART_Init();`, add this custom function:

```c
int __io_putchar(int ch)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
```

> ⚠️ If you use GCC (default in STM32CubeIDE), use `fputc()` instead of `__io_putchar()`:

```c
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
```

---

### 🧪 Step 5: Test `printf()` from STM32

In `main.c`, inside the main loop:

```c
while (1)
{
  printf("Hello from STM32 UART\r\n");
  HAL_Delay(1000);
}
```

---

### 🖥️ Step 6: Connect to PC

1. Connect **USB to UART** converter (like CH340 or CP2102):

   * TX → PA10 (RX)
   * RX → PA9 (TX)
   * GND → GND

2. Open **PuTTY or Tera Term**

   * COM port: match your converter (check Device Manager)
   * Baud Rate: 9600
   * Data: 8 bit, Parity: None, Stop bit: 1
   * Flow control: None

---

### 📌 Done!

You should now see `Hello from STM32 UART` printed every second in the terminal. 🎉

---

### ✅ Summary

| Step | Description                         |
| ---- | ----------------------------------- |
| 1    | Create STM32CubeIDE project         |
| 2    | Enable UART in .ioc (USART1)        |
| 3    | Generate code                       |
| 4    | Redirect `printf()` using `fputc()` |
| 5    | Add `printf()` in main loop         |
| 6    | Connect UART to PC & test           |

---

