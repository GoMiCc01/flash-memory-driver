#pragma once
#include "flash_private.h"

/** @brief Default SPI communication timeout in milliseconds */
#define FLASH_SPI_TIMEOUT_MS 500U

/** @brief Length of command (1 byte) + address (3 bytes) */
#define FLASH_ADDRESS_LEN 4U

/**
 * @brief Sends a single 1-byte command to the flash memory.
 *
 * @param flash Pointer to the flash instance
 * @param cmd   Command code (e.g., Write Enable)
 * @return FLASH_OK on success
 */
flash_status_t flash_cmd(flash_handle* flash, uint8_t cmd);

/**
 * @brief Sends a command followed by a 24-bit address.
 *
 * @param flash Pointer to the flash instance
 * @param cmd   Command code (e.g., Sector Erase)
 * @param adr   24-bit target address
 * @return FLASH_OK on success
 */
flash_status_t flash_cmd_adr(flash_handle* flash, uint8_t cmd, uint32_t adr);

/**
 * @brief Sends a command and reads a response back.
 *
 * @param flash Pointer to the flash instance
 * @param cmd   Command code (e.g., Read Status Register)
 * @param data  Buffer to store the received data
 * @param len   Number of bytes to receive
 * @return FLASH_OK on success
 */
flash_status_t flash_cmd_receive_data(flash_handle* flash, uint8_t cmd, uint8_t* data, uint16_t len);

/**
 * @brief Sends a command, a 24-bit address, and a data payload.
 *
 * @param flash Pointer to the flash instance
 * @param cmd   Command code (e.g., Page Program)
 * @param adr   24-bit target address
 * @param data  Pointer to the data payload
 * @param len   Number of bytes to transmit
 * @return FLASH_OK on success
 */
flash_status_t flash_transmit_data(flash_handle* flash,
                                   uint8_t cmd,
                                   uint32_t adr,
                                   const uint8_t* const data,
                                   uint32_t len);

/**
 * @brief Sends a command, a 24-bit address, and reads a data payload.
 *
 * @param flash Pointer to the flash instance
 * @param cmd   Command code (e.g., Read Data)
 * @param adr   24-bit target address
 * @param data  Buffer to store the received data
 * @param len   Number of bytes to read
 * @return FLASH_OK on success
 */
flash_status_t flash_receive_data(flash_handle* flash,
                                  uint8_t cmd,
                                  uint32_t adr,
                                  uint8_t* data,
                                  uint32_t len);
