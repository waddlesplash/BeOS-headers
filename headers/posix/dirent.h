#ifndef _DIRENT_H_
#define _DIRENT_H_

#include <sys/types.h>

typedef struct dirent {
	dev_t			d_dev;
	dev_t			d_pdev;
	ino_t			d_ino;
	ino_t			d_pino;
	unsigned short	d_reclen;
	char			d_name[1];
} dirent_t;

typedef struct {
	int				fd;
	struct dirent	ent;
} DIR;

#ifndef DIRSIZ
#define DIRSIZ  64
#endif


#ifndef MAXNAMLEN
#ifdef  NAME_MAX
#define MAXNAMLEN NAME_MAX
#else
#define MAXNAMLEN 64
#endif
#endif

#ifdef	__cplusplus
extern "C" {
#endif

extern DIR			 *opendir(const char *dirname);
extern struct dirent *readdir(DIR *dirp);
extern int			  closedir(DIR *dirp);
extern void			  rewinddir(DIR *dirp);


#ifdef	__cplusplus
}
#endif

#endif /* _DIRENT_H_ */
