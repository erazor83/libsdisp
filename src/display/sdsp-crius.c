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
	ctx->features=SDSP_CRIUS_FEATURES;
	ctx->width=SDSP_CRIUS_WIDTH;
	ctx->height=SDSP_CRIUS_HEIGHT;
	ctx->type_name=SDSP_CRIUS_NAME;
	return ctx;
}

int sdsp_crius_dump_name(const char* name) {
	//TODO
}


#endif /* _SDSP_CRIUS_C_ */
