/*****************************************************************************

	File:		OS.h

	Description:	Operating System functions.

	Copyright 1992-96, Be Incorporated, All Rights Reserved.

*****************************************************************************/

#ifndef _OS_H
#define _OS_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* -----
	system-wide constants
----- */

#define B_FILE_NAME_LENGTH		64		
#define B_OS_NAME_LENGTH		32		
#define B_PAGE_SIZE				4096		

/* -----
	types
----- */

typedef long	area_id;
typedef long	port_id;
typedef long	sem_id;
typedef long	thread_id;
typedef long	team_id;

/*--------------------------------------------------------------------------*/

/* Areas */

#define B_NO_LOCK			0	
#define B_LAZY_LOCK			1	
#define B_FULL_LOCK			2	

#define B_ANY_ADDRESS		0	
#define B_EXACT_ADDRESS		1	
#define B_BASE_ADDRESS		2	
#define B_CLONE_ADDRESS		3	
				
#define B_READ_AREA			1	
#define B_WRITE_AREA		2	

typedef struct area_info {
	area_id		area;
	char		name[B_OS_NAME_LENGTH];
	void		*address;
	ulong		size;
	ulong		lock;
	ulong		protection;
	team_id		team;
	ulong		ram_size;
	ulong		copy_count;
	ulong		in_count;
	ulong		out_count;
} area_info;

extern area_id	create_area(const char *name, void **start_addr,
					ulong addr_spec, ulong size, ulong lock, ulong protection);
extern area_id	find_area(const char *name);
extern area_id	area_for(void *addr);
extern area_id	clone_area(const char *name, void **dest_addr, ulong addr_spec,
					ulong protection, area_id source);
extern long		delete_area(area_id id);
extern long		resize_area(area_id id, ulong new_size);
extern long		set_area_protection(area_id id, ulong new_protection);
extern long		get_area_info(area_id id, area_info *ainfo);
extern long		get_nth_area_info(team_id team, long n, area_info *ainfo);


/*--------------------------------------------------------------------------*/

/* Ports */

#define B_MAX_PORT_COUNT		(128)

typedef struct port_info {
	port_id		port;
	team_id		team;
	char		name[B_OS_NAME_LENGTH];
	long		capacity; /* queue depth */
	long		queue_count; /* # msgs waiting to be read */
	long		total_count; /* total # msgs read so far */
} port_info;

extern port_id	create_port(long capacity, const char *name);
extern port_id	find_port(const char *name);

extern long		write_port(port_id port, long code, const void *buf, long buf_size);
extern long 	read_port(port_id port, long *code, void *buf, long buf_size);

extern long		write_port_etc(port_id port, long code, const void *buf, long buf_size,
                              int flags, double timeout);
extern long 	read_port_etc(port_id port, long *code, void *buf, long buf_size,
                              int flags, double timeout);

extern long		port_buffer_size(port_id port);
extern long		port_buffer_size_etc(port_id port, int flags, double timeout);

extern long		port_count(port_id port);
extern long		set_port_owner(port_id port, team_id team);

extern long		delete_port(port_id port);

extern long		get_port_info(port_id port, port_info *info);
extern long		get_nth_port_info(team_id team, long n, port_info *info);

/*--------------------------------------------------------------------------*/

/* Semaphores */

typedef struct sem_info {
	sem_id 		sem;
	team_id 	team;
	char		name[B_OS_NAME_LENGTH];
	long		count;
	thread_id 	latest_holder;
} sem_info;

extern sem_id	create_sem(long count, const char *name);
extern long		delete_sem(sem_id sem);
extern long		acquire_sem(sem_id sem);
extern long		acquire_sem_etc(sem_id sem, int count, int flags,
								double microsecond_timeout);
extern long		release_sem(sem_id sem);
extern long		release_sem_etc(sem_id sem, long count, long flags);
extern long		get_sem_count(sem_id sem, long *count); /* XXXdbg -- should go away  */

extern long		set_sem_owner(sem_id sem, team_id team);

extern long		get_sem_info(sem_id sem, sem_info *info);
extern long		get_nth_sem_info(team_id team, long n, sem_info *info);


/* -----
	flags for semaphore control
----- */

enum {
	B_CAN_INTERRUPT     = 1, 	/* semaphore can be interrupted by a signal */
	B_DO_NOT_RESCHEDULE = 2,	/* release() without rescheduling */
	B_CHECK_PERMISSION  = 4,	/* disallow users changing kernel semaphores */
	B_TIMEOUT           = 8     /* honor the timeout parameter */
};

/*--------------------------------------------------------------------------*/

/* Threads */

