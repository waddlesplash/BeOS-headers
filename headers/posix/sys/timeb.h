#ifndef _SYS_TIMEB_H
#define _SYS_TIMEB_H

#include <time.h>
#if __BEOS__
#include <BeBuild.h>
#else
#ifndef _IMPEXP_ROOT
#define	_IMPEXP_ROOT
#endif
#endif

struct timeb {
    time_t		time;		/* Seconds since the epoch	*/
    unsigned short	millitm;	/* Field not used		*/
    short		timezone;
    short		dstflag;	/* Field not used		*/
};

#ifdef __cplusplus
extern "C" {
#endif

_IMPEXP_ROOT int ftime(struct timeb *tp);

#ifdef __cplusplus
}
#endif	

#endif /* _SYS_TIMEB_H */
