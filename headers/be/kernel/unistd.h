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
#include <sys/types.h>

extern void         _exit(int status);
extern int			access(const char *path, int amode);			/* I */

/* XXX alarm */

extern int			chdir(const char *path);						/* */
extern int			chown(const char *path, uid_t owner, gid_t group);
extern int			close(int fd);									/* */
extern char        *ctermid(char *s);
extern char        *cuserid(char *s);
extern int			dup(int fd);									/* */
extern int			dup2(int fd1, int fd2);							/* */
extern int			execve(const char *path, char *argv[], char **envp);
extern int          execl(const char *path, const char *arg, ...);
extern int          execv(const char *path, char **argv);
extern int          execlp(const char *file, const char *arg, ...);
#if 0   /* metrowerks doesn't grok a regular arg after var args */
extern int          execle(const char *path, const char *arg , ..., char **envp);
#endif
extern int          exect(const char *path, char **argv);
extern int          execvp(const char *file, char **argv);


extern pid_t		fork(void);										/* E */
extern long         fpathconf(int fd, int name);
extern char		   *getcwd(char *buffer, size_t size);				/* P I */
extern gid_t		getegid(void);									/* I */
extern uid_t		geteuid(void);									/* I */
extern gid_t		getgid(void);									/* I */
extern int          getgroups(size_t size, gid_t list[]);
extern char		   *getlogin(void);									/* I */
extern pid_t        getpgrp(void);
extern pid_t		getpid(void);
extern pid_t		getppid(void);
extern uid_t		getuid(void);									/* I */
extern int			isatty(int fd);									/* I */
extern int			link(const char *name, const char *new_name);	/* I */
extern off_t		lseek(int fd, long offset, int whence);			/* P */
extern long			pathconf(const char *path, int name);
extern int 			pause(void);
extern int			pipe(int fildes[2]);							/* I */
extern int			read(int fd, void *buf, size_t count);			/* P */
extern int			rmdir(const char *path);						/* */
extern int			setgid(gid_t gid);								/* I */

extern int          setpgid(pid_t pid, pid_t pgid);
extern pid_t		setsid(void);


extern int			setuid(uid_t uid);								/* I */
extern unsigned int sleep(unsigned int seconds);					/* */
extern long 		sysconf(int name);
extern pid_t        tcgetpgrp(int fd);
extern int          tcsetpgrp(int fd, pid_t pgrpid);
extern char        *ttyname(int fd);

extern int			unlink(const char *name);						/* */
extern int			write(int fd, const void *buf, size_t count);	/* P */

extern int			ioctl(int fd, int op, ...);

extern int			system(const char *string);
extern clock_t		clock(void);									/* I */

extern int 			load_posix(const char *name, const char **argv,
							   const char **envp);

extern long			mount_vol(const char *device);
extern long			unmount_vol(long volid);
extern long			format_device(const char *device, const char *volume_name,
								  char low_level);

extern long			get_file_type_creator(const char *path, ulong *type,
								ulong *creator);
extern long			set_file_type_creator(const char *path, ulong type,
								ulong creator);

#ifdef __cplusplus
}
#endif

#define F_OK   0
#define R_OK   1
#define W_OK   2
#define X_OK   3

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
#define _POSIX_VDISABLE            13
#define _POSIX_VERSION             14
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

#endif

