/* ++++++++++
	KernelExport.h

	Functions exported from the kernel for driver use that are not already
	prototyped elsewhere.
	
	Copyright 1996-98, Be Incorporated.
+++++ */


#ifndef _KERNEL_EXPORT_H
#define _KERNEL_EXPORT_H

#include <BeBuild.h>
#include <SupportDefs.h>
#include <OS.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ---
	kernel threads
--- */

extern _IMPEXP_KERNEL thread_id spawn_kernel_thread (
	thread_entry	function, 
	const char 		*thread_name, 
	long			priority,
	void			*arg
);


/* ---
	disable/restore interrupt enable flag on current cpu
--- */

typedef ulong		cpu_status;

extern _IMPEXP_KERNEL cpu_status	disable_interrupts();
extern _IMPEXP_KERNEL void			restore_interrupts(cpu_status status);


/* ---
	spinlocks.  Note that acquire/release should be called with
	interrupts disabled.
--- */

typedef vlong	spinlock;

extern _IMPEXP_KERNEL void			acquire_spinlock (spinlock *lock);
extern _IMPEXP_KERNEL void			release_spinlock (spinlock *lock);


/* ---
	An interrupt handler returns TRUE if it handled the interrupt
--- */

typedef bool (*interrupt_handler) (void *data);

/* ---
	virtual memory buffer functions
--- */

#define		B_DMA_IO		0x00000001
#define		B_READ_DEVICE	0x00000002

typedef struct {
	void		*address;				/* address in physical memory */
	ulong		size;					/* size of block */
} physical_entry;

extern _IMPEXP_KERNEL long		lock_memory (
	void		*buf,			/* -> virtual buffer to lock (make resident) */
	ulong		num_bytes,		/* size of virtual buffer */
	ulong		flags
);

extern _IMPEXP_KERNEL long		unlock_memory (
	void		*buf,			/* -> virtual buffer to unlock */
	ulong		num_bytes,		/* size of virtual buffer */
	ulong		flags
);

