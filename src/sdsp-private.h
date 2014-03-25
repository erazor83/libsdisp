/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 */


#ifndef _SDSP_PRIVATE_H_
#define _SDSP_PRIVATE_H_

#ifndef _MSC_VER
# include <stdint.h>
# include <sys/time.h>
#else
# include "stdint.h"
# include <time.h>
typedef int ssize_t;
#endif
#include <sys/types.h>

#include "sdsp.h"

SDSP_BEGIN_DECLS


typedef enum {
	_SDSP_BACKEND_TYPE_RTU=0
} sdsp_bakend_type_t;

/* This structure reduces the number of params in functions and so
* optimizes the speed of execution (~ 37%). */
typedef struct _sft {
	int sdsp_id;
	int instruction;
	int t_id;
} sft_t;

typedef struct _sdsp_display {
	uint8_t backend_type;
	uint8_t header_length;
	uint8_t checksum_length;
	uint8_t max_adu_length;
		
	int8_t (*build_request_basis) (sdsp_t *ctx, uint8_t id, sdsp_request_t instruction,
																 uint8_t parameter_count, uint8_t *req);
	//int8_t (*build_response_basis) (sft_t *sft, uint8_t *rsp);
	//int8_t (*prepare_response_tid) (const uint8_t *req, int *req_length);
		
	int8_t (*send_msg_pre) (uint8_t *req, uint8_t req_length);
	ssize_t (*send) (sdsp_t *ctx, const uint8_t *req, uint8_t req_length);
	ssize_t (*recv) (sdsp_t *ctx, uint8_t *rsp, uint8_t rsp_length);
	int8_t (*check_integrity) (sdsp_t *ctx, uint8_t *msg,
														const uint8_t msg_length);
	int8_t (*connect) (sdsp_t *ctx);
	void (*close) (sdsp_t *ctx);
	int8_t (*flush) (sdsp_t *ctx);
	int8_t (*select) (sdsp_t *ctx, fd_set *rfds, struct timeval *tv, uint8_t msg_length);
} sdsp_backend_t;

struct _sdsp {
	/* Socket or file descriptor */
	int s;
	bool debug;
	bool error_recovery;
	struct timeval response_timeout;
	struct timeval byte_timeout;
	const sdsp_backend_t *backend;
	void *backend_data;
	uint8_t *response_data;
};

void _sdsp_init_common(sdsp_t *ctx);
void _error_print(sdsp_t *ctx, const char *context);
void sdsp_free(sdsp_t *ctx);

#ifndef HAVE_STRLCPY
size_t strlcpy(char *dest, const char *src, size_t dest_size);
#endif

SDSP_END_DECLS

#endif  /* _SDSP_PRIVATE_H_ */
