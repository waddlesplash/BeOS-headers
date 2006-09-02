#ifndef _INTTYPES_H_
#define _INTTYPES_H_

#include <be_setup.h>
#include <posix/stdint.h>

#ifndef __int8_t_defined    /* gnu */
# define __int8_t_defined    /* for compiling glibc */
#endif

typedef signed int 			intptr_t;
typedef unsigned int 		uintptr_t;

#if __GNUC__

#define __need_wchar_t /* gnu */
#include <stddef.h>

__extern_c_start

/* Like `strtol' but convert to `intmax_t'.  */
extern intmax_t strtoimax(const char *__nptr,
						  char **__endptr, int __base);

/* Like `strtoul' but convert to `uintmax_t'.  */
extern uintmax_t strtoumax(const char * __nptr,
						   char ** __endptr, int __base);

/* Like `wcstol' but convert to `intmax_t'.  */
extern intmax_t wcstoimax(const wchar_t * __nptr,
						  wchar_t **__endptr, int __base);

/* Like `wcstoul' but convert to `uintmax_t'.  */
extern uintmax_t wcstoumax(const wchar_t * __nptr,
						   wchar_t ** __endptr, int __base);

__extern_c_end

#endif /* __GNUC__ */


#endif /* _INTTYPES_H_ */
