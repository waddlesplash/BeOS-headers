/* ++++++++++
	KernelOS.h

	Copyright (C) 1991-3 Be Inc.  All Rights Reserved.
	Interface file for kernel functions.

	Modification History (reverse chron):
	16 aug 93	elr		new today.
+++++ */

#ifndef _OS_H
#define _OS_H

#ifndef _BE_DEFS_H
#include "BeDefs.h"
#endif

/*---------------------------------------------------------------------------*/
/*
 * Area data structures
 */

typedef	void	*as_token;

/*
 * the flags for area protection/object attribute/object size
 */

#define WRITE		pageWmask	/* writeable area */
#define USER		pageUmask	/* user area */

#define	LOCK		0x80000000	/* locked object */
#define	TEXT		0x40000000	/* object containing text */
#define	CONTIG		0x20000000	/* contiguously mapped object */

#define	NOSZ		0		/* no size specified */

/*
 * constant to specify the location of areas
 */

#define NOSPEC		0		/* VM freely chooses */
#define	SPEC		1		/* the user specifies the location */
#define	BASESPEC	2		/* the user specifies the base */
#define	TRANS		3		/* virtual = physical (for PHYSOBJ) */

/*---------------------------------------------------------------------------*/
/*
 * Interfaces for area management calls
 */
#ifdef __CPLUSPLUS__
extern "C" {
#endif

extern int	area_create(char *type, as_token asr, char **addr,
			int sel, uint size, uint attr, bool hasowner, ...);

extern int	area_clone(as_token sasr, char *saddr, as_token dasr,
			char **daddr, int sel, uint prot);
extern int	area_delete(char *addr, as_token asr);
extern int	area_resize(char *addr, uint newsize, as_token asr);
extern char	*area_which(char *addr, as_token asr);
extern as_token	get_asr();

/*---------------------------------------------------------------------------*/
/*
 * Buffered message ports
 */

extern int	pcreate(int count);
extern int	psend(int port, int msg, char *buf);
extern int	preceive(int port, char *buf);
extern int	pcount(int port);
extern int 	pdelete(int port);

/*---------------------------------------------------------------------------*/
/*
 * Semaphore calls
 */

typedef int	sem_id;

sem_id		create_sem(long count, char *name);
int		delete_sem(sem_id sem);

int		acquire_sem(sem_id sem);
int		release_sem(sem_id sem);
int		release_sem_count(sem_id sem, long count);
int		get_sem_count(sem_id sem, long *count);
int		get_sem_name(sem_id sem, char *name, int string_len);

/*---------------------------------------------------------------------------*/
/*
 * Thread related calls
 */

/* process state constants */

#define	PRCURR	1				/* process IS running */
#define	PRFREE	2				/* process slot is free */
#define PRREADY	3				/* process is on ready queue */
#define PRRECV	4				/* waiting on a message */
#define PRSLEEP	5				/* sleeping */
#define PRSUSP	6				/* suspended */
#define PRWAIT	7				/* waitin on a semaphore */

#define PNMLEN 15

struct as_rec;

struct pinfo {
	unsigned char	pstate;			/* process state */
	int		pprio;			/* priority */
	int		psem;			/* semaphore, if waiting */
	struct as_rec	*pasr;			/* aspace of this task */
	char		pname[PNMLEN+1];	/* name */
	long		curvol;			/* current volume id */
	long		curdir;			/* current directory id */
	unsigned long	ticks;			/* elapsed clock ticks */
};
	
extern int	spawn(PFV addr, char *name, uint stacksz, int prio, 
			int argc, char **argv);
extern int	kill(int pid);
extern int	get_pid();
extern int	get_proc_status(int pid, struct pinfo *p);
extern int	findpid(char *name);

/*---------------------------------------------------------------------------*/
/*
 * Miscellaneous calls
 */

extern int	sleept(uint milliseconds);

#ifdef __CPLUSPLUS__
}
#endif

#endif		/* ifdef oskernelh */
