
#ifndef _SYS_UTSNAME_H_
#define _SYS_UTSNAME_H_

#if __BEOS__
#include <BeBuild.h>
#else
#ifndef _IMPEXP_NET
#define	_IMPEXP_NET
#endif
#endif

struct utsname {
	char sysname[32];
	char nodename[32];
	char release[32];
	char version[32];
	char machine[32];
};

#ifdef __cplusplus
extern "C" {
#endif

_IMPEXP_NET int uname(struct utsname *name);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_UTSNAME_H_ */
