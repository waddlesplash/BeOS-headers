/*  fcntl.h */

#ifndef _FCNTL_H
#define _FCNTL_H

/* flags for open */

#define O_RDONLY       0  /* read only */
#define O_WRONLY       1  /* write only */
#define O_RDWR         2  /* read and write */

#define O_CREAT		0x0200	/* create and open file */
#define O_TRUNC		0x0400	/* open with truncation */
#define O_EXCL    0x0400  /* exclusive open */
#define O_APPEND	0x0800	/* to end of file */
#define O_TEXT		0x4000	/* CR-LF translation	*/
#define O_BINARY	0x8000	/* no translation	*/

#define S_IREAD 0x0100  /* owner may read */
#define S_IWRITE 0x0080	/* owner may write */

#endif
