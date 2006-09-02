/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	ISA bus manager
	

	This is an improper name - this bus manager uses the PnP manager to
	load device drivers, but calling it ISA PnP manager would be wrong as
	ISA PnP information isn't used at all.
	
	All ISA drivers must be Universal Drivers (see pnp_manager.h), as they
	are all direct children of the ISA bus node. Having an ISA PnP bus manager
	(which we don't), one node would be created per ISA device and thus you 
	could write Specific drivers, but under normal ISA we don't even know 
	how many devices are there, therefore the Universal driver trick.

	Don't forget to acquire associated I/O resources before registering 
	a device node to avoid collisions.
*/

#ifndef _ISA2_H
#define _ISA2_H

#include <pnp/pnp_bus.h>


enum {
	B_8_BIT_TRANSFER,
	B_16_BIT_TRANSFER
};

// maximum size of one dma transfer 
// (in bytes for 8 bit transfer, in words for 16 bit transfer)
#define B_MAX_ISA_DMA_COUNT	0x10000



// ISA bus node.
// there is no generic node per device, so drivers talk to bus directly


// directory of ISA drivers
// (there is only one bus node, so put all drivers under "universal")
#define ISA_DRIVERS_DIR "isa"
// type of ISA bus node
#define ISA_BUS_TYPE "isa"


// priority of ISA device drivers
#define ISA_DRIVER_PRIORITY 1000


// interface to be used by ISA device drivers.
typedef struct isa_bus_interface {
	uint8 (*read_io_8)( int mapped_io_addr );
	void (*write_io_8)( int mapped_io_addr, uint8 value );
	uint16 (*read_io_16)( int mapped_io_addr );
	void (*write_io_16)( int mapped_io_addr, uint16 value );
	uint32 (*read_io_32)( int mapped_io_addr );
	void (*write_io_32)( int mapped_io_addr, uint32 value );
	
	// don't know what it's for, remains for compatibility
	void *(*ram_address)( const void *physical_address_in_system_memory );

	// start dma transfer (scattered DMA is not supported as it's EISA specific)
	status_t (*start_isa_dma)(
		long	channel,				// dma channel to use
		void	*buf,					// buffer to transfer
		long	transfer_count,			// # transfers
		uchar	mode,					// mode flags
		uchar	e_mode					// extended mode flags
	);
} isa_bus_interface;

#define ISA_BUS_INTERFACE "isa/bus/v1"


#endif
