/*****************************************************************************

     Copyright (c) 1995-96 by Be Incorporated.  All Rights Reserved.

*****************************************************************************/

/*
 * This file contains Be's declarations of Posix compliant calls.
 */


#ifndef _UNISTD_H
#define _UNISTD_H

#include <ansi_parms.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <null.h>
#include <sys/types.h>

extern _IMPEXP_ROOT void        _exit(int status);
extern _IMPEXP_ROOT int			access(const char *path, int amode);

extern _IMPEXP_ROOT unsigned int	alarm(unsigned int sec);

extern _IMPEXP_ROOT int			chdir(const char *path);
extern _IMPEXP_ROOT int			chown(const char *path, uid_t owner, gid_t group);
extern _IMPEXP_ROOT int			close(int fd);
extern _IMPEXP_ROOT char *		crypt(const char *key, const char *salt);
extern _IMPEXP_ROOT char        *ctermid(char *s);
extern _IMPEXP_ROOT char        *cuserid(char *s);
extern _IMPEXP_ROOT int			dup(int fd);
extern _IMPEXP_ROOT int			dup2(int fd1, int fd2);
extern _IMPEXP_ROOT int			execve(const char *path, const char *argv[], const char *envp[]);
extern _IMPEXP_ROOT int         execl(const char *path, const char *arg, ...);
extern _IMPEXP_ROOT int         execv(const char *path, char *const *argv);
extern _IMPEXP_ROOT int         execlp(const char *file, const char *arg, ...);
extern _IMPEXP_ROOT int         execle(const char *path, const char *arg , ... /*, char **envp */);
extern _IMPEXP_ROOT int         exect(const char *path, char *const *argv);
extern _IMPEXP_ROOT int         execvp(const char *file, char *const *argv);


extern _IMPEXP_ROOT int			fchown(int fd, uid_t owner, gid_t group);
extern _IMPEXP_ROOT pid_t		fork(void);
extern _IMPEXP_ROOT long        fpathconf(int fd, int name);
extern _IMPEXP_ROOT int         ftruncate(int fd, off_t newsize);
extern _IMPEXP_ROOT char		*getcwd(char *buffer, size_t size);
extern _IMPEXP_ROOT int         getdtablesize(void);
extern _IMPEXP_ROOT gid_t		getegid(void);
extern _IMPEXP_ROOT uid_t		geteuid(void);
extern _IMPEXP_ROOT gid_t		getgid(void);
extern _IMPEXP_ROOT int         getgroups(int size, gid_t list[]);
extern _IMPEXP_ROOT char		*getlogin(void);
extern _IMPEXP_ROOT pid_t       getpgrp(void);
extern _IMPEXP_ROOT pid_t		getpid(void);
extern _IMPEXP_ROOT pid_t		getppid(void);
extern _IMPEXP_ROOT uid_t		getuid(void);
extern _IMPEXP_ROOT int			isatty(int fd);
extern _IMPEXP_ROOT int			link(const char *name, const char *new_name);
extern _IMPEXP_ROOT int			mknod(const char *name, mode_t mode, dev_t dev);
extern _IMPEXP_ROOT off_t		lseek(int fd, off_t offset, int whence);
extern _IMPEXP_ROOT long		pathconf(const char *path, int name);
extern _IMPEXP_ROOT int 		pause(void);
extern _IMPEXP_ROOT int			pipe(int fildes[2]);
extern _IMPEXP_ROOT ssize_t		read(int fd, void *buf, size_t count);
extern _IMPEXP_ROOT ssize_t     read_pos(int fd, off_t pos, void *buf, size_t count);
extern _IMPEXP_ROOT ssize_t     readlink(const char *path, char *buf, size_t bufsize);
extern _IMPEXP_ROOT int			rmdir(const char *path);
extern _IMPEXP_ROOT int			setgid(gid_t gid);

extern _IMPEXP_ROOT int         setpgid(pid_t pid, pid_t pgid);
extern _IMPEXP_ROOT pid_t		setsid(void);


extern _IMPEXP_ROOT int			setuid(uid_t uid);
extern _IMPEXP_ROOT unsigned int sleep(unsigned int seconds);
extern _IMPEXP_ROOT long 		sysconf(int name);
extern _IMPEXP_ROOT int         symlink(const char *from, const char *to);
extern _IMPEXP_ROOT pid_t       tcgetpgrp(int fd);
extern _IMPEXP_ROOT int         tcsetpgrp(int fd, pid_t pgrpid);
extern _IMPEXP_ROOT int         truncate(const char *path, off_t newsize);
extern _IMPEXP_ROOT char        *ttyname(int fd);

extern _IMPEXP_ROOT int			unlink(const char *name);
extern _IMPEXP_ROOT ssize_t		write(int fd, const void *buf, size_t count);
extern _IMPEXP_ROOT ssize_t     write_pos(int fd, off_t pos, const void *buf,size_t count);

extern _IMPEXP_ROOT int			ioctl(int fd, int op, ...);

extern _IMPEXP_ROOT char       *sbrk(int incr);
extern _IMPEXP_ROOT int			sync(void);
extern _IMPEXP_ROOT int			fsync(int fd);

extern _IMPEXP_ROOT int			mount(const char *filesystem, const char *where,
									const char *device, ulong flags,
									void *parms, int len);
extern _IMPEXP_ROOT int			unmount(const char *path);

extern _IMPEXP_ROOT int			system(const char *string);
extern _IMPEXP_ROOT clock_t		clock(void);

extern _IMPEXP_ROOT char *optarg;
extern _IMPEXP_ROOT int optind, opterr, optopt;
extern _IMPEXP_ROOT int getopt (int argc, char *const *argv, const char *shortopts);

#ifdef __cplusplus
}
#endif


#define R_OK   4
#define W_OK   2
#define X_OK   1
#define F_OK   0

#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2

#define _PC_CHOWN_RESTRICTED        1
#define _PC_MAX_CANON               2
#define _PC_MAX_INPUT               3
#define _PC_NAME_MAX                4
#define _PC_NO_TRUNC                5
#define _PC_PATH_MAX                6
#define _PC_PIPE_BUF                7
#define _PC_VDISABLE                8
#define _POSIX_CHOWN_RESTRICTED     9
#define _POSIX_JOB_CONTROL         10
#define _POSIX_NO_TRUNC            11
#define _POSIX_SAVED_IDS           12
#define _POSIX_VDISABLE            (cc_t)-2
#define _POSIX_VERSION             (199009L)
#define _SC_ARG_MAX                15
#define _SC_CHILD_MAX              16
#define _SC_CLK_TCK                17
#define _SC_JOB_CONTROL            18
#define _SC_NGROUPS_MAX            19
#define _SC_OPEN_MAX               20
#define _SC_SAVED_IDS              21
#define _SC_STREAM_MAX             22
#define _SC_TZNAME_MAX             23
#define _SC_VERSION                24
#define _PC_LINK_MAX               25

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif


#endif

