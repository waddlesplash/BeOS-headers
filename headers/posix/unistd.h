/*****************************************************************************

     Copyright (c) 1995-96 by Be Incorporated.  All Rights Reserved.

*****************************************************************************/

/*
 * This file contains Be's declarations of Posix compliant calls.
 */


#ifndef _UNISTD_H
#define _UNISTD_H

#ifdef __cplusplus
extern "C" {
#endif
#include <null.h>
#include <sys/types.h>

extern void         _exit(int status);
extern int			access(const char *path, int amode);

extern unsigned int	alarm(unsigned int sec);

extern int			chdir(const char *path);
extern int			chown(const char *path, uid_t owner, gid_t group);
extern int			close(int fd);
extern char        *ctermid(char *s);
extern char        *cuserid(char *s);
extern int			dup(int fd);
extern int			dup2(int fd1, int fd2);
extern int			execve(const char *path, char *const argv[], char *const *envp);
extern int          execl(const char *path, const char *arg, ...);
extern int          execv(const char *path, char *const *argv);
extern int          execlp(const char *file, const char *arg, ...);
extern int          execle(const char *path, const char *arg , ... /*, char **envp */);
extern int          exect(const char *path, char *const *argv);
extern int          execvp(const char *file, char *const *argv);


extern pid_t		fork(void);
extern long         fpathconf(int fd, int name);
extern int          ftruncate(int fd, off_t newsize);
extern char		   *getcwd(char *buffer, size_t size);
extern int          getdtablesize(void);
extern gid_t		getegid(void);
extern uid_t		geteuid(void);
extern gid_t		getgid(void);
extern int          getgroups(int size, gid_t list[]);
extern char		   *getlogin(void);
extern pid_t        getpgrp(void);
extern pid_t		getpid(void);
extern pid_t		getppid(void);
extern uid_t		getuid(void);
extern int			isatty(int fd);
extern int			link(const char *name, const char *new_name);
extern off_t		lseek(int fd, off_t offset, int whence);
extern long			pathconf(const char *path, int name);
extern int 			pause(void);
extern int			pipe(int fildes[2]);
extern ssize_t		read(int fd, void *buf, size_t count);
extern ssize_t      read_pos(int fd, off_t pos, void *buf, size_t count);
extern ssize_t      readlink(const char *path, char *buf, size_t bufsize);
extern int			rmdir(const char *path);
extern int			setgid(gid_t gid);

extern int          setpgid(pid_t pid, pid_t pgid);
extern pid_t		setsid(void);


extern int			setuid(uid_t uid);
extern unsigned int sleep(unsigned int seconds);
extern long 		sysconf(int name);
extern int          symlink(const char *from, const char *to);
extern pid_t        tcgetpgrp(int fd);
extern int          tcsetpgrp(int fd, pid_t pgrpid);
extern int          truncate(const char *path, off_t newsize);
extern char        *ttyname(int fd);

extern int			unlink(const char *name);
extern ssize_t		write(int fd, const void *buf, size_t count);
extern ssize_t      write_pos(int fd, off_t pos, const void *buf,size_t count);

extern int			ioctl(int fd, int op, ...);

extern int			sync(void);
extern int			fsync(int fd);

extern int			system(const char *string);
extern clock_t		clock(void);


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
#define _POSIX_VDISABLE            -2
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

