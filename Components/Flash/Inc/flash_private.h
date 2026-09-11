#pragma once
#include "flash_high_api.h"

#define FLASH_CMD_WRITE_ENABLE                   0x06
#define FLASH_CMD_VOLATILE_SR_WRITE_ENABLE       0x50
#define FLASH_CMD_WRITE_DISABLE                  0x04
#define FLASH_CMD_RELEASE_POWER_DOWN_ID          0xAB
#define FLASH_CMD_MANUFACTURER_DEVICE_ID         0x90
#define FLASH_CMD_JEDEC_ID                       0x9F
#define FLASH_CMD_READ_UNIQUE_ID                 0x4B
#define FLASH_CMD_READ_DATA                      0x03
#define FLASH_CMD_FAST_READ                      0x0B
#define FLASH_CMD_PAGE_PROGRAM                   0x02
#define FLASH_CMD_SECTOR_ERASE_4KB               0x20
#define FLASH_CMD_BLOCK_ERASE_32KB               0x52
#define FLASH_CMD_BLOCK_ERASE_64KB               0xD8
#define FLASH_CMD_CHIP_ERASE_C7                  0xC7
#define FLASH_CMD_CHIP_ERASE_60                  0x60
#define FLASH_CMD_READ_STATUS_REG_1              0x05
#define FLASH_CMD_WRITE_STATUS_REG_1             0x01
#define FLASH_CMD_READ_STATUS_REG_2              0x35
#define FLASH_CMD_WRITE_STATUS_REG_2             0x31
#define FLASH_CMD_READ_STATUS_REG_3              0x15
#define FLASH_CMD_WRITE_STATUS_REG_3             0x11
#define FLASH_CMD_READ_SFDP_REGISTER             0x5A
#define FLASH_CMD_ERASE_SECURITY_REGISTER        0x44
#define FLASH_CMD_PROGRAM_SECURITY_REGISTER      0x42
#define FLASH_CMD_READ_SECURITY_REGISTER         0x48
#define FLASH_CMD_GLOBAL_BLOCK_LOCK              0x7E
#define FLASH_CMD_GLOBAL_BLOCK_UNLOCK            0x98
#define FLASH_CMD_READ_BLOCK_LOCK                0x3D
#define FLASH_CMD_INDIVIDUAL_BLOCK_LOCK          0x36
#define FLASH_CMD_INDIVIDUAL_BLOCK_UNLOCK        0x39
#define FLASH_CMD_ERASE_PROGRAM_SUSPEND          0x75
#define FLASH_CMD_ERASE_PROGRAM_RESUME           0x7A
#define FLASH_CMD_POWER_DOWN                     0xB9
#define FLASH_CMD_ENABLE_RESET                   0x66
#define FLASH_CMD_RESET_DEVICE                   0x99


typedef struct
{
	uint8_t jedec_id [3];
	uint32_t mem_capacity;
	uint16_t min_erase_size;
	uint16_t page_size;
}flash_device_info_t;

struct flash_handles_t
{
	uint16_t cs_pin;
	SPI_HandleTypeDef* hspi;
	GPIO_TypeDef* cs_port;
	uint32_t mem_capacity;
	uint16_t page_size;
	uint16_t min_erase_size;
};
