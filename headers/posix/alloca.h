#ifndef _ALLOCA_H_
#define _ALLOCA_H_

#ifdef __cplusplus
extern "C" {
#endif

#if __INTEL__

#include <sys/types.h>

#define alloca _alloca			/* the Intel compiler prepends an
								 * underscore before symbols */
#if defined(__cplusplus)
extern "C" void * _alloca(size_t);
#else
extern void * _alloca(size_t);
#endif

#else	
#define alloca __alloca
#endif	


#ifdef __cplusplus
}
#endif
#endif /* _ALLOCA_H_ */
