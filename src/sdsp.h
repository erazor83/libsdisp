/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 */
#ifndef _SDSP_H_
#define _SDSP_H_

/* Add this for macros that defined unix flavor */
#if (defined(__unix__) || defined(unix)) && !defined(USG)
#include <sys/param.h>
#endif

#include <sdsp_config.h>

#ifdef  __cplusplus
# define SDSP_BEGIN_DECLS  extern "C" {
# define SDSP_END_DECLS    }
#else
# define SDSP_BEGIN_DECLS
# define SDSP_END_DECLS
#endif


SDSP_BEGIN_DECLS

#define SDSP_DEBUG 1
#define SDSP_NO_DEBUG 0

/* Native libsdsp error codes */
#define E_SDSP_BADCHECKSUM 	1

/*
typedef enum {
	DISPLAY_TYPE_SSD1306=11306,

} display_type_t;
*/

extern const unsigned int libsdsp_version_major;
extern const unsigned int libsdsp_version_minor;
extern const unsigned int libsdsp_version_micro;

typedef struct _sdsp sdsp_t;


/* sdsp core funcions */
int8_t sdsp_init(sdsp_t *ctx);
void sdsp_test(sdsp_t *);
void sdsp_close(sdsp_t *);
void sdsp_free(sdsp_t *ctx);


SDSP_END_DECLS

#endif  /* _SDSP_H_ */
