#include "flash_high_api.h"
#include "flash_private.h"

#define MAX_DEVICE_COUNT 3

static flash_handle flash_entity [MAX_DEVICE_COUNT];
static uint8_t device_count = 0;

flash_handle* createEntity(SPI_HandleTypeDef* hspi, uint16_t cs_pin , GPIO_TypeDef* cs_port)
{
	flash_handle* new_flash = NULL;
	if(NULL!= hspi && NULL!= cs_port)
	{
		if(device_count < MAX_DEVICE_COUNT)
		{
			new_flash = &flash_entity[device_count];
			new_flash->cs_pin = cs_pin;
			new_flash->cs_port = cs_port;
			new_flash->hspi = hspi;
			device_count++;
		}
	}
	return new_flash;
}

flash_status_t flash_init(flash_handle* flash_handle){}


