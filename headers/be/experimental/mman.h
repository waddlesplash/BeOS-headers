#ifndef MMAN_H_
#define MMAN_H_

#include <sys/types.h>

#ifndef off64_t
	typedef off_t off64_t;
#endif

/* defines */

/* mman.h defines */
#define PROT_READ        0x1       /* page can be read */
#define PROT_WRITE       0x2       /* page can be written */
#define PROT_EXEC        0x4       /* page can be executed */
#define PROT_NONE        0x0       /* page can not be accessed */

#define MAP_SHARED       1         /* Share changes */
#define MAP_PRIVATE      2         /* Changes are private */
#define MAP_TYPE         0xf       /* Mask for type of mapping */
#define MAP_FIXED        0x10      /* Interpret addr exactly */

/* mmap() wrappers */
/* mmu_man */

extern void *mmap(void *, size_t, int, int, int, off_t);
extern void *mmap64(void *, size_t, int, int, int, off64_t);
extern int msync(void *, size_t, int);
extern int munmap(void *, size_t);

#endif /* MMAN_H_ */
