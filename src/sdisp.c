/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

#include "compat.c"

#include "sdisp.h"
#include "sdisp-private.h"

int8_t sdisp_display__init(sdisp_t *ctx){
	sdisp_display_calls_t* calls;
	
	if ((ctx != NULL) && 
			(ctx->display_calls != NULL)) {
		calls=(sdisp_display_calls_t*)(ctx->display_calls);
	}
	if (calls->init != NULL) {
		return calls->init(ctx);
	}
	return -1;
}

int8_t sdisp_display__test(sdisp_t *ctx){
	sdisp_display_calls_t* calls;
	
	if ((ctx != NULL) && 
			(ctx->display_calls != NULL)) {
		calls=(sdisp_display_calls_t*)(ctx->display_calls);
	}
	if (calls->test != NULL) {
		return calls->test(ctx);
	}
	return -1;
}

int8_t sdisp_display__clear(sdisp_t *ctx){
	sdisp_display_calls_t* calls;
	
	if ((ctx != NULL) && 
			(ctx->display_calls != NULL)) {
		calls=(sdisp_display_calls_t*)(ctx->display_calls);
	}
	if (calls->clear != NULL) {
		return calls->clear(ctx);
	}
	return -1;
}

int8_t sdisp_display__mov_to(sdisp_t *ctx,uint8_t x,uint8_t y){
	sdisp_display_calls_t* calls;
	
	if ((ctx != NULL) && 
			(ctx->display_calls != NULL)) {
		calls=(sdisp_display_calls_t*)(ctx->display_calls);
	}
	if (calls->mov_to != NULL) {
		return calls->mov_to(ctx,x,y);
	}
	return -1;
}


void sdisp_dump(sdisp_t* ctx) {
	printf("name:     %s\n",ctx->type_name);
	printf("width:    %i\n",ctx->width);
	printf("height:   %i\n",ctx->height);
	printf("features: 0x%04x\n",ctx->features);
	
	
	if (ctx->features & SDISP_FEATURE_HAS_DETECT)  {
		printf("  * SDISP_FEATURE_HAS_DETECT\n");
	}
	if (ctx->features & SDISP_FEATURE_HAS_TEST)  {
		printf("  * SDISP_FEATURE_HAS_TEST\n");
	}
	if (ctx->features & SDISP_FEATURE_GRAPHIC)  {
		printf("  * SDISP_FEATURE_GRAPHIC\n");
	}
	if (ctx->features & SDISP_FEATURE_MONOCHROME)  {
		printf("  * SDISP_FEATURE_MONOCHROME\n");
	}
	if (ctx->features & SDISP_FEATURE_HAS_INVERT)  {
		printf("  * SDISP_FEATURE_HAS_INVERT\n");
	}
}

void sdisp_close(sdisp_t *ctx) {
	if (ctx == NULL) {
		return;
	}

	//ctx->display_data->close(ctx);
}

void sdisp_free(sdisp_t *ctx) {
	if (ctx == NULL) {
		return;
	}

	if (ctx->free != NULL) {
		ctx->free(ctx);
	}
	
	if (ctx->display_data != NULL) {
		free(ctx->display_data);
	}
	free(ctx);
}

void sdisp_set_debug(sdisp_t *ctx, bool value) {
	ctx->debug = value;
}

