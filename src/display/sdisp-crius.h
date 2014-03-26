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
#define SDISP_CRIUS_HEIGHT						64
#define SDISP_CRIUS_I2C_ADDRESS			0

#define SDISP_CRIUS_DEV_PATH_PREFIX	"/dev/i2c-"

#define SDISP_CRIUS_NAME							"Crius-oLED"

#include "i2c/i2c.h"

typedef struct _sdisp_crius_display_data {
		i2c_bus_t*	i2c_bus;
		i2c_dev_t*	i2c_dev;
		uint8_t			bus_nr;
//		uint8_t			dev_address;
		uint8_t* 		buffer;
} sdisp_crius_display_data_t;


sdisp_t* sdisp_new_crius(uint8_t bus_nr);
int sdisp_crius_init(sdisp_t* ctx);
int sdisp_crius_free(sdisp_t* ctx);

int sdisp_crius_open_bus(sdisp_t* ctx);
int sdisp_crius_close_bus(sdisp_t* ctx);


int sdisp_crius_detect(sdisp_t* ctx);
int sdisp_crius_invert(sdisp_t* ctx);
int sdisp_crius_test(sdisp_t* ctx);

int sdisp_crius_buffer_clear(sdisp_t* ctx);
int sdisp_crius_buffer_draw(sdisp_t* ctx);


#endif /* _SDISP_CRIUS_H_ */
