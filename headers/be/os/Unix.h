/* ++++++++++
	unix.h	

	Copyright (C) 1993 Be Labs, Inc.  All Rights Reserved
	A simple header file intended to be included by anyone unfortunate
	enough to be making use of the "unix compatibility functions"
	available in libos.a.

	Modification History (most recent first):
	08 dec 93	elr		New Today.

+++++ */

#ifndef _UNIX_H
#define _UNIX_H


typedef	unsigned short		ino_t;		/* <inode> type */
typedef short			cnt_t;		/* ?<count> type */
typedef	long			time_t;		/* <time> type */
typedef unsigned short		mode_t;
typedef short			nlink_t;
typedef	short			dev_t;		/* <old device number> type */
typedef	long			off_t;		/* ?<offset> type */

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
	dev_t	st_dev;
	ino_t	st_ino;
	mode_t 	st_mode;
	nlink_t	st_nlink;
	uid_t 	st_uid;
	gid_t 	st_gid;
	dev_t	__pad1;
	dev_t	st_rdev;
	off_t	st_size;
	time_t	st_atime;
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
	int	vol;
	int	dir;
	int	pos;
	struct dirent	*dp;
} DIR;

extern DIR            		*opendir(char *);
extern struct dirent		*readdir(DIR *);
extern void           		closedir(DIR *);
extern long           		telldir(DIR *);
extern void    			seekdir(DIR *, long);
#define rewinddir( dirp ) 	seekdir( dirp, 0L )

#ifndef	DIRSIZ
#define	DIRSIZ	14
#endif
struct	direct
{
	unsigned short	d_ino;
	char		d_name[DIRSIZ];
};

struct group {
       char *gr_name;
       char *gr_passwd;
       int gr_gid;
       char **gr_mem;
};

/* major part of a device */
#define	major(x)	(int)((unsigned)((x)>>8)&0x7F)
#define	bmajor(x)	(int)((unsigned)((x)>>8)&0x7F)

/* minor part of a device */
#define	minor(x)	(int)((x)&0xFF)

/* make a device number */
#define	makedev(x,y)	(dev_t)(((x)<<8) | (y))

typedef long	clock_t;
struct tms {
	clock_t	tms_utime;		/* user time */
	clock_t	tms_stime;		/* system time */
	clock_t	tms_cutime;		/* user time, children */
	clock_t	tms_cstime;		/* system time, children */
};

#endif	/* _UNIX_H */
