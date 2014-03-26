/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDSP_CRIUS_C_
#define _SDSP_CRIUS_C_

#include <stdio.h>
#include <stdlib.h>

#include "sdsp-private.h"
#include "sdsp-crius.h"

sdsp_t* sdsp_new_crius(void) {
	sdsp_t *ctx;
	ctx = (sdsp_t *) malloc(sizeof(sdsp_t));
	ctx->features			=SDSP_CRIUS_FEATURES;
	ctx->width				=SDSP_CRIUS_WIDTH;
	ctx->height				=SDSP_CRIUS_HEIGHT;
	ctx->type_name		=SDSP_CRIUS_NAME;
	
	sdsp_display_calls_t *calls;
	calls=malloc(sizeof(sdsp_display_calls_t));
	calls->init			=(void*)&sdsp_crius_init;
	calls->test			=(void*)&sdsp_crius_test;
	calls->invert		=(void*)&sdsp_crius_invert;
	calls->detect		=(void*)&sdsp_crius_detect;
	
	ctx->display_calls=(void*)calls;
	return ctx;
}

int sdsp_crius_init(sdsp_t* ctx) {
	//checks if the display exists
	_sdsp_print_debug(ctx,"display->init()...");
	return 0;
}

int sdsp_crius_detect(sdsp_t* ctx) {
	//checks if the display exists
	_sdsp_print_debug(ctx,"display->detect()...");
	return 0;
}

int sdsp_crius_invert(sdsp_t* ctx) {
	//checks if the display exists
	_sdsp_print_debug(ctx,"display->invert()...\n");
	return 0;
}
int sdsp_crius_test(sdsp_t* ctx) {
	//checks if the display exists
	_sdsp_print_debug(ctx,"display->test()...\n");
	return 0;
}

#endif /* _SDSP_CRIUS_C_ */
