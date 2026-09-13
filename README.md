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
```

## LittleFS Integration (File System)
This driver is ready to be used with LittleFS right out of the box. A porting layer (`lfs_port.c` / `lfs_port.h`) is provided to link the flash driver with the file system dynamically.

```c
#include "lfs.h"
#include "lfs_port.h"

lfs_t lfs;
lfs_file_t file;

if (flash_init(my_flash) == FLASH_OK) {
    
    // 1. Load the detected flash sizes into LittleFS config
    lfs_port_init(my_flash); 
    
    // 2. Mount the file system (format automatically if it's empty)
    if (lfs_mount(&lfs, &lfs_cfg) != 0) {
        lfs_format(&lfs, &lfs_cfg);
        lfs_mount(&lfs, &lfs_cfg);
    }

    // 3. Create and write to a standard file!
    lfs_file_open(&lfs, &file, "boot_count.txt", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_write(&lfs, &file, "System booted!", 14);
    lfs_file_close(&lfs, &file);
}  
```  

## How to Add to Your Project
1. Copy the `Components/Flash` folder into your STM32CubeIDE project.
2. Go to **Properties -> C/C++ Build -> Settings -> Tool Settings -> Include paths** and add the path to the copied folder.
3. (Optional) If you want to use files, download the LittleFS library and include the `Components/FileSystem` adapter.

## Documentation
The source code is fully documented using Doxygen.
To generate the web documentation locally:

1. Open a terminal in the project root.
2. Run `doxygen Doxyfile`.
3. Open `html/index.html` in your favorite web browser.
