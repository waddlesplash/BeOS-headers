/* ++++++++++
	unix.h	

	Copyright (C) 1993-96 Be Labs, Inc.  All Rights Reserved
	A simple header file intended to be included by anyone unfortunate
	enough to be making use of the "unix compatibility functions"
	available in libos.a.

+++++ */

#include <time.h>

#ifndef _UNIX_H
#define _UNIX_H

/* returns 1 is system is in resource hiding mode. 0 otherwise */

#ifdef __cplusplus
extern "C" {
#endif

int			hide_resources();

/* returns a NEWLY alloc'ed ptr to the string "<path>.res" */
char		*make_rsrc_name(const char *path);

/* returns a NEWLY alloc'ed ptr to the string "<path>" minus ".res" extension */
extern		char *make_base_name(const char *path);

int			is_rsrc_name(const char *path);

#ifdef __cplusplus
}
#endif

typedef	unsigned short		ino_t;		/* <inode> type */
typedef short				cnt_t;		/* ?<count> type */
typedef unsigned short		mode_t;
typedef short				nlink_t;
typedef	short				dev_t;		/* <old device number> type */
typedef	long				off_t;		/* ?<offset> type */

/* Hack for PowerPC, until Metaware fixes .cnf file to be like hobbit. If
   UID_T already defined, skip this (likely incompatible) definition.  This
   may cause some wierdness with uid's, but who cares? */
#ifndef _UID_T
typedef unsigned short		uid_t;
#define _UID_T
#endif
typedef unsigned short		gid_t;

typedef short			pid_t;		/* used for process ids */

/*
 * stat structure
 */

struct	stat {
	dev_t	st_dev;				/* Not currently supported */
	ino_t	st_ino;				/* Not currently supported */
	mode_t 	st_mode;
	nlink_t	st_nlink;			/* Not currently supported */
	uid_t 	st_uid;				/* Not currently supported */
	gid_t 	st_gid;				/* Not currently supported */
	dev_t	__pad1;
	dev_t	st_rdev;			/* Not currently supported */
	off_t	st_size;
	time_t	st_atime;			/* same as last modification time */
	time_t	st_mtime;
	time_t	st_ctime;
};


#define		S_IFMT	0170000	/* type of file */
#define		S_IFREG	0100000	/* regular */
#define		S_IFBLK	0060000	/* block special */
#define		S_IFDIR	0040000	/* directory */
#define		S_IFCHR	0020000	/* character special */
#define		S_IFIFO	0010000	/* fifo */

#define		S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
#define		S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
#define		S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#define		S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#define		S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)

#define	S_ISUID	04000		/* set user id on execution */
#define	S_ISGID	02000		/* set group id on execution */

#define	S_ISVTX	01000		/* save swapped text even after use */

#define	S_IRWXU	00700		/* read, write, execute: owner */
#define	S_IRUSR	00400		/* read permission: owner */
#define	S_IWUSR	00200		/* write permission: owner */
#define	S_IXUSR	00100		/* execute permission: owner */
#define	S_IRWXG	00070		/* read, write, execute: group */
#define	S_IRGRP	00040		/* read permission: group */
#define	S_IWGRP	00020		/* write permission: group */
#define	S_IXGRP	00010		/* execute permission: group */
#define	S_IRWXO	00007		/* read, write, execute: other */
#define	S_IROTH	00004		/* read permission: other */
#define	S_IWOTH	00002		/* write permission: other */
#define	S_IXOTH	00001		/* execute permission: other */


struct dirent				/* data from readdir() */
	{
	ino_t		d_ino;		/* inode number of entry */
	short		d_pad;		/* because ino_t is ushort */
	off_t		d_off;		/* offset of disk directory entry */
	unsigned short	d_reclen;	/* length of this record */
	char		d_name[1];	/* name of file */
	};

typedef struct {
	char			*path;
	int				pos;
	int				num;
	struct dirent	*dp;
} DIR;

#ifndef	DIRSIZ
#define	DIRSIZ	64
#endif

struct group {
       char *gr_name;
       char *gr_passwd;
       int gr_gid;
       char **gr_mem;
};

struct passwd {
		char	*pw_name;
		uid_t	pw_uid;
		gid_t	pw_gid;
		char	*pw_dir;
		char	*pw_shell;
};

/* major part of a device */
#define	major(x)	(int)((unsigned)((x)>>8)&0x7F)
#define	bmajor(x)	(int)((unsigned)((x)>>8)&0x7F)

/* minor part of a device */
#define	minor(x)	(int)((x)&0xFF)

/* make a device number */
#define	makedev(x,y)	(dev_t)(((x)<<8) | (y))

struct tms {
	clock_t	tms_utime;		/* user time */
	clock_t	tms_stime;		/* system time */
	clock_t	tms_cutime;		/* user time, children */
	clock_t	tms_cstime;		/* system time, children */
};

#endif	/* _UNIX_H */
