#ifndef _UTIME_H_
#define _UTIME_H_

struct utimbuf
{
	time_t actime;
	time_t modtime;
};


#ifdef __cplusplus
extern "C" {
#endif

int utime(const char *path, const struct utimbuf *times);

#ifdef __cplusplus
}
#endif

#endif /* _UTIME_H_ */
