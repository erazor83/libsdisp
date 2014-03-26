#include <stdio.h>

#include "sdisp.h"

#define I2C_BUS		0

int main(void) {
	sdisp_t *ctx;

	ctx = sdisp_new_crius(I2C_BUS);
	
	sdisp_display__init(ctx);
	sdisp_display__clear(ctx);
	
	
	sdisp_close(ctx);
	sdisp_free(ctx);
}
