/*
 * Copyright 1997, Be, Inc.
 * All Rights Reserved
 */
#ifndef _BYTEORDER_H
#define _BYTEORDER_H

#include <ansi_parms.h>
#include <SupportDefs.h>

#if __cplusplus
extern "C" {
#endif /* __cplusplus */

double _swap_double(double arg);
float _swap_float(float arg);
uint64 _swap_int64(uint64 uarg);
uint32 _swap_int32(uint32 uarg);

#if __MWERKS__ 

static inline uint16 _swap_int16(uint16 x)
{
	return ((x << 8) | (x >> 8));
}

#else /* __MWERKS__ */
/*
 * inline not supported
 */
#define _swap_int16(x) ((uint16)((((x) << 8) | (uint8)((x) >> 8))))

#endif /* __MWERKS__ */

#if __LITTLE_ENDIAN

#define B_HOST_IS_LENDIAN 1
#define B_HOST_IS_BENDIAN 0

/*
 * host to little-endian 
 */
#define B_HOST_TO_LENDIAN_DOUBLE(arg)	(double)(arg)
#define B_HOST_TO_LENDIAN_FLOAT(arg)	(float)(arg)
#define B_HOST_TO_LENDIAN_INT64(arg)	(uint64)(arg)
#define B_HOST_TO_LENDIAN_INT32(arg)	(uint32)(arg)
#define B_HOST_TO_LENDIAN_INT16(arg)	(uint16)(arg)

/*
 * host to big-endian 
 */
#define B_HOST_TO_BENDIAN_DOUBLE(arg)	_swap_double(arg)
#define B_HOST_TO_BENDIAN_FLOAT(arg)	_swap_float(arg)
#define B_HOST_TO_BENDIAN_INT64(arg)	_swap_int64(arg)
#define B_HOST_TO_BENDIAN_INT32(arg)	_swap_int32(arg)
#define B_HOST_TO_BENDIAN_INT16(arg)	_swap_int16(arg)

/*
 * little-endian to host
 */
#define B_LENDIAN_TO_HOST_DOUBLE(arg)	(double)(arg)
#define B_LENDIAN_TO_HOST_FLOAT(arg)	(float)(arg)
#define B_LENDIAN_TO_HOST_INT64(arg)	(uint64)(arg)
#define B_LENDIAN_TO_HOST_INT32(arg)	(uint32)(arg)
#define B_LENDIAN_TO_HOST_INT16(arg)	(uint16)(arg)

/*
 * big-endian to host
 */
#define B_BENDIAN_TO_HOST_DOUBLE(arg)	_swap_double(arg)
#define B_BENDIAN_TO_HOST_FLOAT(arg)	_swap_float(arg)
#define B_BENDIAN_TO_HOST_INT64(arg)	_swap_int64(arg)
#define B_BENDIAN_TO_HOST_INT32(arg)	_swap_int32(arg)
#define B_BENDIAN_TO_HOST_INT16(arg)	_swap_int16(arg)

#else /* __LITTLE_ENDIAN */

#define B_HOST_IS_LENDIAN 0
#define B_HOST_IS_BENDIAN 1

/*
 * host to little-endian 
*/
#define B_HOST_TO_LENDIAN_DOUBLE(arg)	_swap_double(arg)
#define B_HOST_TO_LENDIAN_FLOAT(arg)	_swap_float(arg)
#define B_HOST_TO_LENDIAN_INT64(arg)	_swap_int64(arg)
#define B_HOST_TO_LENDIAN_INT32(arg)	_swap_int32(arg)
#define B_HOST_TO_LENDIAN_INT16(arg)	_swap_int16(arg)

/*
 * host to big-endian 
 */
#define B_HOST_TO_BENDIAN_DOUBLE(arg)	(double)(arg)
#define B_HOST_TO_BENDIAN_FLOAT(arg)	(float)(arg)
#define B_HOST_TO_BENDIAN_INT64(arg)	(uint64)(arg)
#define B_HOST_TO_BENDIAN_INT32(arg)	(uint32)(arg)
#define B_HOST_TO_BENDIAN_INT16(arg)	(uint16)(arg)

/*
 * little-endian to host
 */
#define B_LENDIAN_TO_HOST_DOUBLE(arg)	_swap_double(arg)
#define B_LENDIAN_TO_HOST_FLOAT(arg)	_swap_float(arg)
#define B_LENDIAN_TO_HOST_INT64(arg)	_swap_int64(arg)
#define B_LENDIAN_TO_HOST_INT32(arg)	_swap_int32(arg)
#define B_LENDIAN_TO_HOST_INT16(arg)	_swap_int16(arg)

/*
 * big-endian to host
 */
#define B_BENDIAN_TO_HOST_DOUBLE(arg)	(double)(arg)
#define B_BENDIAN_TO_HOST_FLOAT(arg)	(float)(arg)
#define B_BENDIAN_TO_HOST_INT64(arg)	(uint64)(arg)
#define B_BENDIAN_TO_HOST_INT32(arg)	(uint32)(arg)
#define B_BENDIAN_TO_HOST_INT16(arg)	(uint16)(arg)

#endif /* __LITTLE_ENDIAN */

/*
 * Standard Berkeley macros
 */
#define htonl(x) B_HOST_TO_BENDIAN_INT32(x)
#define ntohl(x) B_BENDIAN_TO_HOST_INT32(x)
#define htons(x) B_HOST_TO_BENDIAN_INT16(x)
#define ntohs(x) B_BENDIAN_TO_HOST_INT16(x)

#if __cplusplus
}
#endif /* __cplusplus */

#endif /* _BYTEORDER_H */
