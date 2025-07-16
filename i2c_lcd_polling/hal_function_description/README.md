# 📘 Beginner’s Guide to STM32F103C8T6 – I2C LCD (PCF8574T) with HAL

---

## **1. Introduction**

The PCF8574T is an I/O expander used to control HD44780 LCDs using I2C.
This saves GPIO pins and uses only **2 wires**: SDA and SCL.

STM32 HAL provides an easy-to-use I2C API for this.

---

## **2. What is I2C LCD?**

It’s a standard 16x2 LCD display (with HD44780 controller) connected via an I2C backpack (PCF8574T).
The LCD works in **4-bit parallel mode**, but we use I2C serial commands to simulate those signals.

---

## **3. Development Setup**

| Component | Details                                |
| --------- | -------------------------------------- |
| MCU       | STM32F103C8T6 (Blue Pill)              |
| LCD       | 16x2 with PCF8574T I2C backpack        |
| I2C Addr  | 0x27 (must be shifted to 0x4E for HAL) |
| IDE       | STM32CubeIDE                           |
| Comm      | I2C – Polling Method                   |

---

## **4. HAL I2C Function Documentation**

---

### 🔹 4.1 `HAL_I2C_Master_Transmit()`

* **Purpose**: Send data to a slave device (here, LCD via PCF8574T)

* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_I2C_Master_Transmit(
    I2C_HandleTypeDef *hi2c,
    uint16_t DevAddress,
    uint8_t *pData,
    uint16_t Size,
    uint32_t Timeout
  );
  ```

* **Parameters**:

  | Parameter    | Meaning                                    |
  | ------------ | ------------------------------------------ |
  | `hi2c`       | Pointer to I2C handle (e.g. `&hi2c1`)      |
  | `DevAddress` | 8-bit address of slave (0x27 << 1 = 0x4E)  |
  | `pData`      | Pointer to data buffer to send             |
  | `Size`       | Number of bytes to send                    |
  | `Timeout`    | Max wait time in ms (e.g. `HAL_MAX_DELAY`) |

* **Example**:

  ```c
  uint8_t data[] = {0x3C}; // Send single byte
  HAL_I2C_Master_Transmit(&hi2c1, 0x4E, data, 1, HAL_MAX_DELAY);
  ```

---

### 🧠 Understanding LCD 4-bit I2C Logic

Because the PCF8574 just toggles **8 digital lines**, we emulate 4-bit LCD protocol like this:

```c
buf[0] = UPPER_NIBBLE | control bits | ENABLE
buf[1] = UPPER_NIBBLE | control bits          // falling edge = latch
buf[2] = LOWER_NIBBLE | control bits | ENABLE
buf[3] = LOWER_NIBBLE | control bits
```

Then send:

```c
HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, buf, 4, HAL_MAX_DELAY);
```

---

### 🔹 4.2 LCD Control Bits Summary

| Bit       | Description               |
| --------- | ------------------------- |
| RS = 0    | Send **command**          |
| RS = 1    | Send **data** (character) |
| E         | Strobe signal (Enable)    |
| Backlight | Always keep ON (0x08)     |

We send both **upper nibble** and **lower nibble** using I2C burst.

---

## **5. Supporting HAL Functions**

### 🔹 `HAL_Delay()`

Used to create timing gaps after I2C transmission:

```c
HAL_Delay(1); // Required for LCD timing
```

---

## **6. Expected Outcome**

* LCD initialized using HAL-based I2C commands
* Text appears on Line 1 and Line 2
* You only use **SCL (PB6)** and **SDA (PB7)** — saves GPIOs!
* Clean, portable HAL code

---

## ✅ Summary Table

| Function                    | Role                             |
| --------------------------- | -------------------------------- |
| `HAL_I2C_Master_Transmit()` | Sends data to LCD                |
| `HAL_Delay()`               | Ensures timing/strobe separation |
| `lcd_send_cmd()`            | Sends LCD instruction            |
| `lcd_send_data()`           | Sends characters                 |
| `lcd_send_string()`         | Sends string                     |
| `lcd_init()`                | Full LCD initialization          |

---

