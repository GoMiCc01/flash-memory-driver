# SPI Flash Memory Driver

A lightweight, hardware-abstracted C driver for SPI NOR Flash memories, optimized for STM32 microcontrollers (STM32 HAL).

## Features
* **Supported Devices:** GigaDevice GD25Q32, Winbond W25Q32 / W25Q64 / W25Q128, Macronix MX25L32.
* **Auto-detection:** Automatically reads the JEDEC ID and configures memory geometry (capacity, page size).
* **Cross-page writing:** Automatically handles writing across page boundaries.
* **API Levels:** Separated into High, Low, and Private APIs for clean architecture.

## Basic Usage

```c
#include "flash_high_api.h"

// 1. Create a flash instance (bind to SPI peripheral and CS pin)
flash_handle* my_flash = createEntity(&hspi1, FLASH_CS_Pin, FLASH_CS_GPIO_Port);

// 2. Initialize and detect device
if (flash_init(my_flash) == FLASH_OK) {
    
    // 3. Erase a sector before writing
    flash_erase_4kb(my_flash, 0x000000);
    
    // 4. Write data
    const uint8_t test_data[] = "Hello from GD25Q32!";
    flash_write_data(my_flash, test_data, sizeof(test_data), 0x000000);
    
    // 5. Read data back
    uint8_t read_buffer[64] = {0};
    flash_read(my_flash, 0x000000, read_buffer, sizeof(test_data));
}