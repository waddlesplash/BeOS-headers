/* ++++++++++
	KernelExport.h

	Functions exported from the kernel for driver use that are not already
	prototyped elsewhere.
	
	Copyright 1996, Be Incorporated.
+++++ */

#ifndef _KERNEL_EXPORT_H
#define _KERNEL_EXPORT_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _OS_H
#include <OS.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* ---
	kernel threads
--- */

extern thread_id spawn_kernel_thread (
	thread_entry	function, 
	const char 		*thread_name, 
	long			priority,
	void			*arg
);


/* ---
	disable/restore interrupt enable flag on current cpu
--- */

typedef ulong		cpu_status;

extern cpu_status	disable_interrupts();
extern void			restore_interrupts(cpu_status status);


/* ---
	spinlocks.  Note that acquire/release should be called with
	interrupts disabled.
--- */

typedef vlong	spinlock;

extern spinlock *		create_spinlock (void);
extern void				delete_spinlock (spinlock *lock);
extern void				acquire_spinlock (spinlock *lock);
extern void				release_spinlock (spinlock *lock);


/* ---
	An interrupt handler returns TRUE if it handled the interrupt
--- */

typedef bool (*interrupt_handler) (void *data);


/* ---
	ISA interrupts, access to ISA i/o space
--- */

extern long		disable_isa_interrupt (long irq_number);
extern long		enable_isa_interrupt (long irq_number);
extern long		set_isa_interrupt_handler (
	long				irq_number,
	interrupt_handler	handler,
	void				*data
);

extern void		*isa_address (long offset_in_isa_io_space);


/* ---
	virtual memory buffer functions
--- */

typedef struct {
	void	*address;				/* address in physical memory */
	ulong	size;					/* size of block */
} physical_entry;

extern long		lock_memory (
	void			*buf,			/* -> virtual buffer to lock (make resident) */
	ulong			num_bytes,		/* size of virtual buffer */
	bool			set_dirty		/* mark pages as dirty? (for reads) */
);

extern long		unlock_memory (
	void			*buf,			/* -> virtual buffer to unlock */
	ulong			num_bytes		/* size of virtual buffer */
);

extern long		get_memory_map (
	void			*address,		/* -> virtual buffer to translate */
	ulong			size,			/* size of virtual buffer */
	physical_entry	*table,			/* -> caller supplied table */
	long			num_entries		/* # entries in table */
);
	

/* ---
	ISA dma support
--- */

#define B_MAX_ISA_DMA_COUNT	0x10000

extern long		lock_isa_dma_channel (long channel);
extern long		unlock_isa_dma_channel (long channel);

extern long start_isa_dma (
	long	channel,				/* dma channel to use */
	void	*buf,					/* buffer to transfer */
	long	transfer_count,			/* # transfers */
	uchar	mode,					/* mode flags */
	uchar	e_mode					/* extended mode flags */
);


/* ---
	ISA scatter/gather dma support.
--- */

typedef struct {
	ulong	address;				/* memory address (little endian!) */
	ushort	transfer_count;			/* # transfers minus one (little endian!) */
	uchar	reserved;				/* filler */
	struct {
		int	end_of_list	: 1;		/* end of list flag */
		int reserved	: 7;		/* filler */
	} flags;
} isa_dma_entry;

enum {
	B_8_BIT_TRANSFER,
	B_16_BIT_TRANSFER
};

extern long		make_isa_dma_table (
	void			*buffer,		/* buffer to make a table for */
	long			buffer_size,	/* buffer size */
	ulong			num_bits,		/* dma transfer size that will be used */
	isa_dma_entry	*table,			/* -> caller-supplied scatter/gather table */
	long			num_entries		/* max # entries in table */
);

extern long		start_scattered_isa_dma (
	long			channel,		/* channel # to use */
	isa_dma_entry	*table,			/* -> scatter/gather table */
	uchar			mode,			/* mode flags */
	uchar			emode			/* extended mode flags */
);


/* ---
	Be's onboard interrupt controller support
--- */

extern long		disable_io_interrupt (long interrupt_number);
extern long		enable_io_interrupt (long interrupt_number);
extern long		set_io_interrupt_handler (
	long				interrupt_number,
	interrupt_handler	handler,
	void				*data
);


/* -----
	hardware inquiry
----- */

extern long		motherboard_version (void);
extern long		io_card_version (void);


/* ---
	primitive kernel debugging facilities.   Debug output is on serial port 4
	at 19.2 kbaud, no parity, 8 bit, 1 stop bit.
--- */

extern void		dprintf (const char *format, ...);		/* just like printf */
extern bool		set_dprintf_enabled (bool new_state);	/* returns old state */
extern void		kernel_debugger (const char *message);	/* enter kernel debugger */


/* -----
	misc
----- */

extern void		spin (double num_microseconds);


/* -----
	flags for semaphore control
----- */

enum {
	B_CAN_INTERRUPT = 1,			/* semaphore can be interrupted by a signal */
	B_DO_NOT_RESCHEDULE = 2,		/* release() without rescheduling */
	B_CHECK_PERMISSION = 4			/* disallow users changing kernel semaphores */
};

/* ----------
	souped-up versions of semaphore routines with more explicit
	semantic control.
---- */

extern long acquire_sem_flag (sem_id sem, long flags);
extern long acquire_sem_count_flag (sem_id sem, long count, long flags);
extern long acquire_sem_timeout_flag (sem_id sem, double timeout, long flags);
extern long acquire_sem_count_timeout_flag (sem_id sem, long count,
										   double timeout, long flags);
extern long release_sem_count_flag (sem_id sem, long count, long flags);


#ifdef __cplusplus
}
#endif

#endif
