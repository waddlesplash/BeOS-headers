/*
 *	errno.h
 *
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef __errno__
#define __errno__

#include <Errors.h>

#define ENOERR          0
#define EOK 			ENOERR  /* some code assumes EOK exists */

extern

#if __cplusplus
"C"
#endif /* __cplusplus */

int *_errnop(void);

extern int *_errnop(void);


#define errno (*(_errnop()))


#endif /* __errno__ */
