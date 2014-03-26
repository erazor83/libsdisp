/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 */


#ifndef _SDSP_PRIVATE_H_
#define _SDSP_PRIVATE_H_

#ifndef _MSC_VER
# include <stdint.h>
# include <sys/time.h>
#else
# include "stdint.h"
# include <time.h>
typedef int ssize_t;
#endif
#include <sys/types.h>

#include "sdsp.h"

SDSP_BEGIN_DECLS


typedef enum {
	_SDSP_BACKEND_TYPE_RTU=0
} sdsp_bakend_type_t;


typedef struct _sdsp_display {

	int8_t (*select) (sdsp_t *ctx);
		
	int8_t (*init) (sdsp_t *ctx);
	int8_t (*invert) (sdsp_t *ctx);
	int8_t (*update) (sdsp_t *ctx);
	int8_t (*clear) (sdsp_t *ctx);
	int8_t (*set_pixel) (sdsp_t *ctx);
	
} sdsp_backend_t;

struct _sdsp {
	uint8_t width;
	uint8_t height;
	const char* type_name;
	uint16_t features;

	/* Socket or file descriptor */
	bool debug;
	void *display_data;
};

void _sdsp_init_common(sdsp_t *ctx);
void _error_print(sdsp_t *ctx, const char *context);
void sdsp_free(sdsp_t *ctx);

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dest, const char *src, size_t dest_size);
#endif

SDSP_END_DECLS

#endif  /* _SDSP_PRIVATE_H_ */
