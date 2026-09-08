#pragma once
#include "flash_private.h"

#define FLASH_SPI_TIMEOUT_MS 500U
#define FLASH_ADDRESS_LEN 4U

flash_status_t flash_cmd(flash_handle* flash, uint8_t cmd);

flash_status_t flash_cmd_adr(flash_handle* flash, uint8_t cmd, uint32_t adr);

flash_status_t flash_transmit_data(flash_handle* flash,
								  uint8_t cmd,
								  uint32_t adr ,
								  const uint8_t* const data ,
								  uint16_t len);

flash_status_t flash_receive_data(flash_handle* flash,
								  uint8_t cmd,
								  uint32_t adr ,
								  uint8_t* data ,
								  uint16_t len);
