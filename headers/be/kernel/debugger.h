/* ++++++++++
	File:			debugger.h
	Description:	kernel interface for a debugger.

	Copyright (c) 1995-96 by Be Incorporated.  All Rights Reserved.
+++++ */

#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _IMAGE_H
#include <image.h>
#endif

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* -----
	kernel calls
----- */

extern int		install_default_debugger (port_id to_debugger_port);
extern port_id	install_team_debugger (team_id team, port_id to_debugger_port);
extern int		remove_team_debugger (team_id team);
extern int		debug_thread (thread_id thread);


/* -----
	per-thread debugging flags (returned by the get_thread_debug_info
	request to the debugging nub)
----- */

#define	B_STOP_CHILD_THREADS	0x01

/* -----
	ids for why a thread is invoking the debugger
----- */

typedef enum {
	B_THREAD_NOT_RUNNING,
	B_DEBUGGER_CALL,
	B_BREAKPOINT_HIT,
	B_NMI,
	B_MACHINE_CHECK_EXCEPTION,
	B_DATA_ACCESS_EXCEPTION,
	B_INSTRUCTION_ACCESS_EXCEPTION,
	B_ALIGNMENT_EXCEPTION,
	B_PROGRAM_EXCEPTION
} db_why_stopped;


/* -----
	cpu state.  It is arranged to be useable by the kernel, hence all the
	C volatile regs are grouped at the beginning.  The non-volatile ones
	are only saved when neccessary.
----- */

typedef struct {
	long	pc;
	long	msr;
	long	lr;
	long	ctr;
	long	xer;
	long	cr;
	long	filler1;
	long	fpscr;
	long	r0;
	long	r1;			/* stack ptr */
	long	r2;
	long	r3;
	long	r4;
	long	r5;
	long	r6;
	long	r7;
	long	r8;
	long	r9;
	long	r10;
	long	r11;
	long	r12;
	long	r13;
	double	f0;
	double	f1;
	double	f2;
	double	f3;
	double	f4;
	double	f5;
	double	f6;
	double	f7;
	double	f8;
	double	f9;
	double	f10;
	double	f11;
	double	f12;
	double	f13;	/* C non-volatile regs start here */
	double	f14;
	double	f15;
	double	f16;
	double	f17;
	double	f18;
	double	f19;
	double	f20;
	double	f21;
	double	f22;
	double	f23;
	double	f24;
	double	f25;
	double	f26;
	double	f27;
	double	f28;
	double	f29;
	double	f30;
	double	f31;
	long	r14;
	long	r15;
	long	r16;
	long	r17;
	long	r18;
	long	r19;
	long	r20;
	long	r21;
	long	r22;
	long	r23;
	long	r24;
	long	r25;
	long	r26;
	long	r27;
	long	r28;
	long	r29;
	long	r30;
	long	r31;
} cpu_state;
	
/* -----
	messages from debug server to the nub running in a target
	thread's address space.
----- */

enum debug_nub_message {
	B_READ_MEMORY = 0,			/* read some memory */
	B_WRITE_MEMORY,				/* write some memory */
	B_RUN_THREAD,				/* run thread full speed */
	B_STEP_THREAD,				/* step thread while pc in range */
	B_STEP_OVER_THREAD,			/* step thread while pc in range, skip calls */
	B_STEP_OUT_THREAD,			/* step thread till exit current proc */
	B_SET_BREAKPOINT,			/* set a breakpoint */
	B_CLEAR_BREAKPOINT,			/* set a breakpoint */
	B_STOP_NEW_THREADS,			/* en/disable stopping of child threads */
	B_GET_THREAD_DEBUG_INFO,	/* get debugging info */
	B_ACKNOWLEGE_IMAGE_CREATED	/* acknowlege image created */
};

/* -----
	structures passed to the nub
----- */

typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	char		*addr;					/* address to read */
	int			count;					/* # bytes */
} nub_read_memory_msg;
	
typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	char		*addr;					/* address to write */
	int			count;					/* # bytes */
} nub_write_memory_msg;

typedef struct {
	thread_id	thread;					/* thread id */
	long		align_to_double;		/* for alignment */
	cpu_state	cpu;					/* cpu state */
} nub_run_thread_msg;

