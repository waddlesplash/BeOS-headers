#ifndef _SYS_TIMES_H_
#define _SYS_TIMES_H_

#ifndef __time__
#define __time__
typedef unsigned long clock_t;
#endif

struct tms {
    clock_t tms_utime;      /* user time */
    clock_t tms_stime;      /* system time */
    clock_t tms_cutime;     /* user time, children */
    clock_t tms_cstime;     /* system time, children */
};

#ifdef __cplusplus
extern "C" {
#endif

clock_t times(struct tms *buffer); 

#ifdef __cplusplus
}
#endif
#endif /* _SYS_TIMES_H_ */
