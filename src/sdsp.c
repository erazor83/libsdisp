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

int8_t sdsp_init(sdsp_t *ctx){
	//TODO
	return -1;
}
void sdsp_test(sdsp_t *ctx){
	//TODO
}
void sdsp_clear(sdsp_t *ctx){
	//TODO
}


void sdsp_dump(sdsp_t* ctx) {
	printf("name:     %s\n",ctx->type_name);
	printf("width:    %i\n",ctx->width);
	printf("height:   %i\n",ctx->height);
	printf("features: 0x%04x\n",ctx->features);
	if (ctx->features & SDSP_FEATURE_GRAPHIC)  {
		printf("  * SDSP_FEATURE_GRAPHIC\n");
	}
	if (ctx->features & SDSP_FEATURE_MONOCHROME)  {
		printf("  * SDSP_FEATURE_MONOCHROME\n");
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

	if (ctx->display_data != NULL) {
		free(ctx->display_data);
	}
	free(ctx);
}

void sdsp_set_debug(sdsp_t *ctx, bool value) {
	ctx->debug = value;
}

