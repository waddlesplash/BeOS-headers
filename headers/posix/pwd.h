#ifndef _PWD_H_
#define _PWD_H_

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct passwd {
        char    *pw_name;
		char    *pw_passwd;
        uid_t   pw_uid;
        gid_t   pw_gid;
        char    *pw_dir;
        char    *pw_shell;
};

extern void           setpwent(void);
extern void           endpwent(void);
extern struct passwd *getpwent(void);
extern struct passwd *getpwnam(const char *name);
extern struct passwd *getpwuid(uid_t uid);

#ifdef __cplusplus
}
#endif
#endif /* _PWD_H_ */
