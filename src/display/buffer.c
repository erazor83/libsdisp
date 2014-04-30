/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sdisp-private.h"
#include "sdisp-i2c_common.h"

#include "buffer.h"


int buffer__clear_i2c(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->buffer_clear()...");
	memset(
		((sdisp_display_common_i2c__data_t*)(ctx->display_data))->buffer,
		0,
		(ctx->width * ctx->height / 8)
	);
	return 0;
}

int buffer__draw_i2c_wmove(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->buffer_draw()...");
	
	sdisp_display_common_i2c__data_t* display_data=(sdisp_display_common_i2c__data_t*)(ctx->display_data);
	uint8_t *p=display_data->buffer;
	
	sdisp_display_calls_t *calls;
	calls=(sdisp_display_calls_t*)(ctx->display_calls);
	
	for (uint8_t y=0;y<((ctx->height)/8);y++) {
		calls->mov_to(ctx,0,y);
		for (uint8_t x=0;(x<(ctx->width));x++) {
			display_data->_draw_byte(ctx,*(p++));
		}
	}
	return 0;
}

int buffer__draw_i2c(sdisp_t* ctx) {
	_sdisp_print_debug(ctx,"display->buffer_draw()...");
	
	sdisp_display_common_i2c__data_t* display_data=(sdisp_display_common_i2c__data_t*)(ctx->display_data);
	uint8_t *p=display_data->buffer;
	
	for (uint8_t y=0;y<((ctx->height)/8);y++) {
		for (uint8_t x=0;(x<(ctx->width));x++) {
			display_data->_draw_byte(ctx,*(p++));
		}
	}
	return 0;
}

int buffer__fill(sdisp_t* ctx,uint8_t* p,uint16_t len, uint8_t* data) {
	while (len--) {
		*(p++)=*(data++);
	}
	return len;
}

int buffer__set_pixel(sdisp_t *ctx,uint16_t x,uint16_t y,uint8_t color) {
	sdisp_display_common_i2c__data_t* display_data=(sdisp_display_common_i2c__data_t*)(ctx->display_data);
	uint8_t* p=display_data->buffer;
	
	if (1) {
		//if color is b/w
		p+=(x+(y/8)*ctx->width);
		if (color) {
			*p|= (1<<(y%8));
		} else {
			*p&=~(1<<(y%8));
		}
	} else {
		//if color is grey-scale
		p[x+y*ctx->width]=color;
	}
	return 0;
}

int buffer__set_pixels(sdisp_t *ctx,uint16_t start,uint16_t len, uint8_t* color) {
	sdisp_display_common_i2c__data_t* display_data=(sdisp_display_common_i2c__data_t*)(ctx->display_data);
	uint8_t *p=display_data->buffer;
	
	uint16_t pixel_count=(ctx->width*ctx->height)/8;
	if (((start+len)/8)<pixel_count) {
		if (1) {
			uint16_t x=start%ctx->width;
			uint16_t y=start/ctx->width;
			p+=(x+(y/8)*ctx->width);
			while (len--) {
				if (color) {
					*p|= (1<<(y%8));
				} else {
					*p&=~(1<<(y%8));
				}
				x++;
				p++;
				if (x==ctx->width) {
					x=0;
					y++;
				}
			}
		}
		return 0;
	} else {
		return -1;
	}
}

