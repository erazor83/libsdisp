/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_I2C_COMMON_H_
#define _SDISP_I2C_COMMON_H_


#include <sdisp.h>

#include "i2c/i2c.h"

#define SDISP_I2C_DEV_PATH_PREFIX	"/dev/i2c-"

typedef struct _sdisp_display_common_i2c__data {
		i2c_bus_t*	i2c_bus;
		i2c_dev_t*	i2c_dev;
		uint8_t			bus_nr;
		uint8_t			dev_address;
		uint8_t* 		buffer;
		int					(*_draw_byte) (sdisp_t *ctx, uint8_t byte);
		
} sdisp_display_common_i2c__data_t;


sdisp_t* sdisp_new_i2c_common(uint8_t bus_nr,uint8_t dev_addr);
int sdisp_i2c_common__malloc(sdisp_t* ctx);
int sdisp_i2c_common__detect(sdisp_t* ctx);
int sdisp_i2c_common__open(sdisp_t* ctx);
int sdisp_i2c_common__close(sdisp_t* ctx);
int sdisp_i2c_common__free(sdisp_t* ctx);

#endif /* _SDISP_SSD1306_H_ */