typedef struct {
	thread_id	thread;					/* thread id */
	char		*low_pc;				/* low end of pc range */
	char		*high_pc;				/* highend of pc range */
	long		align_to_double;		/* for alignment */
	cpu_state	cpu;					/* cpu state */
} nub_step_thread_msg;

typedef struct {
	thread_id	thread;					/* thread id */
	char		*low_pc;				/* low end of pc range */
	char		*high_pc;				/* highend of pc range */
	long		align_to_double;		/* for alignment */
	cpu_state	cpu;					/* cpu state */
} nub_step_over_thread_msg;

typedef struct {
	thread_id	thread;					/* thread id */
	long		align_to_double;		/* for alignment */
	cpu_state	cpu;					/* cpu state */
} nub_step_out_thread_msg;

typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	char		*addr;					/* breakpoint address */
} nub_set_breakpoint_msg;

typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	char		*addr;					/* breakpoint address */
} nub_clear_breakpoint_msg;

typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	thread_id	thread;
	bool		enabled;				/* en/disable stop of child threads */
} nub_stop_new_threads_msg;

typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	thread_id	thread;
} nub_get_thread_debug_info_msg;

typedef struct {
	long	debug_flags;				/* returned thread debugging flags */
} nub_get_thread_debug_info_reply;

typedef struct {
	long	token;
} nub_acknowlege_image_created_msg;


/* -----
	union of all stuctures passed to the nub
----- */

typedef union {
	nub_read_memory_msg					nub_read_memory;
	nub_write_memory_msg				nub_write_memory;
	nub_run_thread_msg					nub_run_thread;
	nub_step_thread_msg					nub_step_thread;
	nub_step_over_thread_msg			nub_step_over_thread;
	nub_step_out_thread_msg				nub_step_out_thread;
	nub_set_breakpoint_msg				nub_set_breakpoint;
	nub_clear_breakpoint_msg			nub_clear_breakpoint;
	nub_stop_new_threads_msg			nub_stop_new_threads;
	nub_get_thread_debug_info_msg		nub_get_thread_debug_info;
	nub_acknowlege_image_created_msg	nub_acknowlege_image_created;
} to_nub_msg;


/* -----
	messages passed to the external debugger
----- */

enum debugger_message {
	B_THREAD_STOPPED = 0,	/* thread stopped, here is its state */
	B_TEAM_CREATED,			/* team was created */
	B_TEAM_DELETED,			/* team was deleted */
	B_PEF_IMAGE_CREATED,	/* pef image was created */
	B_PEF_IMAGE_DELETED,	/* pef image was deleted */
	B_THREAD_CREATED,		/* thread was created */
	B_THREAD_DELETED		/* thread was deleted */
};

/* ----------
	structures passed to the external debugger
----- */

typedef struct {
	thread_id		thread;		/* thread id */
	team_id			team;		/* team id */
	db_why_stopped	why;		/* reason for contacting debugger */
	port_id			nub_port;	/* port to nub for this team */
	cpu_state		cpu;		/* cpu state */
} db_thread_stopped_msg;
	
typedef struct {
	team_id		team;			/* id of new team  */
} db_team_created_msg;

typedef struct {
	team_id		team;			/* id of deleted team  */
} db_team_deleted_msg;

typedef struct {
	long		reply_token;	/* token to acknowledge receipt (REQUIRED!) */
	team_id		team;			/* team id */
	thread_id	thread;			/* id of thread that is loading the image */
	image_info	info;			/* info for the image */
} db_pef_image_created_msg;

typedef struct {
	team_id		team;
	image_info	info;			/* info for the image */
} db_pef_image_deleted_msg;

typedef struct {
	thread_id	thread;			/* thread id */
	team_id		team;			/* team id */
} db_thread_created_msg;

typedef struct {
	thread_id	thread;			/* thread id */
	team_id		team;			/* team id */
} db_thread_deleted_msg;


/* -----
	union of all structures passed to external debugger
----- */

typedef union {
	db_thread_stopped_msg		thread_stopped;
	db_team_created_msg			team_created;
	db_team_deleted_msg			team_deleted;
	db_pef_image_created_msg	pef_image_created;
	db_pef_image_deleted_msg	pef_image_deleted;
	db_thread_created_msg		thread_created;
	db_thread_deleted_msg		thread_deleted;
} to_debugger_msg;

#ifdef __cplusplus
}
#endif

#endif
