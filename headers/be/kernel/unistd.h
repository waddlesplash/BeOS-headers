/*****************************************************************************

     Copyright (c) 1995-96 by Be Incorporated.  All Rights Reserved.

*****************************************************************************/

/*
 * This file contains Be's declarations of Posix compliant calls.
 */


#ifndef _UNISTD_H
#define _UNISTD_H

#ifndef _UNIX_H
#include <Unix.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

extern int		fstat(int fd, struct stat *buf);					/* E */
extern int		stat(const char *path, struct stat *buf);			/* I */

extern int			creat(const char *path, mode_t mode);			/* */
extern int			open(const char *pathname, int oflags, ...);	/* P */
extern int			close(int fd);									/* */
extern int			read(int fd, void *buf, size_t count);			/* P */
extern int			write(int fd, const void *buf, size_t count);	/* P */
extern off_t		lseek(int fd, long offset, int whence);			/* P */
extern int			ioctl(int fd, int op, ...);
extern int			fcntl(int fd, int op, ...);

extern int			dup(int fd);									/* */
extern int			dup2(int fd1, int fd2);							/* */

extern int			unlink(const char *name);						/* */

extern int			mkdir(const char *path);						/* */
extern int			rmdir(const char *path);						/* */
extern int			chdir(const char *path);						/* */

extern int			system(	const char *cmd);						/* */
extern int			execve(	const char *path,						/* P I */
							char *argv[],
							char **envp);

extern pid_t		fork(void);										/* E */
extern int			kill(pid_t pid, int sig);
extern int			pipe(int fildes[2]);							/* I */
extern struct passwd *getpwnam(const char *name);					/* P I */
extern struct passwd *getpwuid(uid_t uid);							/* I */
extern char			*getcwd(char *buffer, size_t size);				/* P I */
extern char			*getlogin(void);								/* I */
extern unsigned int sleep(unsigned int seconds);					/* */

extern DIR			*opendir(const char *dirname);					/* */
extern struct dirent *readdir(DIR *dirp);							/* */
extern int			closedir(DIR *dirp);							/* */
extern void			rewinddir(DIR *dirp);							/* */

extern pid_t		getpid(void);
extern uid_t		getuid(void);									/* I */
extern uid_t		geteuid(void);									/* I */
extern gid_t		getgid(void);									/* I */
extern gid_t		getegid(void);									/* I */
extern int			setuid(uid_t uid);								/* I */
extern int			setgid(gid_t gid);								/* I */

extern int			isatty(int fd);									/* I */
extern int			utime(const char *path, const char *ubuf);		/* I */
extern int			chmod(const char *path, mode_t mode);			/* I */
extern int			chown(	const char *path,						/* I */
							uid_t owner,
							gid_t group);

extern int			system(const char *string);
extern void			*getgrgid(gid_t gid);							/* I */
extern void			*getgrnam(const char *name);					/* I */
extern int			link(const char *name, const char *new_name);	/* I */
extern int			times();										/* P I */
extern int			access(const char *path, int amode);			/* I */
extern clock_t		clock(void);									/* I */

extern int 			hide_resources(void);
extern char *		make_rsrc_name(const char *path);

extern int 			load_posix(const char *name, const char **argv,
							const char **envp);

#ifdef __cplusplus
}
#endif

#endif

