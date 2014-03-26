/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 */


#ifndef _SDISP_PRIVATE_H_
#define _SDISP_PRIVATE_H_

#ifndef _MSC_VER
# include <stdint.h>
# include <sys/time.h>
#else
# include "stdint.h"
# include <time.h>
typedef int ssize_t;
#endif
#include <sys/types.h>

#include "sdisp.h"

typedef struct _sdisp_display_calls {
		
	int (*init) (sdisp_t *ctx);
	int (*mov_to) (sdisp_t *ctx,uint8_t x,uint8_t y);
	int (*clear) (sdisp_t *ctx);
	
	int (*detect) (sdisp_t *ctx);
	int (*invert) (sdisp_t *ctx);
	int (*test) (sdisp_t *ctx);
	
	int (*set_pixel) (sdisp_t *ctx);
	
	int (*buffer_draw) (sdisp_t *ctx);
	int (*buffer_clear) (sdisp_t *ctx);

	
} sdisp_display_calls_t;

struct _sdisp {
	uint8_t width;
	uint8_t height;
	const char* type_name;
	uint16_t features;


	int8_t (*free) (sdisp_t *ctx);
	/* Socket or file descriptor */
	bool debug;
	void *display_data;
	void *display_calls;
};

//void _sdisp_init_common(sdisp_t *ctx);
void sdisp_free(sdisp_t *ctx);

void _sdisp_print_debug(sdisp_t *ctx, const char *txt);

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dest, const char *src, size_t dest_size);
#endif


#endif  /* _SDISP_PRIVATE_H_ */
