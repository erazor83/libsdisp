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

#include <sdisp_config.h>

#ifdef  __cplusplus
# define SDISP_BEGIN_DECLS  extern "C" {
# define SDISP_END_DECLS    }
#else
# define SDISP_BEGIN_DECLS
# define SDISP_END_DECLS
#endif

#include <stdbool.h>

SDISP_BEGIN_DECLS

#define SDISP_FEATURE_HAS_DETECT    0x0001
#define SDISP_FEATURE_HAS_TEST      0x0002
#define SDISP_FEATURE_GRAPHIC       0x0010
#define SDISP_FEATURE_MONOCHROME    0x0020
#define SDISP_FEATURE_HAS_INVERT    0x0030

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


/* sdisp core funcions */
int8_t sdisp_display_init(sdisp_t*);
int8_t sdisp_display_test(sdisp_t*);

void sdisp_close(sdisp_t*);
void sdisp_free(sdisp_t*);

SDISP_END_DECLS

#endif  /* _SDISP_H_ */
