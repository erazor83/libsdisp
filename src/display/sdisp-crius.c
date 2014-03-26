/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_CRIUS_C_
#define _SDISP_CRIUS_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdisp-private.h"
#include "sdisp-crius.h"

#include "sdisp-crius-test_data.c"

const uint8_t sdisp_crius__init_cmds[] = {
	0xAE,
	0x00,
	0x10,
	0x40,
	0x81,
	0xCF,
	0xA1,
	0xA6,
	0xA8,
	0x3F,
	
	0xD3,
	0x00,
	
	0xD5,
	0x80,
	
	0xD9,
	0xF1,
	
	0xDA,
	0x12,
	
	0xDB,
	0x40,
	
	0x8D,
	0x14,
	
	0xA1,
	0xC8,
	
	0xAF
};

sdisp_t* sdisp_new_crius(uint8_t bus_nr) {
	sdisp_t *ctx;
	ctx = (sdisp_t *) malloc(sizeof(sdisp_t));
	ctx->features			=SDISP_CRIUS_FEATURES;
	ctx->width				=SDISP_CRIUS_WIDTH;
	ctx->height				=SDISP_CRIUS_HEIGHT;
	ctx->type_name		=SDISP_CRIUS_NAME;
	ctx->free					=(void*)&sdisp_crius__free;
	
	
	sdisp_display_crius__data_t* dsp_data;
	dsp_data=malloc(sizeof(sdisp_display_crius__data_t));
	dsp_data->bus_nr=bus_nr;
	dsp_data->i2c_bus=NULL;
	dsp_data->i2c_dev=NULL;
	
	dsp_data->buffer=malloc(SDISP_CRIUS_WIDTH * SDISP_CRIUS_HEIGHT / 8);
	ctx->display_data	=dsp_data;
	
	sdisp_display_calls_t *calls;
	calls=malloc(sizeof(sdisp_display_calls_t));
	calls->init			=(void*)&sdisp_crius__init;
	calls->mov_to		=(void*)&sdisp_crius__mov_to;
	calls->clear		=(void*)&sdisp_crius__clear;
	
	calls->test			=(void*)&sdisp_crius__test;
	calls->invert		=(void*)&sdisp_crius__invert;
	calls->detect		=(void*)&sdisp_crius__detect;
	
	ctx->display_calls=(void*)calls;
	return ctx;
}

int sdisp_crius__cmd(i2c_dev_t* i2c_dev,uint8_t cmd) {
	uint8_t buffer[2];
	buffer[0]=0x80;
	buffer[1]=cmd;
	return i2c_xfer(i2c_dev,sizeof(buffer),buffer,0,NULL);
}

int sdisp_crius__cmds(i2c_dev_t* i2c_dev,uint8_t* cmds,uint8_t len) {
	memmove(cmds+1,cmds,len);
	cmds[0]=0x80;
	return i2c_xfer(i2c_dev,len,cmds,0,NULL);
}

int sdisp_crius__open(sdisp_t* ctx) {
	char path[100];
	int ret;
	sdisp_display_crius__data_t* dsp_data=((sdisp_display_crius__data_t*)(ctx->display_data));
	_sdisp_print_debug(ctx,"Trying to open I2C-Bus...");

	sprintf(
		path,
		"%s%i",
		SDISP_CRIUS_DEV_PATH_PREFIX,
		dsp_data->bus_nr
	);
	_sdisp_print_debug(ctx,path);
	dsp_data->i2c_bus=malloc(sizeof(i2c_bus_t));
	ret=i2c_bus_open(
		dsp_data->i2c_bus,
		path
	);
	if (ret!=0) {
		sprintf(
			path,
			"Error %i while opening bus.",
			ret
		);
		_sdisp_print_debug(ctx,path);
		return ret;
	}
	_sdisp_print_debug(ctx,"Trying to init I2C-Device...");
	dsp_data->i2c_dev=malloc(sizeof(i2c_dev_t));

	i2c_dev_init(
		dsp_data->i2c_dev,
		dsp_data->i2c_bus,
		SDISP_CRIUS_I2C_ADDRESS
	);
	
	return ret;
}
int sdisp_crius__close(sdisp_t* ctx) {
	sdisp_display_crius__data_t* dsp_data=((sdisp_display_crius__data_t*)(ctx->display_data));
	if (dsp_data->i2c_bus) {
		return i2c_bus_close(dsp_data->i2c_bus);
	}
	return 0;
}

