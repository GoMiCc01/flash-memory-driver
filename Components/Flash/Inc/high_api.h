#pragma once

typedef enum
{
	FLASH_NOT_INITIALIZED = 0,
	FLASH_OK
}flash_status_t;

flash_status_t flash_init(void);

flash_status_t flash_write(void);

flash_status_t flash_read(void);

