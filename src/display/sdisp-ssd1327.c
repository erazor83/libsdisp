/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_SSD1327Z_C_
#define _SDISP_SSD1327Z_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdisp-private.h"
#include "sdisp-ssd1327.h"
#include "sdisp-i2c_common.h"

#include "ssd1327.h"
#include "buffer.h"

const uint8_t sdisp_ssd1327__init_cmds[] = {
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

sdisp_t* sdisp_new_ssd1327(uint8_t bus_nr) {
	sdisp_t *ctx;
	ctx = sdisp_new_i2c_common(bus_nr,SDISP_SSD1327Z_I2C_ADDRESS);

	ctx->features			=SDISP_SSD1327Z_FEATURES;
	ctx->width				=SDISP_SSD1327Z_WIDTH;
	ctx->height				=SDISP_SSD1327Z_HEIGHT;
	ctx->type_name		=SDISP_SSD1327Z_NAME;

	sdisp_i2c_common__malloc(ctx);

	sdisp_display_calls_t *calls;
	calls=(sdisp_display_calls_t*)(ctx->display_calls);
	calls->init			=(void*)&sdisp_ssd1327__init;
	calls->mov_to		=(void*)&sdisp_ssd1327__mov_to;
	calls->clear		=(void*)&ssd1327__clear;
	
	calls->test			=(void*)&sdisp_ssd1327__test;
	calls->invert		=(void*)&ssd1327__invert;
	calls->detect		=(void*)&sdisp_i2c_common__detect;
	
	ctx->display_calls=(void*)calls;
	return ctx;
}

int sdisp_ssd1327__init(sdisp_t* ctx) {
	return ssd1327__init(ctx,sdisp_ssd1327__init_cmds,sizeof(sdisp_ssd1327__init_cmds));
}
int sdisp_ssd1327__test(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->test()...");
//return ssd1327__fill_display(ctx,sdisp_crius__test_data);
	return -1;
}

int sdisp_ssd1327__mov_to(sdisp_t* ctx,uint8_t x,uint8_t y) {
	uint8_t cmds[]={
		0xB0|y,
		0x80,
		0x00|((8*x)&0x0F),
		0x80,
		0x10|(((8*x)>>4)&0x0F),
		0x00 /*spare for move*/
	};
	
	return ssd1327__cmds(
		((sdisp_display_common_i2c__data_t*)(ctx->display_data))->i2c_dev,
		cmds,
		5
	);
}


#endif /* _SDISP_SSD1327Z_C_ */
