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
	long		size;
	ulong		lock;
	ulong		protection;
	team_id		team;
	long		ram_size;
	long		copy_count;
	long		in_count;
	long		out_count;
} area_info;

extern area_id	create_area(const char *name, void **start_addr,
					ulong addr_spec, long size, ulong lock, ulong protection);
extern area_id	find_area(const char *name);
extern area_id	area_for(void *addr);
extern area_id	clone_area(const char *name, void **dest_addr, ulong addr_spec,
					ulong protection, area_id source);
extern long		delete_area(area_id id);
extern long		resize_area(area_id id, long new_size);
extern long		set_area_protection(area_id id, ulong new_protection);
extern long		get_area_info(area_id id, area_info *ainfo);
extern long		get_nth_area_info(team_id team, long n, area_info *ainfo);


/*--------------------------------------------------------------------------*/

#define B_MAX_PORT_COUNT		(128)

extern port_id	create_port(long capacity, const char *name);
extern long		write_port(port_id port, long code, void *buf, long buf_size);
extern long 	read_port(port_id port, long *code, void *buf, long buf_size);
extern long		port_buffer_size(port_id port);
extern long		port_count(port_id port);
extern long		get_port_name(port_id port, char *name);
extern long		delete_port(port_id port);
extern port_id	find_port(const char *name);

/*--------------------------------------------------------------------------*/

extern sem_id	create_sem(long count, const char *name);
extern long		delete_sem(sem_id sem);
extern long		acquire_sem(sem_id sem);
extern long		acquire_sem_count(sem_id sem, long count);
extern long		acquire_sem_timeout(sem_id sem, double microsecond_timeout);
extern long		release_sem(sem_id sem);
extern long		release_sem_count(sem_id sem, long count);
extern long		get_sem_count(sem_id sem, long *count);
extern long		get_sem_name(sem_id sem, char *name);

/*--------------------------------------------------------------------------*/


typedef enum {
	B_THREAD_RUNNING=1,
	B_THREAD_READY,
	B_THREAD_RECEIVING,
	B_THREAD_ASLEEP,
	B_THREAD_SUSPENDED,
	B_THREAD_WAITING
} thread_state;

#define B_LOW_PRIORITY			10
#define B_NORMAL_PRIORITY		20
#define B_DISPLAY_PRIORITY		30
#define B_REAL_TIME_PRIORITY	40	

typedef struct  {
	thread_id		thread;
	team_id			team;
	char			name[B_OS_NAME_LENGTH];
	thread_state	state;
	long			priority;
	sem_id			sem;
	double			time;
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
extern long			wait_for_thread (thread_id thread, long *thread_return_value);
extern long			snooze(double microseconds);


extern long send_data(thread_id thread, long code, void *buf, long buffer_size);
extern long receive_data(thread_id *sender, void *buf, long buffer_size);
extern bool has_data(thread_id thread);

double system_time (void);	/* time since booting in microseconds */

/*--------------------------------------------------------------------------*/

typedef struct {
	team_id			team;
	long			object_count;
	long			thread_count;
	long			area_count;
	thread_id		debugger_nub_thread;
	port_id			debugger_nub_port;
} team_info;
	
extern long			kill_team(team_id team);
extern long			get_team_info(team_id team, team_info *info);
extern long			get_nth_team_info(long n, team_info *info);
	

/*--------------------------------------------------------------------------*/

/* ----------
	time is represented at the number of seconds since 00:00:00
	Jan 1 1970 Coordinated Universal Time (UTC).  The time zone is kept
	as an offset in seconds from the system time.  Library functions
	convert these to the local time.
----- */

long	real_time_clock (void);
void	set_real_time_clock (long secs_since_jan1_1970);

long	time_zone (void);
void	set_time_zone (long offset_from_utc);


/*--------------------------------------------------------------------------*/

#define		B_MAX_CPU_NUM		8

typedef struct {
	double		active_time;				/* # usec doing useful work since boot */
} cpu_info;

typedef struct {
	double		boot_time;					/* time of boot (# usec since 1/1/70) */
	long		cpu_count;					/* # of cpus */
	cpu_info	cpu_infos[B_MAX_CPU_NUM];		/* info about individual cpus */
	long		max_pages;					/* total # physical pages */
	long		used_pages;					/* # physical pages in use */
	long		max_sems;					/* maximum # semaphores */
	long		used_sems;					/* # semaphores in use */
	long		max_ports;					/* maximum # ports */
	long		used_ports;					/* # ports in use */
	long		max_threads;				/* maximum # threads */
	long		used_threads;				/* # threads in use */
	long		max_teams;					/* maximum # teams */
	long		used_teams;					/* # teams in use */
	long		volume;						/* volume id of running kernel image */
	long		directory;					/* directory id of running kernel image */
	char		name [B_FILE_NAME_LENGTH];	/* name of running kernel */
} system_info;

extern long	get_system_info (system_info *returned_info);

/*--------------------------------------------------------------------------*/

extern void	debugger (const char *message);

extern void	heap_check_on(void);
extern void	heap_check_off(void);

/* ------
	useful assembly language routines
----- */

extern long atomic_add(void *value, long addvalue);	/* atomic add, return old value */
extern long atomic_and(void *value, long andvalue);	/* atomic and, return old value */
extern long atomic_or(void *value, long orvalue);	/* atomic or, return old value */

extern short	read_16_swap (void *address);
extern long		read_32_swap (void *address);
extern void		write_16_swap (void *address, short value);
extern void		write_32_swap (void *addr, long value);


#ifdef __cplusplus
}
#endif

#endif		/* ifdef _OS_H */
