/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDISP_H_
#define _SDISP_H_

/* Add this for macros that defined unix flavor */
#if (defined(__unix__) || defined(unix)) && !defined(USG)
#include <sys/param.h>
#endif

#ifndef _SWIG
#include <stdint.h>
#endif

#ifdef  __cplusplus
# define SDISP_BEGIN_DECLS  extern "C" {
# define SDISP_END_DECLS    }
#else
# define SDISP_BEGIN_DECLS
# define SDISP_END_DECLS
#endif

#ifndef _SWIG
#include <stdbool.h>
#endif

SDISP_BEGIN_DECLS

#define SDISP_FEATURE_HAS_DETECT    (1<<0)
#define SDISP_FEATURE_HAS_TEST      (1<<1)
#define SDISP_FEATURE_HAS_INVERT    (1<<8)
#define SDISP_FEATURE_HAS_FONT      (1<<3)
#define SDISP_FEATURE_GRAPHIC       (1<<10)
#define SDISP_FEATURE_BOOLCHROME    (1<<11)
#define SDISP_FEATURE_MONOCHROME    (1<<12)
#define SDISP_FEATURE_GREYSCALE     (1<<13)
#define SDISP_FEATURE_COLOR         (1<<14)

#define SDISP_DEBUG 1
#define SDISP_NO_DEBUG 0

/* Native libsdisp error codes */
#define E_SDISP_BADCHECKSUM 	1

/*
typedef enum {
	DISPLAY_TYPE_SSD1306=11306,

} display_type_t;
*/

extern const unsigned int libsdisp_version_major;
extern const unsigned int libsdisp_version_minor;
extern const unsigned int libsdisp_version_micro;

typedef struct _sdisp sdisp_t;

#include <sdisp_config.h>

/* sdisp core funcions */
int8_t sdisp_display__init(sdisp_t*);
int8_t sdisp_display__test(sdisp_t*);
int8_t sdisp_display__clear(sdisp_t*);
int8_t sdisp_display__mov_to(sdisp_t*,uint8_t,uint8_t);
int8_t sdisp_display__detect(sdisp_t *ctx);

void sdisp_close(sdisp_t*);
void sdisp_free(sdisp_t*);

SDISP_END_DECLS

#endif  /* _SDISP_H_ */
