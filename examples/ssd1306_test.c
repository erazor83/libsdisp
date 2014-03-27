#include <stdio.h>

#include "sdisp.h"


int main(void) {
	sdisp_t *ctx;

	ctx = sdisp_new_ssd1306();

	sdisp_set_debug(ctx,SDISP_DEBUG);
	
	sdisp_display__init(ctx);
	sdisp_display__clear(ctx);
	
	sdisp_display__test(ctx);
	
	sdisp_close(ctx);
	sdisp_free(ctx);
}
