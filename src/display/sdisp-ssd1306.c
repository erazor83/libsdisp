/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_SSD1306_C_
#define _SDISP_SSD1306_C_

#include <stdio.h>
#include <stdlib.h>

#include "sdisp-private.h"
#include "sdisp-ssd1306.h"


sdisp_t* sdisp_new_ssd1306(void) {
	sdisp_t *ctx;
	ctx = (sdisp_t *) malloc(sizeof(sdisp_t));
	return ctx;
}



#endif /* _SDISP_SSD1306_C_ */
