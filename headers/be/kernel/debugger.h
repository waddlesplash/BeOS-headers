/* ++++++++++
	File:			debugger.h
	Description:	kernel interface for a debugger.

	Copyright (c) 1995-97 by Be Incorporated.  All Rights Reserved.
+++++ */


#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#include <OS.h>
#include <image.h>
#include <SupportDefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -----
	kernel calls
----- */

extern status_t	install_default_debugger (port_id to_debugger_port);
extern port_id	install_team_debugger (team_id team, port_id to_debugger_port);
extern status_t	remove_team_debugger (team_id team);
extern status_t	debug_thread (thread_id thread);


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
	int32	filler1;
	int32	fpscr;
	int32	pc;
	int32	msr;
	int32	lr;
	int32	ctr;
	int32	xer;
	int32	cr;
	int32	sprg0;
	int32	filler2;	/* force alignment on quad-word */
	int32	filler3;
	int32	filler4;
	int32	r0;
	int32	r1;			/* stack ptr */
	int32	r2;
	int32	r3;
	int32	r4;
	int32	r5;
	int32	r6;
	int32	r7;
	int32	r8;
	int32	r9;
	int32	r10;
	int32	r11;
	int32	r12;
	int32	r13;
	int32	r14;
	int32	r15;
	int32	r16;
	int32	r17;
	int32	r18;
	int32	r19;
	int32	r20;
	int32	r21;
	int32	r22;
	int32	r23;
	int32	r24;
	int32	r25;
	int32	r26;
	int32	r27;
	int32	r28;
	int32	r29;
	int32	r30;
	int32	r31;
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
	B_ACKNOWLEGE_IMAGE_CREATED,	/* acknowlege image created */
	B_START_PROFILER,			/* start profiler */
	B_STOP_PROFILER				/* stop profiler */
};

/* -----
	structures passed to the nub
----- */

typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	int32		count;					/* # bytes */
	char		*addr;					/* address to read */
} nub_read_memory_msg;
	
typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	int32		count;					/* # bytes */
	char		*addr;					/* address to write */
} nub_write_memory_msg;

typedef struct {
	thread_id	thread;					/* thread id */
	int32		align_to_double;		/* for alignment */
	cpu_state	cpu;					/* cpu state */
} nub_run_thread_msg;

typedef struct {
	thread_id	thread;					/* thread id */
	int32		align_to_double;		/* for alignment */
	cpu_state	cpu;					/* cpu state */
	char		*low_pc;				/* low end of pc range */
	char		*high_pc;				/* highend of pc range */
} nub_step_thread_msg;

typedef struct {
	thread_id	thread;					/* thread id */
	int32		align_to_double;		/* for alignment */
	cpu_state	cpu;					/* cpu state */
	char		*low_pc;				/* low end of pc range */
	char		*high_pc;				/* highend of pc range */
} nub_step_over_thread_msg;

typedef struct {
	thread_id	thread;					/* thread id */
	int32		align_to_double;		/* for alignment */
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
	int32	debug_flags;				/* returned thread debugging flags */
} nub_get_thread_debug_info_reply;

typedef struct {
	int32	token;
} nub_acknowlege_image_created_msg;

typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	thread_id	thid;
	int32		num;
	int32		slots[1];
} nub_start_profiler_msg;	

typedef struct {
	port_id		reply_port;				/* port for reply from kernel */
	thread_id	thid;
} nub_stop_profiler_msg;	

typedef struct {
	int32		num;
	int32		slots[1];
} nub_stop_profiler_reply;

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
	nub_start_profiler_msg				nub_start_profiler;
	nub_stop_profiler_msg				nub_stop_profiler;
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
	int32		reply_token;	/* token to acknowledge receipt (REQUIRED!) */
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