typedef enum {
	B_THREAD_RUNNING=1,
	B_THREAD_READY,
	B_THREAD_RECEIVING,
	B_THREAD_ASLEEP,
	B_THREAD_SUSPENDED,
	B_THREAD_WAITING
} thread_state;

#define B_LOW_PRIORITY						5
#define B_NORMAL_PRIORITY					10
#define B_DISPLAY_PRIORITY					15
#define	B_URGENT_DISPLAY_PRIORITY			20
#define	B_REAL_TIME_DISPLAY_PRIORITY		100
#define	B_URGENT_PRIORITY					110
#define B_REAL_TIME_PRIORITY				120

typedef struct  {
	thread_id		thread;
	team_id			team;
	char			name[B_OS_NAME_LENGTH];
	thread_state	state;
	long			priority;
	sem_id			sem;
	double			user_time;
	double			kernel_time;
	void			*stack_base;
	void			*stack_end;
} thread_info;

typedef long (*thread_entry) (void *);

extern thread_id spawn_thread (
	thread_entry	function_name, 
	const char 		*thread_name, 
	long			priority, 
	void			*arg
);
				 
extern thread_id	find_thread(const char *name); 
extern long			kill_thread(thread_id thread);
extern long			get_thread_info(thread_id thread, thread_info *info);
extern long			get_nth_thread_info(team_id tmid, long n, thread_info *info);
extern long			resume_thread(thread_id thread);
extern long			suspend_thread(thread_id thread);
extern long			rename_thread(thread_id thread, const char *new_name);
extern long			set_thread_priority (thread_id thread, long new_priority);
extern void         exit_thread(long status);
extern long			wait_for_thread (thread_id thread, long *thread_return_value);
extern long			snooze(double microseconds);

extern long send_data(thread_id thread, long code, const void *buf, long buffer_size);
extern long receive_data(thread_id *sender, void *buf, long buffer_size);
extern bool has_data(thread_id thread);

/*--------------------------------------------------------------------------*/

/* Teams */

#define	B_SYSTEM_TEAM		2

typedef struct {
	team_id			team;
	long			image_count;
	long			thread_count;
	long			area_count;
	thread_id		debugger_nub_thread;
	port_id			debugger_nub_port;

	long            argc;      /* number of args on the command line */
	char            args[64];  /* abbreviated command line args */
} team_info;
	
extern long			kill_team(team_id team);
extern long			get_team_info(team_id team, team_info *info);
extern long			get_nth_team_info(long n, team_info *info);
	
/*--------------------------------------------------------------------------*/

/* System information */

#define		B_MAX_CPU_COUNT		8

#define		B_CPU_PPC_601		1
#define		B_CPU_PPC_603		2
#define		B_CPU_PPC_603e		3
#define		B_CPU_PPC_604		4
#define		B_CPU_PPC_604e		5
#define		B_CPU_PPC_686		13

typedef struct {
	double		active_time;				/* # usec doing useful work since boot */
} cpu_info;

typedef long machine_id[2];					/* unique machine ID */

typedef struct {
	machine_id	id;							/* unique machine ID */
	double		boot_time;					/* time of boot (# usec since 1/1/70) */
	long		cpu_count;					/* # of cpus */
	long		cpu_type;					/* type of cpu */
	long		cpu_revision;				/* revision # of cpu */
	cpu_info	cpu_infos[B_MAX_CPU_COUNT];	/* info about individual cpus */
	double		cpu_clock_speed;	 		/* processor clock speed (Hz) */
	double		bus_clock_speed;			/* bus clock speed (Hz) */
	long		max_pages;					/* total # physical pages */
	long		used_pages;					/* # physical pages in use */
	long		page_faults;				/* # of page faults */
	long		max_sems;					/* maximum # semaphores */
	long		used_sems;					/* # semaphores in use */
	long		max_ports;					/* maximum # ports */
	long		used_ports;					/* # ports in use */
	long		max_threads;				/* maximum # threads */
	long		used_threads;				/* # threads in use */
	long		max_teams;					/* maximum # teams */
	long		used_teams;					/* # teams in use */
	long		volume;						/* volume id of kernel */
	long		directory;					/* directory id of kernel */
	char		name [B_FILE_NAME_LENGTH];	/* name of kernel */
} system_info;

extern long	get_system_info (system_info *returned_info);
extern long is_computer_on(void);
double system_time (void);	/* time since booting in microseconds */

/* Basic debugging and heap check calls. */
extern void	debugger (const char *message);
extern void	heap_check_on(void);
extern void	heap_check_off(void);

#ifdef __cplusplus
}
#endif

#endif		/* ifdef _OS_H */
