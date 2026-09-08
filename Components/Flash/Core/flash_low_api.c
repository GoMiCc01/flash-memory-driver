#include "flash_low_api.h"

flash_status_t flash_cmd(flash_handle* flash, uint8_t cmd)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
	HAL_GPIO_WritePin(flash->cs_port, flash->cs_pin, GPIO_PIN_RESET);
	if(HAL_OK != HAL_SPI_Transmit(flash->hspi, &cmd, sizeof(cmd), FLASH_SPI_TIMEOUT_MS))
	{
		retcode = FLASH_TRANSMIT_ERROR;
	}
	HAL_GPIO_WritePin(flash->cs_port, flash->cs_pin, GPIO_PIN_SET);
	}
	return retcode;
}

flash_status_t flash_cmd_adr(flash_handle* flash, uint8_t cmd, uint32_t adr)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		uint8_t transm_data [FLASH_ADDRESS_LEN];
		transm_data[0] = cmd;
		transm_data[1] = (adr >> 16)&0xFF;
		transm_data[2] = (adr >> 8)&0xFF;
		transm_data[3] = adr & 0xFF;
		HAL_GPIO_WritePin(flash->cs_port, flash->cs_pin, GPIO_PIN_RESET);
		if(HAL_OK != HAL_SPI_Transmit(flash->hspi, transm_data, sizeof(transm_data), FLASH_SPI_TIMEOUT_MS))
		{
			retcode = FLASH_TRANSMIT_ERROR;
		}

		HAL_GPIO_WritePin(flash->cs_port, flash->cs_pin, GPIO_PIN_SET);
	}
	return retcode;
}

flash_status_t flash_transmit_data(flash_handle* flash, uint8_t cmd, uint32_t adr , const uint8_t* const data , uint16_t len)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash || NULL == data)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		uint8_t transm_data [FLASH_ADDRESS_LEN];
		transm_data[0] = cmd;
		transm_data[1] = (adr >> 16)&0xFF;
		transm_data[2] = (adr >> 8)&0xFF;
		transm_data[3] = adr & 0xFF;
		HAL_GPIO_WritePin(flash->cs_port, flash->cs_pin, GPIO_PIN_RESET);
		if(HAL_OK != HAL_SPI_Transmit(flash->hspi, transm_data, sizeof(transm_data), FLASH_SPI_TIMEOUT_MS))
		{
			retcode = FLASH_TRANSMIT_ERROR;
		}

		if(HAL_OK != HAL_SPI_Transmit(flash->hspi, (uint8_t*)data, len, FLASH_SPI_TIMEOUT_MS))
		{
			retcode = FLASH_TRANSMIT_ERROR;
		}

		HAL_GPIO_WritePin(flash->cs_port, flash->cs_pin, GPIO_PIN_SET);
	}
	return retcode;
}

flash_status_t flash_receive_data(flash_handle* flash, uint8_t cmd, uint32_t adr ,uint8_t* data , uint16_t len)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash || NULL == data)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		uint8_t transm_data [FLASH_ADDRESS_LEN];
		transm_data[0] = cmd;
		transm_data[1] = (adr >> 16)&0xFF;
		transm_data[2] = (adr >> 8)&0xFF;
		transm_data[3] = adr & 0xFF;
		HAL_GPIO_WritePin(flash->cs_port, flash->cs_pin, GPIO_PIN_RESET);
		if(HAL_OK != HAL_SPI_Transmit(flash->hspi, transm_data, sizeof(transm_data), FLASH_SPI_TIMEOUT_MS))
		{
			retcode = FLASH_TRANSMIT_ERROR;
		}

		if(HAL_OK != HAL_SPI_Receive(flash->hspi, data, len, FLASH_SPI_TIMEOUT_MS))
		{
			retcode = FLASH_RECEIVE_ERROR;
		}

		HAL_GPIO_WritePin(flash->cs_port, flash->cs_pin, GPIO_PIN_SET);
	}
	return retcode;
}
