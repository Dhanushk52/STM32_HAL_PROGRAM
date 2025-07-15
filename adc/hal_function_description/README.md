
# 📘 Beginner's Guide to STM32F103C8T6 – ADC with HAL Library

---

## **1. Introduction**

The STM32F103C8T6 (Blue Pill) includes a 12-bit Analog-to-Digital Converter (ADC) that allows you to read analog signals from external sensors, potentiometers, and other analog sources. This guide shows how to use ADC with STM32 HAL functions.

---

## **2. What is ADC?**

ADC (Analog-to-Digital Converter) converts analog voltage (0 to 3.3V) into a digital number (0 to 4095 for 12-bit ADC). It allows the microcontroller to sense real-world analog signals.

---

## **3. Development Setup**

| Component  | Value                               |
| ---------- | ----------------------------------- |
| MCU        | STM32F103C8T6 (Blue Pill)           |
| IDE        | STM32CubeIDE                        |
| Peripheral | ADC1                                |
| Input Pin  | PA0 (ADC Channel 0)                 |
| Output     | UART (via PA9) for displaying value |

---

## **4. HAL ADC Function Documentation**

---

### 🔹 **4.1 `HAL_ADC_Start()`**

* **Purpose**: Starts ADC conversion
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc);
  ```
* **Parameters**:

  * `hadc`: pointer to ADC handle (e.g., `&hadc1`)
* **Example**:

  ```c
  HAL_ADC_Start(&hadc1);
  ```
* **Expected Outcome**: Triggers ADC to begin a conversion (but doesn’t wait for result)

---

### 🔹 **4.2 `HAL_ADC_PollForConversion()`**

* **Purpose**: Waits (blocks) until ADC conversion is complete
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);
  ```
* **Parameters**:

  * `hadc`: ADC handle
  * `Timeout`: time to wait in ms
* **Example**:

  ```c
  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
  ```
* **Expected Outcome**: Waits until conversion is done

---

### 🔹 **4.3 `HAL_ADC_GetValue()`**

* **Purpose**: Reads the digital value from the ADC data register
* **Prototype**:

  ```c
  uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);
  ```
* **Parameters**:

  * `hadc`: ADC handle
* **Returns**:

  * 12-bit ADC result (0–4095)
* **Example**:

  ```c
  uint32_t val = HAL_ADC_GetValue(&hadc1);
  ```
* **Expected Outcome**: Gets the voltage level (e.g., 2048 if halfway)

---

### 🔹 **4.4 `HAL_ADC_Init()`**

* **Purpose**: Initializes the ADC peripheral
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef *hadc);
  ```
* **Parameters**:

  * `hadc`: ADC handle
* **Expected Outcome**: Configures internal ADC registers based on your `.Init` struct

---

### 🔹 **4.5 `HAL_ADC_ConfigChannel()`**

* **Purpose**: Sets the ADC input channel and its settings (sampling time, rank)
* **Prototype**:

  ```c
  HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig);
  ```
* **Parameters**:

  * `hadc`: ADC handle
  * `sConfig`: structure with channel config
* **Example**:

  ```c
  ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  ```
* **Expected Outcome**: Selects PA0 as ADC input with a specific sampling time

---

## **5. Example Program**

> This example reads analog value from PA0 and sends the result to PC via UART.

```c
#include "main.h"

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);
void MX_USART1_UART_Init(void);

ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart1;

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();

  char msg[50];
  uint32_t adc_val = 0;

  while (1)
  {
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) == HAL_OK)
    {
      adc_val = HAL_ADC_GetValue(&hadc1);
      int len = sprintf(msg, "ADC Value: %lu\r\n", adc_val);
      HAL_UART_Transmit(&huart1, (uint8_t*)msg, len, HAL_MAX_DELAY);
    }
    HAL_Delay(1000);
  }
}
```

---

## **6. Expected Outcome**

* Connect potentiometer or sensor to PA0.
* Serial monitor will print the ADC value every 1 second.
* Example:

  ```
  ADC Value: 256
  ADC Value: 1296
  ADC Value: 4095
  ```

---

## ✅ Summary Table

| Function                      | Role                        |
| ----------------------------- | --------------------------- |
| `HAL_ADC_Start()`             | Start conversion            |
| `HAL_ADC_PollForConversion()` | Wait for result             |
| `HAL_ADC_GetValue()`          | Read digital value          |
| `HAL_ADC_Init()`              | Setup ADC peripheral        |
| `HAL_ADC_ConfigChannel()`     | Choose channel and settings |

