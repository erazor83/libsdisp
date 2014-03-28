#include <stdio.h>

#include "sdisp.h"

#define I2C_BUS		0

int main(void) {
	sdisp_t *ctx;

	ctx = sdisp_new_crius(I2C_BUS);
	sdisp_set_debug(ctx,SDISP_DEBUG);
	
	sdisp_dump(ctx);
	
	sdisp_display__init(ctx);
	
	sdisp_display__buffer_clear(ctx);
	sdisp_display__buffer_test(ctx);
	sdisp_display__buffer_draw(ctx);

	sdisp_close(ctx);
	sdisp_free(ctx);
}
