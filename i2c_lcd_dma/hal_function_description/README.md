# 📘 HAL Function Documentation – I2C LCD via DMA

---

## 1. 🧠 Introduction

This document explains the HAL functions used to drive a 16x2 I2C LCD using **DMA (Direct Memory Access)**.
This method reduces CPU load by transferring data from memory to peripheral **without blocking main code execution**.

---

## 2. 🔌 Key HAL Functions

---

### 🔹 2.1 `HAL_I2C_Master_Transmit_DMA()`

**Purpose**: Initiates an I2C transfer using DMA.

**Prototype**:

```c
HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(
  I2C_HandleTypeDef *hi2c,
  uint16_t DevAddress,
  uint8_t *pData,
  uint16_t Size
);
```

**Parameters**:

* `hi2c` → I2C handle (e.g., `&hi2c1`)
* `DevAddress` → 8-bit I2C address of slave (e.g., `0x4E`)
* `pData` → Pointer to data buffer
* `Size` → Number of bytes to send

**Example**:

```c
HAL_I2C_Master_Transmit_DMA(&hi2c1, LCD_ADDR, lcd_buf, 4);
```

✅ This non-blocking version allows your CPU to do other tasks while DMA handles the transfer.

---

### 🔹 2.2 `HAL_I2C_GetState()`

**Purpose**: Check the current state of the I2C peripheral.

**Prototype**:

```c
HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
```

**Return**:

* `HAL_I2C_STATE_READY` → Indicates transmission is complete.

**Usage**:

```c
while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);
```

📌 Always check this before starting the next DMA transfer to avoid conflicts.

---

### 🔹 2.3 `MX_DMA_Init()`

**Purpose**: Initializes DMA controller clocks and links DMA to I2C1.

**Note**: You do **not need to manually write this**, STM32CubeIDE auto-generates it when you enable DMA for I2C1.

Check `.ioc`:

* Go to `I2C1 > DMA Settings`
* Enable `Master Transmit` → Assign to `DMA1_Channel6`

---

## 3. 🧾 Supporting HAL I2C Configuration

Make sure these settings are handled by `MX_I2C1_Init()`:

* Clock Speed: 100kHz
* Duty Cycle: Standard
* Addressing Mode: 7-bit

---

## 4. 🧾 DMA-Driven LCD Flow (Quick Summary)

| Step | Function                        | Purpose                       |
| ---- | ------------------------------- | ----------------------------- |
| 1️⃣  | `lcd_send_internal_dma()`       | Prepare and send 4-byte burst |
| 2️⃣  | `HAL_I2C_Master_Transmit_DMA()` | Start DMA I2C transfer        |
| 3️⃣  | `HAL_I2C_GetState()`            | Wait until DMA is ready       |

---

## 5. ✅ Summary Table

| HAL Function                    | Role in Project                  |
| ------------------------------- | -------------------------------- |
| `HAL_I2C_Master_Transmit_DMA()` | Sends LCD command/data using DMA |
| `HAL_I2C_GetState()`            | Waits for I2C/DMA to complete    |
| `MX_DMA_Init()`                 | Auto-generated setup for DMA     |

---

This makes your LCD communication more efficient and scalable — useful for real-world applications 🛠️💡
