/******************************************************************************
/
/	File:			BeBuild.h
/
/	Description:	Import/export macros
/
/	Copyright 1993-98, Be Incorporated
/
*******************************************************************************/

#ifndef _BE_BUILD_H
#define _BE_BUILD_H

#include <ProductFeatures.h>

#define B_BEOS_VERSION_4		0x0400
#define B_BEOS_VERSION_4_5		0x0450
#define B_BEOS_VERSION_5		0x0500
#define B_BEOS_VERSION_5_0_4	0x0504
#define B_BEOS_VERSION_5_1_0	0x0510
#define B_ZETA_VERSION_0_2_0	0x0520
#define B_ZETA_VERSION_0_3_0	0x0530
#define B_ZETA_VERSION_0_4_0	0x0540
#define B_ZETA_VERSION_0_4_1	0x0541
#define B_ZETA_VERSION_1_0_0	0x0600
#define B_ZETA_VERSION_1_1_0	0x0610
#define B_ZETA_VERSION_1_2_0	0x0620


#define B_BEOS_VERSION_MAUI 	B_BEOS_VERSION_5
#define B_BEOS_VERSION_DANO		B_BEOS_VERSION_5_1_0
#define B_ZETA_VERSION_BETA		B_ZETA_VERSION_0_2_0
#define B_ZETA_VERSION_GESTALT	B_ZETA_VERSION_0_3_0
#define B_ZETA_VERSION_BELLA	B_ZETA_VERSION_0_4_0
#define B_ZETA_VERSION_NEO		B_ZETA_VERSION_0_4_1
#define B_ZETA_VERSION_VENTURE	B_ZETA_VERSION_1_0_0
#define B_ZETA_VERSION_HANK		B_ZETA_VERSION_1_1_0
#define B_ZETA_VERSION_DEAN		B_ZETA_VERSION_1_2_0

#define B_ZETA_VERSION			B_ZETA_VERSION_DEAN
#define B_BEOS_VERSION			B_ZETA_VERSION

/* Originally, it wasn't possible to unset _R5_COMPATIBLE_, so make the
 * default behaviour the same.
*/
#ifndef _R5_COMPATIBLE_
#define _R5_COMPATIBLE_ 1
#endif

#if _R5_COMPATIBLE_
#if defined(__powerc) || defined(powerc)
	#define _PR2_COMPATIBLE_ 1
	#define _PR3_COMPATIBLE_ 1
	#define _R4_COMPATIBLE_ 1
	#define _R4_5_COMPATIBLE_ 1
	#define _R5_COMPATIBLE_ 1
	#define _R5_0_4_COMPATIBLE_ 1
#else
	#define _PR2_COMPATIBLE_ 0
	#define _PR3_COMPATIBLE_ 0
	#define _R4_COMPATIBLE_ 1
	#define _R4_5_COMPATIBLE_ 1
	#define _R5_COMPATIBLE_ 1
	#define _R5_0_4_COMPATIBLE_ 1
#endif
#else
	#define _PR2_COMPATIBLE_ 0
	#define _PR3_COMPATIBLE_ 0
	#define _R4_COMPATIBLE_ 0
	#define _R4_5_COMPATIBLE_ 0
	#define _R5_COMPATIBLE_ 0
	#define _R5_0_4_COMPATIBLE_ 0
#endif

#if __GNUC__
#define _UNUSED(x) x
#define _PACKED	__attribute__((packed))
#endif

#define	_EXPORT
#define	_IMPORT

#endif
