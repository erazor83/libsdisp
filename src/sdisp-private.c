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

#include "sdisp.h"
#include "sdisp-private.h"


void _sdisp_print_debug(sdisp_t *ctx, const char *txt) {
	if (ctx->debug) {
		if ((ctx == NULL) || (ctx->type_name==NULL)) {
			printf("[NULL] %s\n",txt);
		} else {
			printf("[%s] %s\n",ctx->type_name,txt);
		}
	}
}
