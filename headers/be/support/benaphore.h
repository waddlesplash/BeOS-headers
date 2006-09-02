/*
	Copyright (c) 2002, Thomas Kurschel


	Part of Open SCSI bus manager
		
	Benaphore definition
*/

#ifndef _BENAPHORE_H
#define _BENAPHORE_H

#include <KernelExport.h>

typedef struct {
	int32	ben;
	sem_id	sem;
} benaphore;

 
#define INIT_BEN(x, prefix)	( (x)->ben = -1, (x)->sem = create_sem(0, #prefix " benaphore"), (x)->sem )
#define	DELETE_BEN(x)		delete_sem((x)->sem);

#if __GNUC__ && _X86_ && !DEBUG

#ifdef NO_PIC

// don't use normal inline as this _does_ incur overhead;
// also, we have to include the xxx_sem call in the assembler code
// as this is the only way to use flags directly (else we had to create
// a temporary variable); this function call leads to the following:
// - it's not PIC safe, making it unusable in user mode!
// - function calls clobber eax, ecx, edx and memory
#define ACQUIRE_BEN( x ) \
__asm__ __volatile__ ( \
	"lock incl %0;" \
	"jng 1f;" \
	"push %1;" \
	"call acquire_sem;" \
	"add  $4,%%esp;" \
	"1:;" \
	: "=m" ((x)->ben) \
	: "m" ((x)->sem), "0" ((x)->ben) \
	: "ax", "cx", "dx" \
);

#define RELEASE_BEN( x ) \
__asm__ __volatile__ ( \
	"lock decl %0;" \
	"jl 1f;" \
	"push %1;" \
	"call release_sem;" \
	"add  $4,%%esp;" \
	"1:;" \
	: "=m" ((x)->ben) \
	: "m" ((x)->sem), "0" ((x)->ben) \
	: "ax", "cx", "dx" \
);

#else	// NO_PIC

// larger, but PIC-safe version

#define ACQUIRE_BEN( x ) \
{ \
	char not_idle; \
\
	__asm__ __volatile__ ( \
		"lock incl %0;" \
		"setg %1" \
		: "=m" ((x)->ben), "=qm" (not_idle) \
		: "0" ((x)->ben) \
	); \
\
	if( not_idle ) \
		acquire_sem( (x)->sem ); \
}

#define RELEASE_BEN( x ) \
{ \
	char not_idle; \
\
	__asm__ __volatile__ ( \
		"lock decl %0;" \
		"setge %1" \
		: "=m" ((x)->ben), "=qm" (not_idle) \
		: "0" ((x)->ben) \
	); \
\
	if( not_idle ) \
		release_sem( (x)->sem ); \
}

#endif

#else	// __GNUC__ && _X86_

#define ACQUIRE_BEN(x) \
	if((atomic_add(&((x)->ben), 1)) >= 0) \
		acquire_sem((x)->sem);
		
#define RELEASE_BEN(x) \
	if((atomic_add(&((x)->ben), -1)) > 0) \
		release_sem((x)->sem);

#endif


#endif
