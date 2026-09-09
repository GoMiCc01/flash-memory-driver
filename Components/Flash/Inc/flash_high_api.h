#pragma once
#include <main.h>

typedef enum
{
	FLASH_NOT_INITIALIZED = 0,
	FLASH_OK,
	FLASH_INVALID_PARAMETERS,
	FLASH_TRANSMIT_ERROR,
	FLASH_RECEIVE_ERROR,
	FLASH_UNKNOWN_DEVICE
}flash_status_t;

typedef struct flash_handles_t flash_handle;

flash_handle* createEntity(SPI_HandleTypeDef* hspi, uint16_t cs_pin , GPIO_TypeDef* cs_port);

flash_status_t flash_init(flash_handle* flash_handle);

flash_status_t flash_write(flash_handle* flash_handle);

flash_status_t flash_read(flash_handle* flash_handle);

