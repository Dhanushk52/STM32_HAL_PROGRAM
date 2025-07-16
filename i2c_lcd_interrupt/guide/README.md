## 📘 `STM32CubeIDE_Pin_Setup.md`

````md
# 🧩 STM32CubeIDE Setup Guide: I2C LCD + Button Interrupt with Flag

This guide walks you through STM32CubeIDE configuration to:
- Interface 16x2 LCD using I2C (PCF8574T @ 0x27)
- Detect external interrupt on PA0 (button)
- Use PC13 to toggle an LED
- Communicate ISR to main using `volatile btn_pressed_flag`

---

## 🛠️ 1. Create New STM32 Project

- Open STM32CubeIDE
- File → New STM32 Project
  - MCU: `STM32F103C8Tx`
  - Project Name: `i2c_lcd_interrupt_flag`
- Finish

---

## 🔌 2. I2C1 Setup for LCD

### Pinout View
- Click **PB6** → Select `I2C1_SCL`
- Click **PB7** → Select `I2C1_SDA`

### Configuration
- Peripherals → I2C1 → Mode: I2C
- Timing: default (100kHz)
- Leave all other fields default

🧠 PCF8574T uses address 0x27 (HAL needs 8-bit address = `0x4E`)

---

## 💡 3. GPIO Output (LED)

- Click on **PC13** → Mode: `GPIO_Output`

📌 This is the on-board user LED.

---

## 🛎️ 4. External Interrupt Input (PA0)

- Click on **PA0** → Mode: `GPIO_EXTI0`

### Configuration:
- Trigger: `Falling edge`
- GPIO mode: `Input`
- Pull: `Pull-up` (if button goes to GND)
- Cube will auto-enable `EXTI0_IRQn` in NVIC

✅ No need to manually edit NVIC

---

## ⚙️ 5. Enable Required Clocks

Cube auto-enables:
- I2C1 (for PB6, PB7)
- GPIOA (PA0)
- GPIOB (I2C)
- GPIOC (LED on PC13)

Verify under **System Core > RCC**

---

## 🧾 6. Generate Code

- Click **Save All** (`Ctrl+S`)
- Click **GENERATE CODE**
- STM32CubeIDE creates:
  - `MX_GPIO_Init()` – for PA0, PC13
  - `MX_I2C1_Init()` – for PB6, PB7
  - EXTI handlers in `stm32f1xx_it.c`

---

## 🔌 7. Hardware Connection Summary

| Peripheral | STM32F103C8T6 Pin | Description         |
|------------|------------------|---------------------|
| LCD SDA    | PB7              | I2C1_SDA            |
| LCD SCL    | PB6              | I2C1_SCL            |
| LCD VCC    | 5V / 3.3V        | Power               |
| LCD GND    | GND              | Ground              |
| LED        | PC13             | On-board LED        |
| Button     | PA0              | Button input        |
| Button GND | GND              | One leg of button   |

✅ Optional: Use 10kΩ pull-down if you see noise on PA0.

---

## ✅ 8. Code Integration Steps

Paste this at the top of `main.c`:

```c
volatile uint8_t btn_pressed_flag = 0;
````

Then inside `main()` loop:

```c
if (btn_pressed_flag) {
  btn_pressed_flag = 0;
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
  lcd_send_cmd(0x01);
  HAL_Delay(2);
  lcd_send_string("Btn Pressed!");
  HAL_Delay(1000);
  lcd_send_cmd(0x01);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  lcd_send_string("Interrupt Ready");
}
```

And define:

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_0) {
    btn_pressed_flag = 1;
  }
}
```

---

## 🎯 Expected Output

* LCD displays: `Interrupt Ready`
* When PA0 is pressed:

  * PC13 LED turns ON for 1 second
  * LCD briefly shows: `Btn Pressed!`
  * Then resets to: `Interrupt Ready`

---

## 🎉 Setup Complete

You’ve now built a **responsive**, **interrupt-safe**, and **HAL-based** LCD controller using STM32!

