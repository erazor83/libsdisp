/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_BUFFER_H_
#define _SDISP_BUFFER_H_

#include <sdisp.h>
//for sdisp_display_common_i2c__data_t
int buffer__clear_i2c(sdisp_t* ctx); 


int buffer__fill(sdisp_t* ctx,uint8_t* p,uint16_t len, uint8_t* data);


int buffer__draw_i2c(sdisp_t* ctx);
int buffer__draw_i2c_wmove(sdisp_t* ctx); //draw with move-instruction

int buffer__set_pixel (sdisp_t *ctx,uint16_t x,uint16_t y,uint8_t color);

int buffer__set_pixels (sdisp_t *ctx,uint16_t start,uint16_t len, uint8_t* color);
#endif /* _SDISP_BUFFER_H_ */
