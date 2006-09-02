#ifndef _ITIMER_H
#define _ITIMER_H
#include <sys/time.h>

struct itimerval
{
  struct timeval it_value;
  struct timeval it_interval;
};

#define ITIMER_REAL 1
#define ITIMER_PROF 2
#define ITIMER_VIRTUAL 3

int setitimer(int which, const struct itimerval *value, struct itimerval *ovalue);


#define SIGVTALRM       26
#define SIGPROF         27

#endif
