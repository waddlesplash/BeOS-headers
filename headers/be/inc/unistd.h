#ifndef	__sys_unistd_h
#define	__sys_unistd_h
#if __CPLUSPLUS__
extern "C" {
#endif

#include <sys/types.h>

#define	STDIN_FILENO	0
#define	STDOUT_FILENO	1
#define	STDERR_FILENO	2

#ifndef NULL
    #define	NULL	0
#endif

/*
 * lseek & access args
 *
 */
#ifndef SEEK_SET
    #define	SEEK_SET	0    /* Set file pointer to "offset" */
    #define	SEEK_CUR	1    /* Set file pointer to current plus "offset" */
    #define	SEEK_END	2    /* Set file pointer to EOF plus "offset" */
#endif

#define	F_OK		0	/* does file exist */
#define	X_OK		1	/* is it executable by caller */
#define	W_OK		2	/* is it writable by caller */
#define	R_OK		4	/* is it readable by caller */

extern void	_exit( int status );
extern int	access( const char *path, int amode );
extern int	chdir( const char *path );
extern int	chmod( const char *path, mode_t mode );
extern int	close( int fildes );
#if _SOL
extern char	*getcwd( char *buf, size_t size );
#else
#if _ATT4
extern char	*getcwd( char *buf, size_t size );
#else
extern char	*getcwd( char *buf, int size );
#endif
#endif

extern int	isatty( int fildes );
extern off_t	lseek( int fildes, off_t offset, int whence );
extern int	open( const char *path,  int mode, ...);
extern int	read( int fildes, char *buf, unsigned int nbyte );
extern int	rmdir( const char *path );
extern int	unlink( const char *path );
extern int	write( int fildes, const char *buf, unsigned int nbyte );

#ifndef __PENPOINT__

    #ifndef	_POSIX_SOURCE
	/*
	 * SVID lockf() requests
	 */
	#define	F_ULOCK		0	/* Unlock a previously locked region */
	#define	F_LOCK		1	/* Lock a region for exclusive use */
	#define	F_TLOCK		2	/* Test and lock a region for exclusive use */
	#define	F_TEST		3	/* Test a region for other processes locks */

	/* Path names: */
	#define	GF_PATH			"/etc/group"
	#define	PF_PATH			"/etc/passwd"

    #endif	/* !_POSIX_SOURCE */

    extern unsigned	alarm( unsigned secs );
    extern int		chhown( const char *path, uid_t owner, gid_t group );
    extern char	*	ctermid( char *s );
    extern char	*	cuserid( char *s );
    extern int		dup( int fildes );
    extern int		dup2( int fildes, int fildes2 );
    extern int		execl( const char *path, const char *, ... );
    extern int		execle( const char *path, const char *, ... );
    extern int		execlp( const char *file, const char *, ... );
    extern int		execv( const char *path, char *const *argv );
    extern int		execve( const char *path, char *const *argv, char *const *envp );
    extern int		execvp( const char *file, char *const *argv );
    extern pid_t	fork( void );
    extern long		fpathconf( int fd, int name );
    extern gid_t	getegid( void );
    extern uid_t	geteuid( void );
    extern gid_t	getgid( void );
    extern int		getgroups( int gidsetsize, gid_t grouplist[] );
    extern char	*	getlogin( void );
    extern pid_t	getpgrp( void );
    extern pid_t	getpid( void );
    extern pid_t	getppid( void );
    extern uid_t	getuid( void );
    extern int		link( const char *path1, const char *path2 );
    extern long		pathconf( const char *path, int name );
    extern int		pause( void );
    extern int		pipe( int fildes[2] );
    extern int		setgid( gid_t gid );
    extern int		setpgid( pid_t pid, pid_t pgid );
    extern pid_t	setsid( void );
    extern int		setuid( uid_t uid );
    extern unsigned	sleep( unsigned int seconds );
    extern long		sysconf( int name );
    extern pid_t	tcgetpgrp( int fildes );
    extern int		tcsetpgrp( int fildes, pid_t pgrp_id );
    extern char	*	ttyname( int fildes );

#endif	/* ! __PENPOINT__ */


#if __CPLUSPLUS__
}
#endif


#endif	/* !__sys_unistd_h */
