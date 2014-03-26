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

sdisp_t* sdisp_new_crius(uint8_t bus_nr) {
	sdisp_t *ctx;
	ctx = (sdisp_t *) malloc(sizeof(sdisp_t));
	ctx->features			=SDISP_CRIUS_FEATURES;
	ctx->width				=SDISP_CRIUS_WIDTH;
	ctx->height				=SDISP_CRIUS_HEIGHT;
	ctx->type_name		=SDISP_CRIUS_NAME;
	ctx->free					=(void*)&sdisp_crius_free;
	
	
	sdisp_crius_display_data_t* dsp_data;
	dsp_data=malloc(sizeof(sdisp_crius_display_data_t));
	dsp_data->bus_nr=bus_nr;
	dsp_data->i2c_bus=NULL;
	dsp_data->i2c_dev=NULL;
	
	dsp_data->buffer=malloc(SDISP_CRIUS_WIDTH * SDISP_CRIUS_HEIGHT / 8);
	ctx->display_data	=dsp_data;
	
	sdisp_display_calls_t *calls;
	calls=malloc(sizeof(sdisp_display_calls_t));
	calls->init			=(void*)&sdisp_crius_init;
	calls->test			=(void*)&sdisp_crius_test;
	calls->invert		=(void*)&sdisp_crius_invert;
	calls->detect		=(void*)&sdisp_crius_detect;
	
	ctx->display_calls=(void*)calls;
	return ctx;
}

int sdisp_crius_open(sdisp_t* ctx) {
	char path[100];
	int ret;
	sdisp_crius_display_data_t* dsp_data=((sdisp_crius_display_data_t*)(ctx->display_data));
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
int sdisp_crius_close(sdisp_t* ctx) {
	sdisp_crius_display_data_t* dsp_data=((sdisp_crius_display_data_t*)(ctx->display_data));
	if (dsp_data->i2c_bus) {
		return i2c_bus_close(dsp_data->i2c_bus);
	}
	return 0;
}

int sdisp_crius_free(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"destroying ctx->display_data->buffer...");
	sdisp_crius_display_data_t* dsp_data=ctx->display_data;
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

int sdisp_crius_init(sdisp_t* ctx) {
	int ret;
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->init()...");
	
	ret=sdisp_crius_open(ctx);
	if (ret!=0) {
		return ret;
	}
		
	
	char info[100];
	sprintf(
		info,
		"using bus %i",
		((sdisp_crius_display_data_t*)(ctx->display_data))->bus_nr
	);
	_sdisp_print_debug(ctx,info);
	return 0;
}

int sdisp_crius_detect(sdisp_t* ctx) {
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->detect()...");
	return 0;
}

int sdisp_crius_invert(sdisp_t* ctx) {
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->invert()...");
	return 0;
}
int sdisp_crius_test(sdisp_t* ctx) {
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->test()...");
	return 0;
}

int sdisp_crius_buffer_clear(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->buffer_clear()...");
	sdisp_crius_close(ctx);
	memset(
		((sdisp_crius_display_data_t*)(ctx->display_data))->buffer,
		0,
		(SDISP_CRIUS_WIDTH * SDISP_CRIUS_HEIGHT / 8)
	);
	return 0;
}
int sdisp_crius_buffer_draw(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->buffer_draw()...");
	//TODO
	return 0;
}

#endif /* _SDISP_CRIUS_C_ */
