/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	stddef.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cstddef__
#define __cstddef__

#include <ansi_parms.h>

__namespace(__stdc_space(stddef))

typedef long	ptrdiff_t;

#include <size_t.h>
#include <wchar_t.h>
#include <null.h>

__end_namespace(stdc_space(stddef))

__import_stdc_into_std_space(stddef)

#define offsetof(type, member)	((size_t) &(((type *) 0)->member))

#endif /* __cstddef__ */
/*     Change record
*/