int sdisp_crius__free(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"destroying ctx->display_data->buffer...");
	sdisp_display_crius__data_t* dsp_data=ctx->display_data;
	if (dsp_data->i2c_bus != NULL) {
		free(dsp_data->i2c_bus);
	}
	if (dsp_data->i2c_dev != NULL) {
		free(dsp_data->i2c_dev);
	}
	if (dsp_data->buffer != NULL) {
		free(dsp_data->buffer);
	}
	return 0;
}

int sdisp_crius__init(sdisp_t* ctx) {
	int ret;
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->init()...");
	
	ret=sdisp_crius__open(ctx);
	if (ret!=0) {
		return ret;
	}
	
	sdisp_display_crius__data_t* dsp_data=ctx->display_data;
	for (uint8_t i=0; i<sizeof(sdisp_crius__init_cmds);i++) {
		ret=sdisp_crius__cmd(dsp_data->i2c_dev,sdisp_crius__init_cmds[i]);
		if (ret!=0) {
			_sdisp_print_debug(ctx,"error in i2c-transfer while init()");
			return ret;
		}
	}
	
	return 0;
}

int sdisp_crius__mov_to(sdisp_t* ctx,uint8_t x,uint8_t y) {
	uint8_t cmds[]={
		0xB0|y,
		0x80,
		0x00|((8*x)&0x0F),
		0x80,
		0x10|(((8*x)>>4)&0x0F),
		0x00 /*spare for move*/
	};
	
	return sdisp_crius__cmds(
		((sdisp_display_crius__data_t*)(ctx->display_data))->i2c_dev,
		cmds,
		5
	);
}

int sdisp_crius__draw_byte(sdisp_t* ctx,uint8_t data) {
	uint8_t buffer[2];
	buffer[0]=0x40;
	buffer[1]=data;
	
	return i2c_xfer(
		((sdisp_display_crius__data_t*)(ctx->display_data))->i2c_dev,
		sizeof(buffer),
		buffer,
		0,
		NULL
	);
}


int sdisp_crius__clear(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->clear()...");
	for (uint8_t y=0;(y<SDISP_CRIUS_HEIGHT/8);y++) {
		sdisp_crius__mov_to(ctx,0,y);
		for (uint8_t x=0;(x<SDISP_CRIUS_WIDTH);x++) {
			sdisp_crius__draw_byte(ctx,0);
		}
	}
	return 0;
}

int sdisp_crius__detect(sdisp_t* ctx) {
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->detect()...");
	return 0;
}

int sdisp_crius__invert(sdisp_t* ctx) {
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->invert()...");
	return 0;
}
int sdisp_crius__test(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->test()...");
	for (uint8_t y=0;y<(sizeof(sdisp_crius__test_data)/SDISP_CRIUS_WIDTH);y++) {
		sdisp_crius__mov_to(ctx,0,y);
		for (uint8_t x=0;(x<SDISP_CRIUS_WIDTH);x++) {
			sdisp_crius__draw_byte(ctx,sdisp_crius__test_data[x+y*SDISP_CRIUS_WIDTH]);
		}
	}
	return 0;
}

int sdisp_crius__buffer_clear(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->buffer_clear()...");
	sdisp_crius__close(ctx);
	memset(
		((sdisp_display_crius__data_t*)(ctx->display_data))->buffer,
		0,
		(SDISP_CRIUS_WIDTH * SDISP_CRIUS_HEIGHT / 8)
	);
	return 0;
}
int sdisp_crius__buffer_draw(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->buffer_draw()...");
	//TODO
	return 0;
}

#endif /* _SDISP_CRIUS_C_ */
