/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDSP_CRIUS_H_
#define _SDSP_CRIUS_H_

#include <sdsp.h>

#define SDSP_CRIUS_FEATURES					SDSP_FEATURE_MONOCHROME | SDSP_FEATURE_GRAPHIC | \
																		SDSP_FEATURE_HAS_DETECT | SDSP_FEATURE_HAS_TEST | \
																		SDSP_FEATURE_HAS_INVERT
#define SDSP_CRIUS_WIDTH						0
#define SDSP_CRIUS_HEIGHT						0
#define SDSP_CRIUS_I2C_ADDRESS			0

#define SDSP_CRIUS_NAME							"Crius-oLED"

SDSP_BEGIN_DECLS
typedef struct _sdsp_crius {
} sdsp_crius_t;


sdsp_t* sdsp_new_crius(void);
int sdsp_crius_init(sdsp_t* ctx);

int sdsp_crius_detect(sdsp_t* ctx);
int sdsp_crius_invert(sdsp_t* ctx);
int sdsp_crius_test(sdsp_t* ctx);


SDSP_END_DECLS

#endif /* _SDSP_CRIUS_H_ */
