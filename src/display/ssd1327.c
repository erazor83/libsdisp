/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdisp-private.h"
#include "sdisp-i2c_common.h"

#include "ssd1327.h"


int ssd1327__cmd(i2c_dev_t* i2c_dev,uint8_t cmd) {
	uint8_t buffer[2];
	buffer[0]=SSD1327_MODE_COMMAND;
	buffer[1]=cmd;
	return i2c_xfer(i2c_dev,sizeof(buffer),buffer,0,NULL);
}

int ssd1327__cmds(i2c_dev_t* i2c_dev,uint8_t* cmds,uint8_t len) {
	memmove(cmds+1,cmds,len);
	cmds[0]=SSD1327_MODE_COMMAND;
	return i2c_xfer(i2c_dev,len,cmds,0,NULL);
}

int ssd1327__init(sdisp_t* ctx, const uint8_t* init_cmds, uint8_t len) {
	int ret;
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->init()...");
	
	ret=sdisp_i2c_common__open(ctx);
	if (ret!=0) {
		return ret;
	}
	
	sdisp_display_common_i2c__data_t* dsp_data=ctx->display_data;
	for (uint8_t i=0; i<len;i++) {
		ret=ssd1327__cmd(dsp_data->i2c_dev,init_cmds[i]);
		if (ret!=0) {
			_sdisp_print_debug(ctx,"error in i2c-transfer while init()");
			return ret;
		}
	}
	
	return 0;
}

int ssd1327__write_byte(sdisp_t* ctx,uint8_t data) {
	uint8_t buffer[2];
	buffer[0]=SSD1327_MODE_DATA;
	buffer[1]=data;
	
	return i2c_xfer(
		((sdisp_display_common_i2c__data_t*)(ctx->display_data))->i2c_dev,
		sizeof(buffer),
		buffer,
		0,
		NULL
	);
}

int ssd1327__invert(sdisp_t* ctx, uint8_t do_invert) {
	//checks if the display exists
	//TODO
	_sdisp_print_debug(ctx,"display->invert()...");
	return 0;
}

int ssd1327__clear(sdisp_t* ctx) {
	uint16_t width=ctx->width;
	uint8_t height=ctx->height;
	
	_sdisp_print_debug(ctx,"display->clear()...");
	sdisp_display_calls_t *calls;
	calls=(sdisp_display_calls_t*)(ctx->display_calls);
	
	if (ctx->features & SDISP_FEATURE_BOOLCHROME) {
		width=width*8;
	}
	
	for (uint8_t y=0;y<(height/8);y++) {
		calls->mov_to(ctx,0,y);
		for (uint16_t x=0;x<width;x++) {
			ssd1327__write_byte(ctx,0);
		}
	}
	return 0;
}

int ssd1327__fill_display(sdisp_t* ctx, const uint8_t* data) {
	uint16_t width=ctx->width;
	uint8_t height=ctx->height;
	sdisp_display_calls_t *calls;
	calls=(sdisp_display_calls_t*)(ctx->display_calls);
	
	if (ctx->features & SDISP_FEATURE_BOOLCHROME) {
		width=width*8;
	}
	for (uint8_t y=0;y<height/8;y++) {
		calls->mov_to(ctx,0,y);
		for (uint16_t x=0;x<width;x++) {
			ssd1327__write_byte(ctx,data[x+y*width]);
		}
	}
	return 0;
}