# 📘 HAL Function Documentation – I2C LCD with Interrupt + Flag Handling

---

## 🧠 1. Introduction

This guide explains the STM32 HAL functions used in a project that:

* Uses **I2C** to drive a 16x2 LCD (via PCF8574T @ 0x27)
* Detects **button presses on PA0** using EXTI (interrupt)
* Toggles **on-board LED on PC13**
* Uses a `volatile` flag for **safe ISR-to-main communication**

---

## 📦 2. Key HAL Functions

### 🔹 2.1 `HAL_I2C_Master_Transmit()`

**Purpose**: Send data to the LCD using the PCF8574T I/O expander.

**Prototype**:

```c
HAL_StatusTypeDef HAL_I2C_Master_Transmit(
  I2C_HandleTypeDef *hi2c,
  uint16_t DevAddress,
  uint8_t *pData,
  uint16_t Size,
  uint32_t Timeout
);
```

**Used In**: `lcd_send_internal()`

**Example**:

```c
HAL_I2C_Master_Transmit(&hi2c1, 0x4E, buf, 4, HAL_MAX_DELAY);
```

---

### 🔹 2.2 `HAL_GPIO_EXTI_Callback()`

**Purpose**: User-defined function that gets called automatically when an external interrupt occurs on a GPIO pin.

**Prototype**:

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
```

**Your Use**:

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_0)
  {
    btn_pressed_flag = 1;
  }
}
```

✅ Instead of doing everything inside the ISR (which is bad practice), we **just set a flag** here.

---

### 🔹 2.3 `volatile uint8_t btn_pressed_flag`

This is not a HAL function, but important to understand:

* **Why volatile?**
  Because it's shared between **ISR context** and **main loop**, `volatile` tells the compiler not to optimize out reads/writes.

**Defined As**:

```c
volatile uint8_t btn_pressed_flag = 0;
```

**Checked In**:

```c
if (btn_pressed_flag) {
  btn_pressed_flag = 0;
  // Handle event
}
```

---

### 🔹 2.4 `HAL_GPIO_WritePin()`

**Purpose**: Set a GPIO output pin HIGH or LOW.

**Prototype**:

```c
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
```

**Example**:

```c
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // LED ON
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   // LED OFF
```

✅ You control the LED connected to PC13 using this.

---

### 🔹 2.5 `HAL_Delay()`

**Purpose**: Simple blocking delay in milliseconds.

**Prototype**:

```c
void HAL_Delay(uint32_t Delay);
```

**Used For**:

* Allow LCD to process
* Pause display for user visibility

---

## 📋 3. Summary Table

| Function                    | Purpose                               |
| --------------------------- | ------------------------------------- |
| `HAL_I2C_Master_Transmit()` | Send LCD command/data                 |
| `HAL_GPIO_EXTI_Callback()`  | Detect external interrupt (PA0)       |
| `HAL_GPIO_WritePin()`       | Toggle LED on PC13                    |
| `HAL_Delay()`               | Add visual or processing delays       |
| `volatile btn_pressed_flag` | Flag shared between ISR and main loop |

---

✅ This version follows best practices for embedded:

* ISR sets flag only ✅
* Main loop handles logic ✅
* Clean HAL-based LCD interface ✅

---
