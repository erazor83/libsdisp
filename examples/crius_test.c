#include <stdio.h>

#include "sdisp.h"

#define I2C_BUS		1

int main(void) {
	sdisp_t *ctx;

	ctx = sdisp_new_crius(I2C_BUS);
	sdisp_set_debug(ctx,SDSP_DEBUG);
	
	sdisp_dump(ctx);
	
	sdisp_display_init(ctx);
	//sdisp_clear(ctx);
	
	sdisp_display_test(ctx);
	
	sdisp_close(ctx);
	sdisp_free(ctx);
}
