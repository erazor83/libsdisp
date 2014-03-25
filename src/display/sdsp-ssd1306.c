/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDSP_SSD1306_C_
#define _SDSP_SSD1306_C_

#include <stdio.h>
#include <stdlib.h>

#include "sdsp-private.h"
#include "sdsp-ssd1306.h"


sdsp_t* sdsp_new_ssd1306(void) {
	sdsp_t *ctx;
	ctx = (sdsp_t *) malloc(sizeof(sdsp_t));
	return ctx;
}



#endif /* _SDSP_SSD1306_C_ */
