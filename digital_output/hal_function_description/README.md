# 📘 Beginner's Guide to STM32F103C8T6 (Blue Pill) – Digital Output using HAL

---

## **1. Introduction**

The STM32F103C8T6, also known as the Blue Pill, is a powerful yet affordable ARM Cortex-M3 microcontroller board. In this guide, you’ll learn how to control a digital output pin using the STM32 HAL (Hardware Abstraction Layer) library — specifically by blinking the on-board LED.

---

## **2. What is Digital Output?**

Digital output allows a microcontroller to control external devices by driving GPIO pins HIGH (3.3V) or LOW (0V). Typical examples include turning on LEDs, relays, motors, or buzzers.

---

## **3. Development Setup**

| Component   | Details                         |
| ----------- | ------------------------------- |
| MCU         | STM32F103C8T6 (Blue Pill)       |
| IDE         | STM32CubeIDE                    |
| HAL Library | STM32 HAL                       |
| Output Pin  | PC13 (On-board LED, Active-Low) |

---

## **4. HAL GPIO Function Documentation**

---

### 🔹 **4.1 `HAL_GPIO_Init()`**

* **Purpose**: Initializes a GPIO pin with the desired mode (input/output), pull configuration, and speed.
* **Prototype**:

  ```c
  void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
  ```
* **Parameters**:

  * `GPIOx`: GPIO port (e.g., GPIOA, GPIOC)
  * `GPIO_Init`: Pointer to a `GPIO_InitTypeDef` structure
* **Example**:

  ```c
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  ```
* **Expected Outcome**: Configures PC13 as a push-pull output pin with low speed.

---

### 🔹 **4.2 `HAL_GPIO_WritePin()`**

* **Purpose**: Writes a HIGH or LOW value to a digital output pin.
* **Prototype**:

  ```c
  void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
  ```
* **Parameters**:

  * `GPIOx`: GPIO port (e.g., GPIOC)
  * `GPIO_Pin`: GPIO pin number (e.g., `GPIO_PIN_13`)
  * `PinState`: `GPIO_PIN_SET` (HIGH) or `GPIO_PIN_RESET` (LOW)
* **Example**:

  ```c
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // LED ON
  HAL_Delay(500);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   // LED OFF
  HAL_Delay(500);
  ```
* **Expected Outcome**: Turns the on-board LED ON for 500ms, then OFF for 500ms.

---

### 🔹 **4.3 `HAL_Delay()`**

* **Purpose**: Creates a blocking delay in milliseconds.
* **Prototype**:

  ```c
  void HAL_Delay(uint32_t Delay);
  ```
* **Parameters**:

  * `Delay`: Time in milliseconds
* **Example**:

  ```c
  HAL_Delay(1000); // Delay for 1 second
  ```
* **Expected Outcome**: Program execution pauses for the specified delay period.

---

## **5. Example Program**

```c
#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1)
  {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // LED ON
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   // LED OFF
    HAL_Delay(500);
  }
}
---

## **6. Expected Outcome**

* The on-board LED connected to **PC13** will continuously blink.
* Each blink cycle is 500ms ON and 500ms OFF.
* HAL functions simplify GPIO handling by hiding low-level register logic.

---
