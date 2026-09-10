#include "flash_high_api.h"
#include "flash_private.h"
#include "flash_low_api.h"

#define MAX_DEVICE_COUNT 3
#define JEDEC_ID_LEN 3
#define MAX_ERASE_TIME_MS 450

static flash_handle flash_entity [MAX_DEVICE_COUNT];
static uint8_t device_count = 0;

static const flash_device_info_t supported_devices[] = {
    {{0xEF, 0x40, 0x18}, 16 * 1024 * 1024, 4096, 256}, // Winbond W25Q128
    {{0xEF, 0x40, 0x17},  8 * 1024 * 1024, 4096, 256}, // Winbond W25Q64
    {{0xEF, 0x40, 0x16},  4 * 1024 * 1024, 4096, 256}, // Winbond W25Q32
    {{0xC2, 0x20, 0x16},  4 * 1024 * 1024, 4096, 256}  // Macronix MX25L32
};

static flash_status_t flash_wait_ready(flash_handle* flash);
static flash_status_t writeEnable(flash_handle* flash);
static flash_status_t is_device_busy(flash_handle* flash, bool* is_busy);
static flash_status_t getDeviceID(flash_handle* flash, uint8_t* jedec_id);
static flash_status_t flash_auto_detect(flash_handle* flash, uint8_t* new_jedec_id);


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
			new_flash->mem_capacity = 0;
			new_flash->min_erase_size = 0;
			new_flash->page_size = 0;
			device_count++;
		}
	}
	return new_flash;
}

flash_status_t flash_init(flash_handle* flash)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		HAL_Delay(5);
		uint8_t jedec_id[JEDEC_ID_LEN];
		retcode = getDeviceID(flash , jedec_id);
		if(FLASH_OK == retcode)
		{
			retcode = flash_auto_detect(flash , jedec_id);
		}
	}
	return retcode;
}

flash_status_t flash_write_data(flash_handle* flash, uint8_t* write_buff, uint32_t buff_length, uint32_t adr)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash || NULL == write_buff)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		uint32_t remaining_bytes = buff_length;
		while(remaining_bytes > 0)
		{
			uint32_t write_bytes = flash->page_size - (adr%flash->page_size);

			if(write_bytes > remaining_bytes)
			{
				write_bytes = remaining_bytes;
			}

			retcode = writeEnable(flash);
			if(FLASH_OK != retcode)
			{
				break;
			}
			retcode = flash_transmit_data(flash, FLASH_CMD_PAGE_PROGRAM, adr, write_buff, write_bytes);
			if(FLASH_OK != retcode)
			{
				break;
			}
			retcode = flash_wait_ready(flash);
			if(FLASH_OK != retcode)
			{
				break;
			}

			remaining_bytes-=write_bytes;
			adr+=write_bytes;
			write_buff+=write_bytes;

		}
	}
	return retcode;
}

flash_status_t flash_read(flash_handle* flash, uint32_t adr ,uint8_t* data_buffer ,uint32_t buffer_len)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash || NULL == data_buffer)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		retcode = flash_receive_data(flash, FLASH_CMD_READ_DATA, adr, data_buffer, buffer_len);
	}
	return retcode;
}

flash_status_t flash_erase_4kb(flash_handle* flash, uint32_t adr)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		retcode = writeEnable(flash);
		if(FLASH_OK == retcode)
		{
			retcode = flash_cmd_adr(flash, FLASH_CMD_SECTOR_ERASE_4KB, adr);
		}
		if(FLASH_OK == retcode)
		{
			retcode = flash_wait_ready(flash);
		}
	}
	return retcode;
}

static flash_status_t flash_wait_ready(flash_handle* flash)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		bool device_busy = true;
		uint32_t start = HAL_GetTick();
		while(device_busy)
		{
		    retcode = is_device_busy(flash, &device_busy);
		    if(FLASH_OK != retcode)
		    {
		        break;
		    }

		    if((HAL_GetTick() - start) > MAX_ERASE_TIME_MS)
		    {
		        retcode = FLASH_TIMEOUT_ERROR;
		        break;
		    }
		}
	}
	return retcode;
}

static flash_status_t writeEnable(flash_handle* flash)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		retcode = flash_cmd(flash, FLASH_CMD_WRITE_ENABLE);
	}
	return retcode;
}

static flash_status_t is_device_busy(flash_handle* flash, bool* is_busy)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash || NULL == is_busy)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		uint8_t status_register = 0;
		retcode = flash_cmd_receive_data(flash, FLASH_CMD_READ_STATUS_REG_1, &status_register, sizeof(status_register));
		*is_busy = (FLASH_OK == retcode && (status_register & 1))?true:false;
	}
	return retcode;
}

static flash_status_t getDeviceID(flash_handle* flash, uint8_t* jedec_id)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		retcode = flash_cmd_receive_data(flash, FLASH_CMD_JEDEC_ID, jedec_id ,JEDEC_ID_LEN);
		if(FLASH_OK == retcode)
		{
			if((jedec_id[0] == 0 && jedec_id[1] == 0 && jedec_id[2] == 0) ||
			  (jedec_id[0] == 0xFF && jedec_id[1] == 0xFF && jedec_id[2] == 0xFF))
			{
				retcode = FLASH_NOT_INITIALIZED;
			}
		}
	}
	return retcode;
}

static flash_status_t flash_auto_detect(flash_handle* flash, uint8_t* new_jedec_id)
{
	flash_status_t retcode = FLASH_OK;
	if(NULL == flash)
	{
		retcode = FLASH_INVALID_PARAMETERS;
	}
	else
	{
		for(uint8_t i = 0; i < sizeof(supported_devices)/sizeof(supported_devices[0]) ; i++)
		{
			if(supported_devices[i].jedec_id[0] == new_jedec_id[0] &&
			  supported_devices[i].jedec_id[1] == new_jedec_id[1] &&
			  supported_devices[i].jedec_id[2] == new_jedec_id[2])
			{
				flash->mem_capacity = supported_devices[i].mem_capacity;
				flash->min_erase_size = supported_devices[i].min_erase_size;
				flash->page_size = supported_devices[i].page_size;
				break;
			}
		}
		if(0 == flash->mem_capacity)
		{
			retcode = FLASH_UNKNOWN_DEVICE;
		}
	}
	return retcode;
}


