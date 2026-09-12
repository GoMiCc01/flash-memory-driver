/**
 * @file flash_high_api.h
 * @brief High-level API for SPI Flash memory operations.
 */

#pragma once
#include <main.h>
#include <string.h>

/**
 * @brief Flash driver status codes
 */
typedef enum
{
	FLASH_NOT_INITIALIZED = 0, ///< Driver is not initialized
	FLASH_OK,                  ///< Operation successful
	FLASH_INVALID_PARAMETERS,  ///< Invalid arguments passed (e.g., NULL pointer)
	FLASH_TRANSMIT_ERROR,      ///< SPI transmit failed
	FLASH_RECEIVE_ERROR,       ///< SPI receive failed
	FLASH_UNKNOWN_DEVICE,      ///< Unsupported or missing JEDEC ID
	FLASH_TIMEOUT_ERROR        ///< Timeout while waiting for flash operation
} flash_status_t;

typedef struct flash_handles_t flash_handle;

/**
 * @brief Allocates and configures a new flash device instance.
 *
 * @param hspi    Pointer to the SPI handle
 * @param cs_pin  Chip Select pin number
 * @param cs_port Pointer to the Chip Select GPIO port
 * @return Pointer to the initialized flash handle, or NULL if limit reached
 */
flash_handle* createEntity(SPI_HandleTypeDef* hspi, uint16_t cs_pin, GPIO_TypeDef* cs_port);

/**
 * @brief Initializes the flash memory and auto-detects its geometry.
 *
 * @param flash_handle Pointer to the flash instance
 * @return FLASH_OK on success, or specific error code
 */
flash_status_t flash_init(flash_handle* flash_handle);

/**
 * @brief Writes data to flash memory. Handles page boundaries automatically.
 *
 * @param flash       Pointer to the flash instance
 * @param write_buff  Pointer to the data payload
 * @param buff_length Number of bytes to write
 * @param adr         Target memory address (must be erased before writing)
 * @return FLASH_OK on success
 */
flash_status_t flash_write_data(flash_handle* flash, const uint8_t* write_buff, uint32_t buff_length, uint32_t adr);

/**
 * @brief Reads a sequence of bytes from flash memory.
 *
 * @param flash       Pointer to the flash instance
 * @param adr         Starting memory address
 * @param data_buffer Buffer to store the read data
 * @param buffer_len  Number of bytes to read
 * @return FLASH_OK on success
 */
flash_status_t flash_read(flash_handle* flash, uint32_t adr, uint8_t* data_buffer, uint32_t buffer_len);

/**
 * @brief Erases a single 4KB sector.
 *
 * @param flash Pointer to the flash instance
 * @param adr   Address inside the target sector (should be 4KB aligned)
 * @return FLASH_OK on success
 */
flash_status_t flash_erase_4kb(flash_handle* flash, uint32_t adr);
