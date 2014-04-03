/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdisp-private.h"
#include "sdisp-i2c_common.h"

sdisp_t* sdisp_new_i2c_common(uint8_t bus_nr,uint8_t dev_addr) {
	sdisp_t *ctx;
	ctx = (sdisp_t *) malloc(sizeof(sdisp_t));
	ctx->free					=(void*)&sdisp_i2c_common__free;
	
	sdisp_display_common_i2c__data_t* dsp_data;
	dsp_data=malloc(sizeof(sdisp_display_common_i2c__data_t));
	dsp_data->bus_nr=bus_nr;
	dsp_data->i2c_bus=NULL;
	dsp_data->i2c_dev=NULL;
	dsp_data->dev_address=dev_addr;
	
	ctx->display_data	=dsp_data;
	
	sdisp_display_calls_t *calls;
	calls=malloc(sizeof(sdisp_display_calls_t));
	ctx->display_calls=(void*)calls;
	return ctx;
}

int sdisp_i2c_common__malloc(sdisp_t* ctx) {
	sdisp_display_common_i2c__data_t* dsp_data;
	dsp_data=(sdisp_display_common_i2c__data_t*)(ctx->display_data);
	if (ctx->features & SDISP_FEATURE_BOOLCHROME) {
		dsp_data->buffer=malloc(ctx->width * ctx->height / 8);
	} else {
		dsp_data->buffer=malloc(ctx->width * ctx->height);
	}
	if (dsp_data->buffer!=NULL) {
		return 0;
	} else {
		return -1;
	}
}

int sdisp_i2c_common__detect(sdisp_t* ctx) {
	//checks if the display exists
	_sdisp_print_debug(ctx,"display->detect()...");
	i2c_dev_t* dev=((sdisp_display_common_i2c__data_t*)(ctx->display_data))->i2c_dev;
	if (i2c_read(dev)==0) {
		_sdisp_print_debug(ctx,"display found");
		return 0;
	} else {
		_sdisp_print_debug(ctx,"display not found");
		return -1;
	}
}


int sdisp_i2c_common__open(sdisp_t* ctx) {
	char path[100];
	int ret;
	sdisp_display_common_i2c__data_t* dsp_data=((sdisp_display_common_i2c__data_t*)(ctx->display_data));
	_sdisp_print_debug(ctx,"Trying to open I2C-Bus...");

	sprintf(
		path,
		"%s%i",
		SDISP_I2C_DEV_PATH_PREFIX,
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
		dsp_data->dev_address
	);
	
	return ret;
}
int sdisp_i2c_common__close(sdisp_t* ctx) {
	sdisp_display_common_i2c__data_t* dsp_data=((sdisp_display_common_i2c__data_t*)(ctx->display_data));
	if (dsp_data->i2c_bus) {
		return i2c_bus_close(dsp_data->i2c_bus);
	}
	return 0;
}


int sdisp_i2c_common__free(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"destroying ctx->display_data->buffer...");
	sdisp_display_common_i2c__data_t* dsp_data=ctx->display_data;
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
