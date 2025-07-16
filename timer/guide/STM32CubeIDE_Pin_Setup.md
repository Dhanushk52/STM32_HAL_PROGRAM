# ⏱️ STM32CubeIDE Setup Guide for Timer Interrupt (TIM2)

This guide explains how to configure TIM2 in **interrupt mode** to generate a periodic signal (e.g. blinking an LED every 500 ms) using STM32F103C8T6 (Blue Pill).

---

## 🧱 1. Create or Open STM32CubeIDE Project

- Open STM32CubeIDE
- Create a new STM32 project
  - Target: **STM32F103C8T6**
  - Project Name: `timer_interrupt`
- Click **Finish**

---

## 📍 2. Enable Timer Peripheral (TIM2)

- In the **Pinout & Configuration** tab:
  - From **Peripherals > Timers**, enable **TIM2**
  - Mode: **Time Base**
  - Enable **Interrupt** checkbox

🧠 TIM2 is a 32-bit general-purpose timer suitable for this use case.

---

## 🛠️ 3. Configure TIM2 Settings

Go to **Configuration > TIM2**:

- **Prescaler**: `7199`  
  → 72 MHz / (7199 + 1) = 10,000 Hz (10 kHz)

- **Counter Period**: `4999`  
  → 10 kHz / 5000 = 2 Hz → **500 ms interval**

- **Counter Mode**: Up
- **Clock Division**: No division
- **Auto-Reload Preload**: Enable

✅ This config makes TIM2 overflow (and generate interrupt) every 500ms

---

## 📡 4. Enable LED Pin (Optional — For Output)

- Click on **PA5**
- Set as **GPIO_Output**
- Used to toggle LED from interrupt

---

## ⚙️ 5. Enable NVIC Interrupt for TIM2

In the **"NVIC Settings"** under **System Core > NVIC**:

- Check ✅ **TIM2 global interrupt**

This tells the CPU to call the ISR when TIM2 overflows.

---

## 🔁 6. Generate Code

- Save the project (`Ctrl + S`)
- Cube will generate:
  - `MX_TIM2_Init()`
  - Interrupt vector setup in `stm32f1xx_it.c`
- `htim2` is automatically created and initialized

🧠 Note: You will write `HAL_TIM_PeriodElapsedCallback()` manually.

---

## 🔌 7. Hardware Setup

| Pin | Function     | Connected To           |
|-----|--------------|------------------------|
| PA5 | GPIO_Output  | LED with resistor      |
| GND | Ground       | Common ground          |

---

## 🧪 8. Build and Flash

- Add your custom logic in `main.c`
  - Start timer using `HAL_TIM_Base_Start_IT(&htim2);`
  - Toggle LED in `HAL_TIM_PeriodElapsedCallback()`

---

## ✅ Final Output

- TIM2 generates interrupt every 500 ms
- LED on PA5 toggles inside ISR
- You’ll see blinking LED or 1 Hz signal on oscilloscope

---

# ✅ Done!

Timer setup is now complete using STM32CubeIDE + HAL interrupt method.
