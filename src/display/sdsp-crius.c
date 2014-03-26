/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDSP_CRIUS_C_
#define _SDSP_CRIUS_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdsp-private.h"
#include "sdsp-crius.h"

sdsp_t* sdsp_new_crius(uint8_t bus_nr) {
	sdsp_t *ctx;
	ctx = (sdsp_t *) malloc(sizeof(sdsp_t));
	ctx->features			=SDSP_CRIUS_FEATURES;
	ctx->width				=SDSP_CRIUS_WIDTH;
	ctx->height				=SDSP_CRIUS_HEIGHT;
	ctx->type_name		=SDSP_CRIUS_NAME;
	ctx->free					=(void*)&sdsp_crius_free;
	
	
	sdsp_crius_display_data_t* dsp_data;
	dsp_data=malloc(sizeof(sdsp_crius_display_data_t));
	dsp_data->bus_nr=bus_nr;
	dsp_data->i2c_bus=NULL;
	dsp_data->i2c_dev=NULL;
	
	dsp_data->buffer=malloc(SDSP_CRIUS_WIDTH * SDSP_CRIUS_HEIGHT / 8);
	ctx->display_data	=dsp_data;
	
	sdsp_display_calls_t *calls;
	calls=malloc(sizeof(sdsp_display_calls_t));
	calls->init			=(void*)&sdsp_crius_init;
	calls->test			=(void*)&sdsp_crius_test;
	calls->invert		=(void*)&sdsp_crius_invert;
	calls->detect		=(void*)&sdsp_crius_detect;
	
	ctx->display_calls=(void*)calls;
	return ctx;
}

int sdsp_crius_open(sdsp_t* ctx) {
	char path[100];
	int ret;
	sdsp_crius_display_data_t* dsp_data=((sdsp_crius_display_data_t*)(ctx->display_data));
	_sdsp_print_debug(ctx,"Trying to open I2C-Bus...");

	sprintf(
		path,
		"%s%i",
		SDSP_CRIUS_DEV_PATH_PREFIX,
		dsp_data->bus_nr
	);
	_sdsp_print_debug(ctx,path);
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
		_sdsp_print_debug(ctx,path);
		return ret;
	}
	_sdsp_print_debug(ctx,"Trying to init I2C-Device...");
	dsp_data->i2c_dev=malloc(sizeof(i2c_dev_t));

	i2c_dev_init(
		dsp_data->i2c_dev,
		dsp_data->i2c_bus,
		SDSP_CRIUS_I2C_ADDRESS
	);
	
	return ret;
}
int sdsp_crius_close(sdsp_t* ctx) {
	sdsp_crius_display_data_t* dsp_data=((sdsp_crius_display_data_t*)(ctx->display_data));
	if (dsp_data->i2c_bus) {
		return i2c_bus_close(dsp_data->i2c_bus);
	}
	return 0;
}

int sdsp_crius_free(sdsp_t* ctx) {
	_sdsp_print_debug(ctx,"destroying ctx->display_data->buffer...");
	sdsp_crius_display_data_t* dsp_data=ctx->display_data;
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

int sdsp_crius_init(sdsp_t* ctx) {
	int ret;
	//checks if the display exists
	_sdsp_print_debug(ctx,"display->init()...");
	
	ret=sdsp_crius_open(ctx);
	if (ret!=0) {
		return ret;
	}
		
	
	char info[100];
	sprintf(
		info,
		"using bus %i",
		((sdsp_crius_display_data_t*)(ctx->display_data))->bus_nr
	);
	_sdsp_print_debug(ctx,info);
	return 0;
}

int sdsp_crius_detect(sdsp_t* ctx) {
	//checks if the display exists
	_sdsp_print_debug(ctx,"display->detect()...");
	return 0;
}

int sdsp_crius_invert(sdsp_t* ctx) {
	//checks if the display exists
	_sdsp_print_debug(ctx,"display->invert()...");
	return 0;
}
int sdsp_crius_test(sdsp_t* ctx) {
	//checks if the display exists
	_sdsp_print_debug(ctx,"display->test()...");
	return 0;
}

int sdsp_crius_buffer_clear(sdsp_t* ctx) {
	_sdsp_print_debug(ctx,"display->buffer_clear()...");
	sdsp_crius_close(ctx);
	memset(
		((sdsp_crius_display_data_t*)(ctx->display_data))->buffer,
		0,
		(SDSP_CRIUS_WIDTH * SDSP_CRIUS_HEIGHT / 8)
	);
	return 0;
}
int sdsp_crius_buffer_draw(sdsp_t* ctx) {
	_sdsp_print_debug(ctx,"display->buffer_draw()...");
	//TODO
	return 0;
}

#endif /* _SDSP_CRIUS_C_ */
