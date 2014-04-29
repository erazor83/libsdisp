/*___________________________________________________
 |  _____                       _____ _ _       _    |
 | |  __ \                     |  __ (_) |     | |   |
 | | |__) |__ _ __   __ _ _   _| |__) || | ___ | |_  |
 | |  ___/ _ \ '_ \ / _` | | | |  ___/ | |/ _ \| __| |
 | | |  |  __/ | | | (_| | |_| | |   | | | (_) | |_  |
 | |_|   \___|_| |_|\__, |\__,_|_|   |_|_|\___/ \__| |
 |                   __/ |                           |
 |  GNU/Linux based |___/  Multi-Rotor UAV Autopilot |
 |___________________________________________________|
  
 Adafruit 128x64 SSD1307 Linux I2C Driver Implementation

 Copyright (C) 2013 Tobias Simon, Ilmenau University of Technology
 Copyright (C) 2014 Alexander Krause <alexander.krause@ed-solutions.de
 
 Based on code written by Limor Fried/Ladyada.  

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details. */

#ifndef _SDISP_SSD1306_H_
#define _SDISP_SSD1306_H_


#include <sdisp.h>

#include "sdisp-i2c_common.h"

#define SDISP_SSD1306_FEATURES			SDISP_FEATURE_GRAPHIC | \
																		SDISP_FEATURE_HAS_DETECT | SDISP_FEATURE_HAS_TEST | \
																		SDISP_FEATURE_HAS_INVERT
#define SDISP_SSD1306_WIDTH						128
#define SDISP_SSD1306_HEIGHT					64
#define SDISP_SSD1306_I2C_ADDRESS			0x3C

#define SDISP_SSD1306_NAME						"SSD1306-oLED"

#include "i2c/i2c.h"

/* internal declarations: */

#define SSD_COMMAND_MODE      0x00
#define SSD_DATA_MODE         0x40
#define SSD_INVERSE_DISPLAY   0xA7
#define SSD_DISPLAY_OFF       0xAE
#define SSD_DISPLAY_ON        0xAF
#define SSD_SET_CONTRAST      0x81
#define SSD_EXTERNAL_VCC      0x01
#define SSD_INTERNAL_VCC      0x02
#define SSD_DEACTIVATE_SCROLL 0x2E

#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON        0xA5
#define SSD1306_Normal_Display      0xA6

#define SSD1306_SETDISPLAYOFFSET    0xD3
#define SSD1306_SETCOMPINS          0xDA
#define SSD1306_SETVCOMDETECT       0xDB
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5
#define SSD1306_SETPRECHARGE        0xD9
#define SSD1306_SETMULTIPLEX        0xA8
#define SSD1306_SETLOWCOLUMN        0x00
#define SSD1306_SETHIGHCOLUMN       0x10
#define SSD1306_SETSTARTLINE        0x40
#define SSD1306_MEMORYMODE          0x20
#define SSD1306_COMSCANINC          0xC0
#define SSD1306_COMSCANDEC          0xC8
#define SSD1306_SEGREMAP            0xA0
#define SSD1306_CHARGEPUMP          0x8D



sdisp_t* sdisp_new_ssd1306(uint8_t bus_nr);
int sdisp_ssd1306__init(sdisp_t* ctx);
int sdisp_ssd1306__free(sdisp_t* ctx);

int sdisp_ssd1306__draw_byte(sdisp_t* ctx,uint8_t data);
int sdisp_ssd1306__clear(sdisp_t* ctx);

int sdisp_ssd1306__invert(sdisp_t* ctx,uint8_t do_invert);
int sdisp_ssd1306__test(sdisp_t* ctx);

int sdisp_ssd1306__buffer_clear(sdisp_t* ctx);
int sdisp_ssd1306__buffer_draw(sdisp_t* ctx);

int sdisp_ssd1306__cmd1(i2c_dev_t* i2c_dev,uint8_t c);
int sdisp_ssd1306__cmd2(i2c_dev_t* i2c_dev,uint8_t c1,uint8_t c2);
int sdisp_ssd1306__cmd3(i2c_dev_t* i2c_dev,uint8_t c1,uint8_t c2,uint8_t c3);

int sdisp_ssd1306__mov_to(sdisp_t* ctx,uint8_t x,uint8_t y);


#endif /* _SDISP_SSD1306_H_ */
