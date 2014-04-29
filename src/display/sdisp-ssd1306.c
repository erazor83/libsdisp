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

#ifndef _SDISP_SSD1306_C_
#define _SDISP_SSD1306_C_

#include <stdio.h>
#include <stdlib.h>

#include "sdisp-private.h"
#include "sdisp-ssd1306.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdisp-private.h"
#include "sdisp-ssd1306.h"
#include "sdisp-i2c_common.h"

#include "buffer.h"

sdisp_t* sdisp_new_ssd1306(uint8_t bus_nr) {
	sdisp_t *ctx;
	ctx = sdisp_new_i2c_common(bus_nr,SDISP_SSD1306_I2C_ADDRESS);
	
	ctx->features			=SDISP_SSD1306_FEATURES;
	ctx->width				=SDISP_SSD1306_WIDTH;
	ctx->height				=SDISP_SSD1306_HEIGHT;
	ctx->type_name		=SDISP_SSD1306_NAME;
	
	sdisp_i2c_common__malloc(ctx);

	sdisp_display_calls_t *calls;
	calls=(sdisp_display_calls_t*)(ctx->display_calls);
	calls->init			=(void*)&sdisp_ssd1306__init;
	calls->mov_to		=(void*)&sdisp_ssd1306__mov_to;
	calls->clear		=(void*)&sdisp_ssd1306__clear;
	
	calls->test			=(void*)&sdisp_ssd1306__test;
	calls->invert		=(void*)&sdisp_ssd1306__invert;
	calls->detect		=(void*)&sdisp_i2c_common__detect;
	
	//calls->_buffer_fill		=(void*)&sdisp_crius__buffer_fill;
	
	calls->buffer_clear		=(void*)&buffer__clear_i2c;
	calls->buffer_draw		=(void*)&buffer__draw_i2c_wmove;
	//calls->buffer_test		=(void*)&sdisp_ssd1306__buffer_test;

	calls->buffer_set_pixel		=(void*)&buffer__set_pixel;
	calls->buffer_set_pixels	=(void*)&buffer__set_pixels;
	
	return ctx;
}

int sdisp_ssd1306__cmd1(i2c_dev_t* i2c_dev,uint8_t c) {
	uint8_t buffer[2];
	buffer[0]=SSD_COMMAND_MODE;
	buffer[1]=c;
	return i2c_xfer(i2c_dev,sizeof(buffer),buffer,0,NULL);
}
int sdisp_ssd1306__cmd2(i2c_dev_t* i2c_dev,uint8_t c1, uint8_t c2) {
	uint8_t buffer[3];
	buffer[0]=SSD_COMMAND_MODE;
	buffer[1]=c1;
	buffer[2]=c2;
	return i2c_xfer(i2c_dev,sizeof(buffer),buffer,0,NULL);
}
int sdisp_ssd1306__cmd3(i2c_dev_t* i2c_dev,uint8_t c1, uint8_t c2, uint8_t c3) {
	uint8_t buffer[4];
	buffer[0]=SSD_COMMAND_MODE;
	buffer[1]=c1;
	buffer[2]=c2;
	buffer[3]=c3;
	return i2c_xfer(i2c_dev,sizeof(buffer),buffer,0,NULL);
}


