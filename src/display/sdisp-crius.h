/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDSP_CRIUS_H_
#define _SDSP_CRIUS_H_

#include <sdsp.h>

#define SDSP_CRIUS_FEATURES					SDSP_FEATURE_MONOCHROME | SDSP_FEATURE_GRAPHIC | \
																		SDSP_FEATURE_HAS_DETECT | SDSP_FEATURE_HAS_TEST | \
																		SDSP_FEATURE_HAS_INVERT
#define SDSP_CRIUS_WIDTH						128
#define SDSP_CRIUS_HEIGHT						64
#define SDSP_CRIUS_I2C_ADDRESS			0

#define SDSP_CRIUS_DEV_PATH_PREFIX	"/dev/i2c-"

#define SDSP_CRIUS_NAME							"Crius-oLED"

#include "i2c/i2c.h"

typedef struct _sdsp_crius_display_data {
		i2c_bus_t*	i2c_bus;
		i2c_dev_t*	i2c_dev;
		uint8_t			bus_nr;
//		uint8_t			dev_address;
		uint8_t* 		buffer;
} sdsp_crius_display_data_t;


sdsp_t* sdsp_new_crius(uint8_t bus_nr);
int sdsp_crius_init(sdsp_t* ctx);
int sdsp_crius_free(sdsp_t* ctx);

int sdsp_crius_open_bus(sdsp_t* ctx);
int sdsp_crius_close_bus(sdsp_t* ctx);


int sdsp_crius_detect(sdsp_t* ctx);
int sdsp_crius_invert(sdsp_t* ctx);
int sdsp_crius_test(sdsp_t* ctx);

int sdsp_crius_buffer_clear(sdsp_t* ctx);
int sdsp_crius_buffer_draw(sdsp_t* ctx);


#endif /* _SDSP_CRIUS_H_ */
