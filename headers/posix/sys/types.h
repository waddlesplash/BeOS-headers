#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#ifndef __time__
#include <time.h>
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef unsigned int        ino_t;      /* <inode> type */
typedef int                 cnt_t;      /* <count> type */
typedef unsigned int        mode_t;     /* file modes */
typedef int                 nlink_t;
typedef int                 dev_t;      /* <old device number> type */
typedef long                off_t;      /* <offset> type */
typedef long		        pid_t;      /* process ids */

typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int umode_t;
typedef int          daddr_t;

/* bsd */
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;

/* sysv */
typedef unsigned char unchar;
#ifndef _SUPPORT_DEFS_H 
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
#endif /* _SUPPORT_DEFS_H */

typedef char *caddr_t;

#ifndef __size_t__
#include <size_t.h>
#endif

typedef size_t ssize_t;

#endif
