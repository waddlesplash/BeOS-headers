#ifndef _SYS_TIME_H
#define _SYS_TIME_H

struct timeval {
	long tv_sec;
	long tv_usec;
};

/*
 * If you depend on timezones, you are in trouble because we don't
 * support them!  Everything is currently in local time and there is
 * no concept of GMT.
 */
struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};

#ifdef __cplusplus
extern "C" {
#endif

int gettimeofday(struct timeval *tv, struct timezone *tz);

#define timerclear(tvp)	((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp)                        \
                  ((tvp)->tv_sec cmp (uvp)->tv_sec ||  \
				   (tvp)->tv_sec == (uvp)->tv_sec &&   \
				   (tvp)->tv_usec cmp (uvp)->tv_usec)


#ifdef __cplusplus
}
#endif	

#endif /* _SYS_TIME_H */