extern _IMPEXP_KERNEL long		get_memory_map (
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

extern _IMPEXP_KERNEL area_id	map_physical_memory (
	const char	*area_name,
	void		*physical_address,
	size_t		size,
	uint32		address_spec,
	uint32		protection,
	void		**mapped_address
);


/* -----
	access to i/o space, both on PCI and ISA busses.  A driver must first map the
	range they wish to access.  For ISA devices, they pass the starting port number and
	size.  For PCI devices, they pass the base register value and the size.  Once mapped,
	drivers can use any address in the returned mapped range with the read/write_io_xxx
	calls to access the i/o space.

	NOTE: not imeplemented yet.
----- */

extern _IMPEXP_KERNEL status_t	map_io_range (
	uint32		start_of_range,		/* start of i/o range to be mapped */
	size_t		size,				/* size of range to be mapped */
	uint32		flags,				/* flags (see below) */
	uint32		*mapped_io_address	/* returned: start of mapped range */
);

enum {
	B_ALLOW_MULTIPLE_IO_MAPPING = 1
};

extern _IMPEXP_KERNEL status_t	unmap_io_range (
	uint32		mapped_io_address	/* start of mapped range */
);


/* -----
	allocate some space in the i/o address space map.  Used for unusual devices that
	do NOT use a PCI base register to request i/o space, but instead expect the
	allocation to be done later and filled in.  Most PCI devices will just use 
	a base register, for which this allocation has already been done.

	NOTE: not implemented yet.
----- */

extern _IMPEXP_KERNEL status_t	allocate_and_map_io_range (
	uint32		address,				/* address (if needed - see flags) */
	size_t		size,					/* size of range to be mapped */
	uint32		alignment,				/* alignment desired (1,2,4,8 etc) */
	uint32		flags,					/* flags (see below) */
	uint32		*allocated_io_address,	/* returned: start of allocated, unmapped range */
	uint32		*mapped_io_address		/* returned: start of mapped range */
);

extern _IMPEXP_KERNEL status_t	unallocate_io_range (
	uint32		allocated_io_address	/* start of allocated, unmapped range */
);

enum {
	B_ANY_IO_ADDRESS = 1,				/* map at any address */
	B_EXACT_IO_ADDRESS = 2,				/* map at exactly passed address */
	B_HIGHER_IO_ADDRESS = 4,			/* map above passed address */
	B_LOWER_IO_ADDRESS = 8				/* map below passed address */
};


/* -----
	i/o space access
----- */

extern _IMPEXP_KERNEL uint8		read_io_8 (int mapped_io_addr);
extern _IMPEXP_KERNEL void		write_io_8 (int mapped_io_addr, uint8 value);
extern _IMPEXP_KERNEL uint16	read_io_16 (int mapped_io_addr);
extern _IMPEXP_KERNEL void		write_io_16 (int mapped_io_addr, uint16 value);
extern _IMPEXP_KERNEL uint32	read_io_32 (int mapped_io_addr);
extern _IMPEXP_KERNEL void		write_io_32 (int mapped_io_addr, uint32 value);


/* ---
	address of system memory when viewed from ISA or PCI (by bus masters).
--- */

extern _IMPEXP_KERNEL void		*ram_address (const void *physical_address_in_system_memory);

/* ---
	ISA dma support
--- */

#define B_MAX_ISA_DMA_COUNT	0x10000

extern _IMPEXP_KERNEL long		lock_isa_dma_channel (long channel);
extern _IMPEXP_KERNEL long		unlock_isa_dma_channel (long channel);

extern _IMPEXP_KERNEL long start_isa_dma (
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

extern _IMPEXP_KERNEL long		make_isa_dma_table (
	const void		*buffer,		/* buffer to make a table for */
	long			buffer_size,	/* buffer size */
	ulong			num_bits,		/* dma transfer size that will be used */
	isa_dma_entry	*table,			/* -> caller-supplied scatter/gather table */
	long			num_entries		/* max # entries in table */
);

extern _IMPEXP_KERNEL long		start_scattered_isa_dma (
	long				channel,	/* channel # to use */
	const isa_dma_entry	*table,		/* -> scatter/gather table */
	uchar				mode,		/* mode flags */
	uchar				emode		/* extended mode flags */
);


/* interrupt handling support for device drivers */

extern _IMPEXP_KERNEL long 	install_io_interrupt_handler (
	long 				interrupt_number, 
	interrupt_handler	handler, 
	void				*data, 
	ulong 				flags
);
extern _IMPEXP_KERNEL long 	remove_io_interrupt_handler (
	long 				interrupt_number,
	interrupt_handler	handler
);


/* -----
	hardware inquiry
----- */

/* platform_type return value is defined in OS.h */

extern _IMPEXP_KERNEL platform_type	platform();
extern _IMPEXP_KERNEL long			motherboard_version (void);
extern _IMPEXP_KERNEL long			io_card_version (void);


/* ---
	primitive kernel debugging facilities.   Debug output is on serial port 4
	at 19.2 kbaud, no parity, 8 bit, 1 stop bit.
--- */

extern _IMPEXP_KERNEL void		dprintf (const char *format, ...);		/* just like printf */
extern _IMPEXP_KERNEL bool		set_dprintf_enabled (bool new_state);	/* returns old state */

extern _IMPEXP_KERNEL void		panic(const char *format, ...);

extern _IMPEXP_KERNEL void		kernel_debugger (const char *message);	/* enter kernel debugger */
extern _IMPEXP_KERNEL void		kprintf (const char *fmt, ...);         /* only for debugger cmds */
extern _IMPEXP_KERNEL ulong		parse_expression (char *str);           /* util for debugger cmds */
extern _IMPEXP_KERNEL int		add_debugger_command (char *name,       /* add a cmd to debugger */
									int (*func)(int argc, char **argv), 
									char *help);
extern _IMPEXP_KERNEL int		load_driver_symbols(const char *driver_name);


/* -----
	misc
----- */

extern _IMPEXP_KERNEL void	spin (bigtime_t num_microseconds);
extern _IMPEXP_KERNEL int	register_kernel_daemon(void (*func)(void *, int), void *arg, int freq);
extern _IMPEXP_KERNEL int	unregister_kernel_daemon(void (*func)(void *, int), void *arg);
extern _IMPEXP_KERNEL int	has_signals_pending(struct thread_rec *);

#ifdef __cplusplus
}
#endif

#endif
