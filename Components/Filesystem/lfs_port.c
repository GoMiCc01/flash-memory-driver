/**
 * @file lfs_port.c
 * @brief LittleFS porting layer for the SPI Flash driver.
 *
 * This file translates logical block operations from LittleFS
 * into physical address operations for the SPI Flash driver.
 */

#include "lfs_port.h"
#include "flash_high_api.h"
#include "flash_private.h"

extern flash_handle* my_flash;
struct lfs_config lfs_cfg = {0};

/**
 * @brief Reads data from a logical block.
 *
 * @param c      LittleFS configuration structure.
 * @param block  Logical block number.
 * @param off    Offset within the block.
 * @param buffer Buffer to store the read data.
 * @param size   Number of bytes to read.
 * @return 0 on success, or LFS_ERR_IO on hardware error.
 */
int lfs_flash_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
    uint32_t addr = (block * c->block_size) + off;
    return (flash_read(my_flash, addr, (uint8_t*)buffer, size) == FLASH_OK) ? 0 : LFS_ERR_IO;
}

/**
 * @brief Programs (writes) data to a logical block.
 *
 * @param c      LittleFS configuration structure.
 * @param block  Logical block number.
 * @param off    Offset within the block.
 * @param buffer Data payload to write.
 * @param size   Number of bytes to write.
 * @return 0 on success, or LFS_ERR_IO on hardware error.
 */
int lfs_flash_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
    uint32_t addr = (block * c->block_size) + off;
    return (flash_write_data(my_flash, (const uint8_t*)buffer, size, addr) == FLASH_OK) ? 0 : LFS_ERR_IO;
}

/**
 * @brief Erases a logical block.
 *
 * @param c     LittleFS configuration structure.
 * @param block Logical block number to erase.
 * @return 0 on success, or LFS_ERR_IO on hardware error.
 */
int lfs_flash_erase(const struct lfs_config *c, lfs_block_t block) {
    uint32_t addr = block * c->block_size;
    return (flash_erase_4kb(my_flash, addr) == FLASH_OK) ? 0 : LFS_ERR_IO;
}

/**
 * @brief Synchronizes the state of the storage device.
 *
 * Since this SPI flash driver is blocking and doesn't use background
 * DMA caching for writes, no explicit sync is needed.
 *
 * @param c LittleFS configuration structure.
 * @return Always returns 0.
 */
int lfs_flash_sync(const struct lfs_config *c) {
    return 0;
}

/**
 * @brief Dynamically populates the LittleFS configuration structure.
 *
 * Extracts the auto-detected hardware parameters (page size, block size,
 * capacity) from the initialized flash handle.
 *
 * @param flash Pointer to the initialized flash device instance.
 */
void lfs_port_init(flash_handle* flash)
{
    if (flash == NULL) return;

    lfs_cfg.read  = lfs_flash_read;
    lfs_cfg.prog  = lfs_flash_prog;
    lfs_cfg.erase = lfs_flash_erase;
    lfs_cfg.sync  = lfs_flash_sync;

    lfs_cfg.read_size = 1;
    lfs_cfg.prog_size = flash->page_size;
    lfs_cfg.block_size = flash->min_erase_size;
    lfs_cfg.block_count = flash->mem_capacity / flash->min_erase_size;

    // Cache buffers matching the physical page size for optimal performance
    lfs_cfg.cache_size = flash->page_size;
    lfs_cfg.lookahead_size = 16;
    lfs_cfg.block_cycles = 500;
}
