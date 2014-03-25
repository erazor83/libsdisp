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


void sdsp_close(sdsp_t *ctx) {
	if (ctx == NULL) {
		return;
	}

	ctx->backend->close(ctx);
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


#endif
