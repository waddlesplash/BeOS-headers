/* ++++++++++
	OS.h

	Copyright (C) 1991-4 Be Inc.  All Rights Reserved.
	Interface file for kernel functions.

+++++ */

#ifndef _OS_H
#define _OS_H

#ifndef _SUPPORT_DEFS_H
#include "support/SupportDefs.h"
#endif

#ifndef _OS_DEFS_H
#include <os/OSDefs.h>
#endif

#ifdef __CPLUSPLUS__
extern "C" {
#endif


typedef int	area_id;
typedef int	port_id;
typedef int	sem_id;
typedef int	thread_id;
typedef int	team_id;

/*---------------------------------------------------------------------------*/
/*
 * Interfaces for area management calls
 */

/* Core/swap constants */
#define NO_LOCK		0	/* swapped as needed */
#define LAZY_LOCK	1	/* locked when paged in; was ATTR_ONDEMAND */
#define FULL_LOCK	2	/* locked at creation; was ATTR_LOCK */

/* Starting address spec */
#define ANY_ADDR	0	/* no address specification; was NOSPEC */
#define EXACT_ADDR	1	/* area start must equal addr; was SPEC */
#define BASE_ADDR	2	/* must start at or above addr; was BASESPEC */
#define CLONE_ADDR	3	/* For cloning only; same as EXACT_ADDR with an
					address of source.address. */
/* Protection */
#define READ_AREA	1	/* was PROT_URD */
#define WRITE_AREA	2	/* was PROT_UWR */

typedef struct area_info {
	area_id		area;
	char		name[OS_NAME_LENGTH];
	char		*address;
	ulong		size;
	uint		lock;
	uint		protection;
	team_id		team;
} area_info;

/* area_for returns the area that contains the given address.  The
address is assumed to be in the "current" team is assumed; this means
that you can't get the area for an address in some other team, but
I figure if an area creator wants to let other teams share his areas,
he'll publish their names.  
*/

extern area_id	create_area(char *name, char **addr, int addr_spec, uint size,
		uint lock, uint protection);
extern area_id	find_area(char *name);
extern area_id	area_for(char *addr);
extern area_id	clone_area(char *name, char **dest_addr, uint addr_spec,
		 uint protection, area_id source);
extern int	delete_area(area_id id);
extern int	resize_area(area_id id, uint new_size);
extern int	set_area_protection(area_id id, uint new_protection);
extern int	get_area_info(area_id id, area_info *ainfo);


/*---------------------------------------------------------------------------*/
/*
 * Queued data ports
 */

#define MAX_PORT_COUNT		(128)

extern port_id	create_port(long capacity, char *name);
extern int	write_port(port_id port, long code, void *buf, int buf_size);
extern int 	read_port(port_id port, long *code, void *buf, int buf_size);
extern int	port_buf_size(port_id port);
extern int	port_count(port_id port);
extern int	get_port_name(port_id port, char *name);
extern int	delete_port(port_id port);
extern port_id	find_port(char *name);

/*---------------------------------------------------------------------------*/
/*
 * Semaphore calls
 */


sem_id		create_sem(long count, char *name);
int		delete_sem(sem_id sem);

int		acquire_sem(sem_id sem);
int		release_sem(sem_id sem);
int		release_sem_count(sem_id sem, long count);
int		get_sem_count(sem_id sem, long *count);
int		get_sem_name(sem_id sem, char *name);

/*---------------------------------------------------------------------------*/
/*
 * Thread related calls
 */

typedef enum {
	THREAD_RUNNING=1,
	THREAD_READY,
	THREAD_RECEIVING,
	THREAD_ASLEEP,
	THREAD_SUSPENDED,
	THREAD_SEM_WAIT
} thread_state;

/* Thread priority levels */
#define LOW_LEVEL	10
#define NORMAL_LEVEL	20
#define DISPLAY_LEVEL	30
#define REALTIME_LEVEL  40	

typedef struct  {
	thread_id	thread;
	team_id		team;
	char		name[OS_NAME_LENGTH];		
	thread_state	state;		
	int		priority;
	sem_id		sem;		
	ulong		ticks;		
} thread_info;

extern thread_id	spawn_thread(	PFV func, 
					char *name, 
					int priority, 
					int argc, 
					char **argv);
				 
extern thread_id	find_thread(char *name); 
extern int		kill_thread(thread_id thread);
extern int		get_thread_info(thread_id thread, thread_info *info);
extern int		get_nth_thread_info(int n, team_id tmid, thread_info *info);
extern int		resume_thread(thread_id thread);
extern int		suspend_thread(thread_id thread);
extern int		rename_thread(thread_id thread, char *name);
extern int		snooze(int milliseconds);

/*---------------------------------------------------------------------------*/
/*
 * Unqueued, thread-specific data transmission
 */
extern int send_data(thread_id thread, int code, char *buf, int buf_size);
extern int receive_data(thread_id *sender, char *buf, int buf_size);
extern bool has_data(thread_id thread);

/*---------------------------------------------------------------------------*/
/*
 * the Joystick driver.
 */

typedef struct joysticks {
	char	x1;
	char	y1;
	char 	left_button1;
	char	right_button1;
	char	x2;
	char	y2;
	char 	left_button2;
	char	right_button2;
} joysticks;

/*---------------------------------------------------------------------------*/
/*
 * the Keyboard driver.
 */

typedef struct {
	bool	keyDown;
	uchar	rawKeyCode;
	ulong	modifiers;
	uchar	key_states[16];
} keyRecord;

/*---------------------------------------------------------------------------*/
/*
 * Miscellaneous calls
 */

extern void	debugger (char *message);

#ifdef __CPLUSPLUS__
}
#endif

#endif		/* ifdef oskernelh */
