/*
 *	ansi_parms.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __ansi_parms__
#define __ansi_parms__

#ifdef __cplusplus

#define __extern_c			extern "C" {
#define __end_extern_c	}

#else

#define __extern_c
#define __end_extern_c

#endif /* __cplusplus */

#define __undef_os	0
#define __mac_os		1
#define __be_os			2

#define __dest_os __be_os
#endif /* ndef __ansi_parms__ */
