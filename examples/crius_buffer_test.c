#include <stdio.h>

#include "sdisp.h"

int main (int argc, char *argv[]) {
	uint8_t i2c_address;
	sdisp_t *ctx;

	if (argc != 2) {
		printf("usage: crius_clear <bus>\n");
		return -1;
	}

	i2c_address=atol(argv[1]);
	ctx = sdisp_new_crius(i2c_address);

	sdisp_set_debug(ctx,SDISP_DEBUG);
	
	sdisp_dump(ctx);
	
	sdisp_display__init(ctx);
	
	sdisp_display__buffer_clear(ctx);
	sdisp_display__buffer_test(ctx);
	sdisp_display__buffer_draw(ctx);

	sdisp_close(ctx);
	sdisp_free(ctx);
}
