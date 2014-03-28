/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * http://www.seeedstudio.com/wiki/Grove_-_OLED_Display_1.12%22
 */
#ifndef _SDISP_SSD1327Z_H_
#define _SDISP_SSD1327Z_H_

#include <sdisp.h>

#define SDISP_SSD1327Z_FEATURES			SDISP_FEATURE_MONOCHROME | SDISP_FEATURE_GRAPHIC | \
																		SDISP_FEATURE_HAS_DETECT | SDISP_FEATURE_HAS_TEST | \
																		SDISP_FEATURE_HAS_INVERT
#define SDISP_SSD1327Z_WIDTH				96
#define SDISP_SSD1327Z_HEIGHT				96
#define SDISP_SSD1327Z_I2C_ADDRESS	0x3C

#define SDISP_SSD1327Z_NAME					"SSD1327Z-oLED"

sdisp_t* sdisp_new_ssd1327(uint8_t bus_nr);
int sdisp_ssd1327__init(sdisp_t* ctx);
int sdisp_ssd1327__free(sdisp_t* ctx);

int sdisp_ssd1327__test(sdisp_t* ctx);

int sdisp_ssd1327__buffer_clear(sdisp_t* ctx);
int sdisp_ssd1327__buffer_draw(sdisp_t* ctx);

int sdisp_ssd1327__mov_to(sdisp_t* ctx,uint8_t x,uint8_t y);

#endif /* _SDISP_SSD1327Z_H_ */