int sdisp_ssd1306__init(sdisp_t* ctx) {
	int ret;
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->init()...");
	
	ret=sdisp_i2c_common__open(ctx);
	if (ret!=0) {
		return ret;
	}
	
	i2c_dev_t* dev=((sdisp_display_common_i2c__data_t*)(ctx->display_data))->i2c_dev;
	sdisp_ssd1306__cmd1(dev, SSD_DISPLAY_OFF);
	sdisp_ssd1306__cmd2(dev, SSD1306_SETDISPLAYCLOCKDIV, 0x80);
	sdisp_ssd1306__cmd2(dev, SSD1306_SETMULTIPLEX, 0x3F);
	sdisp_ssd1306__cmd2(dev, SSD1306_SETDISPLAYOFFSET, 0x00);
	sdisp_ssd1306__cmd1(dev, SSD1306_SETSTARTLINE);
	sdisp_ssd1306__cmd2(dev, SSD1306_CHARGEPUMP, 0x14); 
	sdisp_ssd1306__cmd2(dev, SSD1306_MEMORYMODE, 0x00);
	sdisp_ssd1306__cmd1(dev, SSD1306_SEGREMAP | 0x1);
	sdisp_ssd1306__cmd1(dev, SSD1306_COMSCANDEC);
	sdisp_ssd1306__cmd2(dev, SSD1306_SETCOMPINS, 0x12);
	sdisp_ssd1306__cmd2(dev, SSD_SET_CONTRAST, 0xFF);
	sdisp_ssd1306__cmd2(dev, SSD1306_SETPRECHARGE, 0xF1);
	sdisp_ssd1306__cmd2(dev, SSD1306_SETVCOMDETECT, 0x40);
	sdisp_ssd1306__cmd1(dev, SSD1306_DISPLAYALLON_RESUME);
	sdisp_ssd1306__cmd1(dev, SSD1306_Normal_Display);

	sdisp_ssd1306__cmd3(dev, 0x21, 0, 127); 
	sdisp_ssd1306__cmd3(dev, 0x22, 0, 7); 
	sdisp_ssd1306__cmd1(dev, SSD_DEACTIVATE_SCROLL);
		
	sdisp_ssd1306__clear(ctx);
	sdisp_ssd1306__buffer_draw(ctx);
	sdisp_ssd1306__cmd1(dev, SSD_DISPLAY_ON);
	return 0;
}

int sdisp_ssd1306__mov_to(sdisp_t* ctx,uint8_t x,uint8_t y) {
	//TODO
	//i2c_dev_t* dev=((sdisp_display_common_i2c__data_t*)(ctx->display_data))->i2c_dev;
	return -1;
}

int sdisp_ssd1306__draw_byte(sdisp_t* ctx,uint8_t data) {
	//TODO
	return -1;
}


int sdisp_ssd1306__clear(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->clear()...");
	sdisp_ssd1306__mov_to(ctx,0,0);
	for (uint8_t y=0;(y<SDISP_SSD1306_HEIGHT/8);y++) {
		for (uint8_t x=0;(x<SDISP_SSD1306_WIDTH);x++) {
			sdisp_ssd1306__draw_byte(ctx,0);
		}
	}
	return 0;
}

int sdisp_ssd1306__invert(sdisp_t* ctx, uint8_t do_invert) {
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->invert()...");
	i2c_dev_t* dev=((sdisp_display_common_i2c__data_t*)(ctx->display_data))->i2c_dev;
	
	if (do_invert) {
		return sdisp_ssd1306__cmd1(dev, SSD_INVERSE_DISPLAY);
	} else {
		return sdisp_ssd1306__cmd1(dev, SSD1306_Normal_Display);
	}
}

int sdisp_ssd1306__test(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->test()...");
	//TODO
	return -1;
}

int sdisp_ssd1306__buffer_draw(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->buffer_draw()...");
	//TODO
	/*
   ssd1306_cmd1(ssd, SSD1306_SETLOWCOLUMN | 0x0);
   ssd1306_cmd1(ssd, SSD1306_SETHIGHCOLUMN | 0x0);
   ssd1306_cmd1(ssd, SSD1306_SETSTARTLINE | 0x0);

   uint8_t *p = ssd->buf;
   uint8_t buf[17] ;
   buf[0] = SSD_DATA_MODE; 
   for (uint16_t i = 0; i < (ssd->width * ssd->height / 8); i += 16) 
   {
      for (uint8_t x = 1; x <= 16; x++) 
         buf[x] = *p++;
      i2c_xfer(ssd->i2c_dev, sizeof(buf), buf, 0, NULL);
   }
   */
	return 0;
}


#endif /* _SDISP_SSD1306_C_ */
