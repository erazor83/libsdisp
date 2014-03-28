/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SSD1327_H_
#define _SSD1327_H_

#include <sdisp.h>

#include "i2c/i2c.h"

#define SSD1327Z_VERTICAL_MODE				01
#define SSD1327Z_HORIZONTAL_MODE			02

#define SSD1327_MODE_COMMAND					0x80
#define SSD1327_MODE_DATA							0x40

#define SSD1327_CMD_OFF								0xAE
#define SSD1327_CMD_ON								0xAF

#define SSD1327_CMD_INVERSE_NORMAL		0xA4
#define SSD1327_CMD_INVERSE_INVERSE		0xA7
#define SSD1327_CMD_SCROLL_ACTIVATE		0x2F
#define SSD1327_CMD_SCROLL_DEACTIVATE	0x2E
#define SSD1327_CMD_SET_CONTRAST			0x81

int ssd1327__cmd(i2c_dev_t* i2c_dev,uint8_t cmd);
int ssd1327__cmds(i2c_dev_t* i2c_dev,uint8_t* cmds,uint8_t len);

int ssd1327__init(sdisp_t* ctx, const uint8_t* init_cmds, uint8_t len);
int ssd1327__draw_byte(sdisp_t* ctx,uint8_t data);
int ssd1327__clear(sdisp_t* ctx);

int ssd1327__invert(sdisp_t* ctx, uint8_t do_invert);

int ssd1327__fill_display(sdisp_t* ctx, const uint8_t* data);

#endif /* _SDISP_SSD1327_H_ */
