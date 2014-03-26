#include <stdio.h>

#include "sdsp.h"

#define I2C_BUS		1

int main(void) {
	sdsp_t *ctx;

	ctx = sdsp_new_crius(I2C_BUS);
	sdsp_set_debug(ctx,SDSP_DEBUG);
	
	sdsp_dump(ctx);
	
	sdsp_display_init(ctx);
	//sdsp_clear(ctx);
	
	sdsp_display_test(ctx);
	
	sdsp_close(ctx);
	sdsp_free(ctx);
}
