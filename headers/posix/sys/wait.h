#ifndef _SYS_WAIT_H_
#define _SYS_WAIT_H_


#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *stat_loc, int options);

#ifdef __cplusplus
}
#endif

#define WNOHANG    0x1
#define WUNTRACED  0x2


#define WIFEXITED(val)    (val == 0)
#define WEXITSTATUS(val)  ((val) & 0xff)
#define WIFSIGNALED(val)  (val)
#define WTERMSIG(val)     (val)
#define WIFSTOPPED(val)   (val)
#define WSTOPSIG(val)     (val)
#define WIFCORED(val)     (val)

						 
#endif /* _SYS_WAIT_H_ */
