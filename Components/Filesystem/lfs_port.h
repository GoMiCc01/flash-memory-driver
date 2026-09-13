#pragma once
#include "lfs.h"
#include "flash_high_api.h"

extern struct lfs_config lfs_cfg;
void lfs_port_init(flash_handle* flash);
