#pragma once
#include "flash_high_api.h"

struct flash_handles_t
{
	uint16_t cs_pin;
	SPI_HandleTypeDef* hspi;
	GPIO_TypeDef* cs_port;
};
