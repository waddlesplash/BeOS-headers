//#ifndef _SYS_RESOURCE_H
//#define _SYS_RESOURCE_H
#ifndef _RLIMIT_H
#define _RLIMIT_H
/* limit ourselves to rlimit */

//#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * parts ripped of Linux (seems they come from somewhere else even =)
 * /usr/src/linux-2.2.19/include/linux/resource.h
 * /usr/src/linux-2.2.19/include/asm/resource.h
 */

/*
 * Resource control/accounting header file for linux
 */

/*
 * Definition of struct rusage taken from BSD 4.3 Reno
 *
 * We don't support all of these yet, but we might as well have them....
 * Otherwise, each time we add new items, programs which depend on this
 * structure will lose.  This reduces the chances of that happening.
 */

#if 0

#define RUSAGE_SELF     0
#define RUSAGE_CHILDREN (-1)
#define RUSAGE_BOTH     (-2)            /* sys_wait4() uses this */

struct  rusage {
        struct timeval ru_utime;        /* user time used */
        struct timeval ru_stime;        /* system time used */
        long    ru_maxrss;              /* maximum resident set size */
        long    ru_ixrss;               /* integral shared memory size */
        long    ru_idrss;               /* integral unshared data size */
        long    ru_isrss;               /* integral unshared stack size */
        long    ru_minflt;              /* page reclaims */
        long    ru_majflt;              /* page faults */
        long    ru_nswap;               /* swaps */
        long    ru_inblock;             /* block input operations */
        long    ru_oublock;             /* block output operations */
        long    ru_msgsnd;              /* messages sent */
        long    ru_msgrcv;              /* messages received */
        long    ru_nsignals;            /* signals received */
        long    ru_nvcsw;               /* voluntary context switches */
        long    ru_nivcsw;              /* involuntary " */
};


//extern int getrusage(int who, struct rusage *r);

#endif


#define RLIM_INFINITY   ((long)(~0UL>>1))

struct rlimit {
        long    rlim_cur;
        long    rlim_max;
};

#define PRIO_MIN        (-20)
#define PRIO_MAX        20

#define PRIO_PROCESS    0
#define PRIO_PGRP       1
#define PRIO_USER       2


/*
 * Resource limits
 */

#define RLIMIT_CPU      0               /* CPU time in ms */
#define RLIMIT_FSIZE    1               /* Maximum filesize */
#define RLIMIT_DATA     2               /* max data size */
#define RLIMIT_STACK    3               /* max stack size */
#define RLIMIT_CORE     4               /* max core file size */
#define RLIMIT_RSS      5               /* max resident set size */
#define RLIMIT_NPROC    6               /* max number of processes */
#define RLIMIT_NOFILE   7               /* max number of open files */
#define RLIMIT_MEMLOCK  8               /* max locked-in-memory address space */
#define RLIMIT_AS       9               /* address space limit */

#define RLIM_NLIMITS    10



extern int getrlimit(int resource, struct rlimit *rlp);

extern int setrlimit(int resource, const struct rlimit *rlp);

#ifdef __cplusplus
}
#endif

#endif
