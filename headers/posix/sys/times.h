#ifndef _SYS_TIMES_H_
#define _SYS_TIMES_H_

#if __BEOS__
#include <BeBuild.h>
#else
#ifndef _IMPEXP_ROOT
#define	_IMPEXP_ROOT
#endif
#endif

#ifndef _CLOCK_T_DEFINED_

typedef long	clock_t;
#define _CLOCK_T_DEFINED_

#endif /* _CLOCK_T_DEFINED_ */

struct tms {
    clock_t tms_utime;      /* user time */
    clock_t tms_stime;      /* system time */
    clock_t tms_cutime;     /* user time, children */
    clock_t tms_cstime;     /* system time, children */
};

#ifdef __cplusplus
extern "C" {
#endif

_IMPEXP_ROOT clock_t times(struct tms *buffer); 

#ifdef __cplusplus
}
#endif
#endif /* _SYS_TIMES_H_ */
