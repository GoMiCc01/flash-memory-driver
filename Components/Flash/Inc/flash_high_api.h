#pragma once
#include <main.h>

typedef enum
{
	FLASH_NOT_INITIALIZED = 0,
	FLASH_OK,
	FLASH_INVALID_PARAMETERS,
	FLASH_TRANSMIT_ERROR,
	FLASH_RECEIVE_ERROR,
	FLASH_UNKNOWN_DEVICE,
	FLASH_TIMEOUT_ERROR
}flash_status_t;

typedef struct flash_handles_t flash_handle;

flash_handle* createEntity(SPI_HandleTypeDef* hspi, uint16_t cs_pin , GPIO_TypeDef* cs_port);

flash_status_t flash_init(flash_handle* flash_handle);

flash_status_t flash_write_data(flash_handle* flash, uint8_t* write_buff, uint32_t buff_length, uint32_t adr);

flash_status_t flash_read(flash_handle* flash, uint32_t adr ,uint8_t* data_buffer ,uint32_t buffer_len);

flash_status_t flash_erase_4kb(flash_handle* flash, uint32_t adr);

