/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 * Dynamixel library - a fork from libmodbus (http://libmodbus.org)
 */

#ifndef _SDSP_VERSION_H_
#define _SDSP_VERSION_H_

/* The full version, like 1.2.3 */
#define SDSP_VERSION						@LIBSDSP_VERSION@

/* The full version, in string form (suited for string concatenation)
 */
#define LIBSDSP_VERSION_STRING	"@LIBSDSP_VERSION@"

/* Numerically encoded version, like 0x010203 */
#define LIBSDSP_VERSION_HEX			((LIBSDSP_MAJOR_VERSION << 24)	|	\
																(LIBSDSP_MINOR_VERSION << 16)		|	\
																(LIBSDSP_MICRO_VERSION << 8))

/* Evaluates to True if the version is greater than @major, @minor and @micro
 */
#define LIBSDSP_VERSION_CHECK(major,minor,micro)	\
		(LIBSDSP_VERSION_MAJOR > (major) ||						\
		(LIBSDSP_VERSION_MAJOR == (major) &&					\
			LIBSDSP_VERSION_MINOR > (minor)) ||					\
		(LIBSDSP_VERSION_MAJOR == (major) &&					\
			LIBSDSP_VERSION_MINOR == (minor) &&					\
			LIBSDSP_VERSION_MICRO >= (micro)))

#endif /* _SDSP_VERSION_H_ */
