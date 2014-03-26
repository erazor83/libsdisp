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

#include "sdsp.h"
#include "sdsp-private.h"

int8_t sdsp_display_init(sdsp_t *ctx){
	sdsp_display_calls_t* calls;
	
	if ((ctx != NULL) && 
			(ctx->display_calls != NULL)) {
		calls=(sdsp_display_calls_t*)(ctx->display_calls);
	}
	if (calls->init != NULL) {
		return calls->init(ctx);
	}
	return -1;
}

int8_t sdsp_display_test(sdsp_t *ctx){
	sdsp_display_calls_t* calls;
	
	if ((ctx != NULL) && 
			(ctx->display_calls != NULL)) {
		calls=(sdsp_display_calls_t*)(ctx->display_calls);
	}
	if (calls->test != NULL) {
		return calls->test(ctx);
	}
	return -1;
}

int8_t sdsp_display_clear(sdsp_t *ctx){
	sdsp_display_calls_t* calls;
	
	if ((ctx != NULL) && 
			(ctx->display_calls != NULL)) {
		calls=(sdsp_display_calls_t*)(ctx->display_calls);
	}
	if (calls->test != NULL) {
		return calls->clear(ctx);
	}
	return -1;
}


void sdsp_dump(sdsp_t* ctx) {
	printf("name:     %s\n",ctx->type_name);
	printf("width:    %i\n",ctx->width);
	printf("height:   %i\n",ctx->height);
	printf("features: 0x%04x\n",ctx->features);
	
	
	if (ctx->features & SDSP_FEATURE_HAS_DETECT)  {
		printf("  * SDSP_FEATURE_HAS_DETECT\n");
	}
	if (ctx->features & SDSP_FEATURE_HAS_TEST)  {
		printf("  * SDSP_FEATURE_HAS_TEST\n");
	}
	if (ctx->features & SDSP_FEATURE_GRAPHIC)  {
		printf("  * SDSP_FEATURE_GRAPHIC\n");
	}
	if (ctx->features & SDSP_FEATURE_MONOCHROME)  {
		printf("  * SDSP_FEATURE_MONOCHROME\n");
	}
	if (ctx->features & SDSP_FEATURE_HAS_INVERT)  {
		printf("  * SDSP_FEATURE_HAS_INVERT\n");
	}
}

void sdsp_close(sdsp_t *ctx) {
	if (ctx == NULL) {
		return;
	}

	//ctx->display_data->close(ctx);
}

void sdsp_free(sdsp_t *ctx) {
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

void sdsp_set_debug(sdsp_t *ctx, bool value) {
	ctx->debug = value;
}

