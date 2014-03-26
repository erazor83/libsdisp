/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_CRIUS_H_
#define _SDISP_CRIUS_H_

#include <sdisp.h>

#define SDISP_CRIUS_FEATURES					SDISP_FEATURE_MONOCHROME | SDISP_FEATURE_GRAPHIC | \
																		SDISP_FEATURE_HAS_DETECT | SDISP_FEATURE_HAS_TEST | \
																		SDISP_FEATURE_HAS_INVERT
#define SDISP_CRIUS_WIDTH						128
#define SDISP_CRIUS_HEIGHT					64
#define SDISP_CRIUS_I2C_ADDRESS			0x3C

#define SDISP_CRIUS_DEV_PATH_PREFIX	"/dev/i2c-"

#define SDISP_CRIUS_NAME						"Crius-oLED"

#include "i2c/i2c.h"

typedef struct _sdisp_display_crius__data {
		i2c_bus_t*	i2c_bus;
		i2c_dev_t*	i2c_dev;
		uint8_t			bus_nr;
//		uint8_t			dev_address;
		uint8_t* 		buffer;
} sdisp_display_crius__data_t;


sdisp_t* sdisp_new_crius(uint8_t bus_nr);
int sdisp_crius__init(sdisp_t* ctx);
int sdisp_crius__free(sdisp_t* ctx);

int sdisp_crius__open_bus(sdisp_t* ctx);
int sdisp_crius__close_bus(sdisp_t* ctx);

int sdisp_crius__draw_byte(sdisp_t* ctx,uint8_t data);
int sdisp_crius__clear(sdisp_t* ctx);

int sdisp_crius__detect(sdisp_t* ctx);
int sdisp_crius__invert(sdisp_t* ctx);
int sdisp_crius__test(sdisp_t* ctx);

int sdisp_crius__buffer_clear(sdisp_t* ctx);
int sdisp_crius__buffer_draw(sdisp_t* ctx);

int sdisp_crius__cmd(i2c_dev_t* i2c_dev,uint8_t cmd);
int sdisp_crius__cmds(i2c_dev_t* i2c_dev,uint8_t* cmds,uint8_t len);

int sdisp_crius__mov_to(sdisp_t* ctx,uint8_t x,uint8_t y);

#endif /* _SDISP_CRIUS_H_ */
