#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#include <sys/types.h>

/*
 * stat structure
 */

struct  stat {
    dev_t   st_dev;             /* Not currently supported */
    ino_t   st_ino;             /* Not currently supported */
    mode_t  st_mode;
    nlink_t st_nlink;           /* Not currently supported */
    uid_t   st_uid;             /* Not currently supported */
    gid_t   st_gid;             /* Not currently supported */
    dev_t   __pad1;
    dev_t   st_rdev;            /* Not currently supported */
    off_t   st_size;
    ulong   st_blksize;
    time_t  st_atime;           /* same as last modification time */
    time_t  st_mtime;
    time_t  st_ctime;
};


#define     S_IFMT  0170000 /* type of file */
#define     S_IFREG 0100000 /* regular */
#define     S_IFBLK 0060000 /* block special */
#define     S_IFDIR 0040000 /* directory */
#define     S_IFCHR 0020000 /* character special */
#define     S_IFIFO 0010000 /* fifo */

#define     S_ISREG(m)  (((m) & S_IFMT) == S_IFREG)
#define     S_ISBLK(m)  (((m) & S_IFMT) == S_IFBLK)
#define     S_ISDIR(m)  (((m) & S_IFMT) == S_IFDIR)
#define     S_ISCHR(m)  (((m) & S_IFMT) == S_IFCHR)
#define     S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)

#define S_ISUID 04000       /* set user id on execution */
#define S_ISGID 02000       /* set group id on execution */

#define S_ISVTX 01000       /* save swapped text even after use */

#define S_IRWXU 00700       /* read, write, execute: owner */
#define S_IRUSR 00400       /* read permission: owner */
#define S_IWUSR 00200       /* write permission: owner */
#define S_IXUSR 00100       /* execute permission: owner */
#define S_IRWXG 00070       /* read, write, execute: group */
#define S_IRGRP 00040       /* read permission: group */
#define S_IWGRP 00020       /* write permission: group */
#define S_IXGRP 00010       /* execute permission: group */
#define S_IRWXO 00007       /* read, write, execute: other */
#define S_IROTH 00004       /* read permission: other */
#define S_IWOTH 00002       /* write permission: other */
#define S_IXOTH 00001       /* execute permission: other */


#ifdef  __cplusplus
extern "C" {
#endif

extern int fstat(int fd, struct stat *buf);
extern int stat(const char *path, struct stat *buf);
extern int chmod(const char *path, mode_t mode);
extern int mkdir(const char *path, mode_t mode);
extern mode_t umask(mode_t cmask);          /* XXX */
extern int mkfifo(char *path, mode_t mode); /* XXX */

#ifdef  __cplusplus
}
#endif

#endif /* _SYS_STAT_H_ */

