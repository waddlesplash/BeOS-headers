/* ++++++++++
	KernelExport.h

	Functions exported from the kernel for driver use that are not already
	prototyped elsewhere.
	
	Copyright 1996-97, Be Incorporated.
+++++ */


#ifndef _KERNEL_EXPORT_H
#define _KERNEL_EXPORT_H

#include <SupportDefs.h>
#include <OS.h>

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

/* ---
	virtual memory buffer functions
--- */

#define		B_DMA_IO		0x00000001
#define		B_READ_DEVICE	0x00000002

typedef struct {
	void		*address;				/* address in physical memory */
	ulong		size;					/* size of block */
} physical_entry;

extern long		lock_memory (
	void		*buf,			/* -> virtual buffer to lock (make resident) */
	ulong		num_bytes,		/* size of virtual buffer */
	ulong		flags
);

extern long		unlock_memory (
	void		*buf,			/* -> virtual buffer to unlock */
	ulong		num_bytes,		/* size of virtual buffer */
	ulong		flags
);

extern long		get_memory_map (
	const void		*address,		/* -> virtual buffer to translate */
	ulong			size,			/* size of virtual buffer */
	physical_entry	*table,			/* -> caller supplied table */
	long			num_entries		/* # entries in table */
);
	

/* -----
	address specifications for mapping physical memory
----- */

#define	B_ANY_KERNEL_BLOCK_ADDRESS	((B_ANY_KERNEL_ADDRESS)+1)

/* -----
	call to map physical memory - typically used for memory-mapped i/o
----- */

extern area_id	map_physical_memory (
	const char	*area_name,
	void		*physical_address,
	size_t		size,
	uint32		address_spec,
	uint32		protection,
	void		**mapped_address
);

/* ---
	address of system memory when viewed from ISA or PCI (by bus masters).
--- */

extern void		*ram_address (const void *physical_address_in_system_memory);

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
	ulong	address;				/* memory address (little endian!) 4 bytes */
	ushort	transfer_count;			/* # transfers minus one (little endian!) 2 bytes*/
	uchar	reserved;				/* filler, 1byte*/
    uchar   flag;					/* end of link flag, 1byte */
} isa_dma_entry;

#define 	B_LAST_ISA_DMA_ENTRY	0x80	/* sets end of link flag in isa_dma_entry */

enum {
	B_8_BIT_TRANSFER,
	B_16_BIT_TRANSFER
};

extern long		make_isa_dma_table (
	const void		*buffer,		/* buffer to make a table for */
	long			buffer_size,	/* buffer size */
	ulong			num_bits,		/* dma transfer size that will be used */
	isa_dma_entry	*table,			/* -> caller-supplied scatter/gather table */
	long			num_entries		/* max # entries in table */
);

extern long		start_scattered_isa_dma (
	long				channel,	/* channel # to use */
	const isa_dma_entry	*table,		/* -> scatter/gather table */
	uchar				mode,		/* mode flags */
	uchar				emode		/* extended mode flags */
);


/* ---
	Be's onboard interrupt controller support
--- */

extern long		disable_io_interrupt (long interrupt_number);
extern long		enable_io_interrupt (long interrupt_number);
extern long		clear_io_interrupt (long interrupt_number);
extern long		set_io_interrupt_handler (
	long				interrupt_number,
	interrupt_handler	handler,
	void				*data
);


/* -----
	hardware inquiry
----- */

/* platform_type return value is defined in OS.h */

extern platform_type	platform();
extern long				motherboard_version (void);
extern long				io_card_version (void);


/* ---
	primitive kernel debugging facilities.   Debug output is on serial port 4
	at 19.2 kbaud, no parity, 8 bit, 1 stop bit.
--- */

extern void		dprintf (const char *format, ...);		/* just like printf */
extern bool		set_dprintf_enabled (bool new_state);	/* returns old state */

extern void     panic(const char *format, ...);

extern void		kernel_debugger (const char *message);	/* enter kernel debugger */
extern void     kprintf (const char *fmt, ...);         /* only for debugger cmds */
extern ulong    parse_expression (char *str);           /* util for debugger cmds */
extern int      add_debugger_cmd (char *name,           /* add a cmd to debugger */
                                  int (*func)(int argc, char **argv), 
                                  char *help);
extern int      load_driver_symbols(const char *driver_name);


/* -----
	misc
----- */

extern void		spin (bigtime_t num_microseconds);


#ifdef __cplusplus
}
#endif

#endif
