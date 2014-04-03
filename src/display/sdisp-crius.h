/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_CRIUS_H_
#define _SDISP_CRIUS_H_

#include <sdisp.h>

#define SDISP_CRIUS_FEATURES					SDISP_FEATURE_BOOLCHROME | SDISP_FEATURE_GRAPHIC | \
																		SDISP_FEATURE_HAS_DETECT | SDISP_FEATURE_HAS_TEST | \
																		SDISP_FEATURE_HAS_INVERT
#define SDISP_CRIUS_WIDTH						128
#define SDISP_CRIUS_HEIGHT					64
#define SDISP_CRIUS_I2C_ADDRESS			0x3C

#define SDISP_CRIUS_NAME						"Crius-oLED"

#include "i2c/i2c.h"

#define SDISP_CRIUS_MODE_COMMAND				0x80
#define SDISP_CRIUS_MODE_DATA						0x40

sdisp_t* sdisp_new_crius(uint8_t bus_nr);
int sdisp_crius__init(sdisp_t* ctx);
int sdisp_crius__mov_to(sdisp_t* ctx,uint8_t x,uint8_t y);

int sdisp_crius__test(sdisp_t* ctx);

int sdisp_crius__buffer_fill(sdisp_t* ctx,uint8_t start, uint8_t len, uint8_t* data);
int sdisp_crius__buffer_test(sdisp_t* ctx);

#endif /* _SDISP_CRIUS_H_ */
