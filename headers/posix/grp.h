#ifndef _GRP_H_
#define _GRP_H_

#include <sys/types.h>

struct group {
       char *gr_name;
       char *gr_passwd;
       int gr_gid;
       char **gr_mem;
};


#ifdef __cplusplus
extern "C" {
#endif

extern struct group *getgrgid(gid_t gid);
extern struct group *getgrnam(const char *name);

extern struct group *getgrent(void);
extern void          setgrent(void);
extern void          endgrent(void);

#ifdef __cplusplus
}
#endif

#endif /* _GRP_H_ */
