#ifndef _DIRENT_H_
#define _DIRENT_H_

#include <sys/types.h>

struct dirent           /* data from readdir() */
{
    ino_t   d_ino;      /* inode number of entry */
    short   d_pad;      /* because ino_t is ushort */
    off_t   d_off;      /* offset of disk directory entry */
    ushort  d_reclen;   /* length of this record */
    char    d_name[1];  /* name of file */
};

typedef struct {
    char            *path;
    int             pos;
    int             num;
    struct dirent   *dp;
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
