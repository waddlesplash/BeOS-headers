/* ++++++++++

	fcntl.h
	Copyright (C) 1993-96 Be Inc.  All Rights Reserved.

+++++ */

#ifndef _FCNTL_H
#define _FCNTL_H

#define	FD_CLOEXEC		1

/* -----
	cmd ids for fcntl
----- */

#define	F_DUPFD			1
#define	F_GETFD			2
#define	F_SETFD			3
#define	F_GETFL			4
#define	F_SETFL			5
/* THIS IS NOT POSIX - REMOVE THIS */
#define	F_DUP2FD		6

/* flags for open */

#define O_RDONLY       0  /* read only */
#define O_WRONLY       1  /* write only */
#define O_RDWR         2  /* read and write */

#define O_CREAT		0x0200	/* create and open file */
#define O_TRUNC		0x0400	/* open with truncation */
#define O_APPEND	0x0800	/* to end of file */
#define	O_EXCL		0x0100	/* exclusive creat */
#define	O_NONBLOCK	0x0080	/* non blocking io */
#define O_TEXT		0x4000	/* CR-LF translation	*/
#define O_BINARY	0x8000	/* no translation	*/

#define O_RESOURCE	0x1000	/* allows opening/creating of resource files */
#define O_EXCLOPEN	0x2000  /* exclusive open */

#define S_IREAD 0x0100  /* owner may read */
#define S_IWRITE 0x0080	/* owner may write */

#define	OPEN_MAX	32		/* Maximum number of open user file descriptors */

#endif
