/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 * Dynamixel library - a fork from libmodbus (http://libmodbus.org)
 */

#ifndef _SDISP_VERSION_H_
#define _SDISP_VERSION_H_

/* The full version, like 1.2.3 */
#define SDISP_VERSION						@LIBSDISP_VERSION@

/* The full version, in string form (suited for string concatenation)
 */
#define LIBSDISP_VERSION_STRING	"@LIBSDISP_VERSION@"

/* Numerically encoded version, like 0x010203 */
#define LIBSDISP_VERSION_HEX			((LIBSDISP_MAJOR_VERSION << 24)	|	\
																(LIBSDISP_MINOR_VERSION << 16)		|	\
																(LIBSDISP_MICRO_VERSION << 8))

/* Evaluates to True if the version is greater than @major, @minor and @micro
 */
#define LIBSDISP_VERSION_CHECK(major,minor,micro)	\
		(LIBSDISP_VERSION_MAJOR > (major) ||						\
		(LIBSDISP_VERSION_MAJOR == (major) &&					\
			LIBSDISP_VERSION_MINOR > (minor)) ||					\
		(LIBSDISP_VERSION_MAJOR == (major) &&					\
			LIBSDISP_VERSION_MINOR == (minor) &&					\
			LIBSDISP_VERSION_MICRO >= (micro)))

#endif /* _SDISP_VERSION_H_ */
