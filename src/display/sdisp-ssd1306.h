/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_SSD1306_H_
#define _SDISP_SSD1306_H_

#include <sdisp.h>

SDISP_BEGIN_DECLS
typedef struct _sdisp_ssd1306 {
} sdisp_ssd1306_t;


sdisp_t* sdisp_new_ssd1306(void);


SDISP_END_DECLS

#endif /* _SDISP_SSD1306_H_ */
