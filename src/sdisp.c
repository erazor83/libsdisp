/*
 * Copyright (C) 2014 Alexander Krause <alexander.krause@ed-solutions.de>
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

/* Exported version */
const unsigned int libsdisp_version_major = LIBSDISP_VERSION_MAJOR;
const unsigned int libsdisp_version_minor = LIBSDISP_VERSION_MINOR;
const unsigned int libsdisp_version_micro = LIBSDISP_VERSION_MICRO;

//preprocessor-magic... hurray!!!
#define STRUCT_ACCESS_OP(name)				calls->name
#define SDISP_INTERFACE_CODE(__name__)	\
	sdisp_display_calls_t* calls;			\
																		\
	if ((ctx != NULL) && 							\
			(ctx->display_calls != NULL)) {										\
		calls=(sdisp_display_calls_t*)(ctx->display_calls);	\
	}																											\
	if (STRUCT_ACCESS_OP(__name__) != NULL) {			\
		return STRUCT_ACCESS_OP(__name__)(ctx);			\
	}																											\
	return -1;
	
#define SDISP_INTERFACE_CODE_ARGS(__name__, ...)	\
	sdisp_display_calls_t* calls;			\
																		\
	if ((ctx != NULL) && 							\
			(ctx->display_calls != NULL)) {										\
		calls=(sdisp_display_calls_t*)(ctx->display_calls);	\
	}																											\
	if (STRUCT_ACCESS_OP(__name__) != NULL) {			\
		return STRUCT_ACCESS_OP(__name__)(ctx, __VA_ARGS__);			\
	}																											\
	return -1;

int16_t sdisp_display__getWidth(sdisp_t *ctx){
	return ctx->width;
}
int16_t sdisp_display__getHeight(sdisp_t *ctx){
	return ctx->height;
}
FEATURES_TYPE sdisp_display__getFeatures(sdisp_t *ctx){
	return ctx->features;
}

int8_t sdisp_display__init(sdisp_t *ctx){
	SDISP_INTERFACE_CODE(init);
}

int8_t sdisp_display__test(sdisp_t *ctx){
	SDISP_INTERFACE_CODE(test);
}

int8_t sdisp_display__detect(sdisp_t *ctx){
	SDISP_INTERFACE_CODE(detect);
}

int8_t sdisp_display__clear(sdisp_t *ctx){
	SDISP_INTERFACE_CODE(clear);
}

int8_t sdisp_display__mov_to(sdisp_t *ctx,uint8_t x,uint8_t y){
	SDISP_INTERFACE_CODE_ARGS(mov_to, x, y);
}

/*
int8_t sdisp_display__buffer_set_pixel_mc(sdisp_t *ctx,uint8_t x,uint8_t y,uint8_t color){
	SDISP_INTERFACE_CODE_ARGS(buffer_set_pixel_mc,x,y,color);
}*/


int8_t sdisp_display__buffer_draw(sdisp_t *ctx){
	SDISP_INTERFACE_CODE(buffer_draw);
}

int8_t sdisp_display__buffer_clear(sdisp_t *ctx){
	SDISP_INTERFACE_CODE(buffer_clear);
}

int8_t sdisp_display__buffer_test(sdisp_t *ctx){
	SDISP_INTERFACE_CODE(buffer_test);
}

int8_t sdisp_display__buffer_set_pixel(sdisp_t *ctx,uint16_t x, uint16_t y, uint8_t color){
	SDISP_INTERFACE_CODE_ARGS(buffer_set_pixel,x,y,color);
}

int8_t sdisp_display__buffer_set_pixels(sdisp_t *ctx,uint16_t start, uint16_t len, uint8_t* color){
	SDISP_INTERFACE_CODE_ARGS(buffer_set_pixels,start,len,color);
}

#define SDISP_CHECK_FEATURE_PRINT(feature,feature_str)					\
	if (ctx->features & feature)  {																\
		printf("  * %s\n",feature_str);									\
	}

void sdisp_dump(sdisp_t* ctx) {
	printf("name:     %s\n",ctx->type_name);
	printf("width:    %i\n",ctx->width);
	printf("height:   %i\n",ctx->height);
	printf("features: 0x%04x\n",ctx->features);
	
	SDISP_CHECK_FEATURE_PRINT(SDISP_FEATURE_HAS_DETECT,"SDISP_FEATURE_HAS_DETECT");
	SDISP_CHECK_FEATURE_PRINT(SDISP_FEATURE_HAS_TEST,"SDISP_FEATURE_HAS_TEST");
	SDISP_CHECK_FEATURE_PRINT(SDISP_FEATURE_GRAPHIC,"SDISP_FEATURE_GRAPHIC");
	SDISP_CHECK_FEATURE_PRINT(SDISP_FEATURE_MONOCHROME,"SDISP_FEATURE_MONOCHROME");
	SDISP_CHECK_FEATURE_PRINT(SDISP_FEATURE_HAS_INVERT,"SDISP_FEATURE_HAS_INVERT");
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

