#ifndef _SYS_TYPES_H

#define _SYS_TYPES_H

#include <time.h>
#include <null.h>

#if INTEL_LONG_LONG_FIX
typedef long           ino_t;      /* <inode> type */
#else
typedef long long           ino_t;      /* <inode> type */
#endif
typedef int                 cnt_t;      /* <count> type */
typedef unsigned int        mode_t;     /* file modes */
typedef int                 nlink_t;
typedef long                dev_t;      /* <old device number> type */
#if INTEL_LONG_LONG_FIX
typedef long           off_t;      /* <offset> type */
#else
typedef long long           off_t;      /* <offset> type */
#endif
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

#include <size_t.h>

#endif
