/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	PCI bus manager
*/

#ifndef _PCI2_H
#define _PCI2_H

#include <pnp/pnp_driver.h>
#include "r5_wrapper.h"
#include <be/drivers/PCI.h>

// currently, this structure is disables to avoid collision with R5 header
#if 0

typedef struct pci_info {
	ushort	vendor_id;				/* vendor id */
	ushort	device_id;				/* device id */
	uchar	bus;					/* bus number */
	uchar	device;					/* device number on bus */
	uchar	function;				/* function number in device */
	uchar	revision;				/* revision id */
	uchar	class_api;				/* specific register interface type */
	uchar	class_sub;				/* specific device function */
	uchar	class_base;				/* device type (display vs network, etc) */
	uchar	line_size;				/* cache line size in 32 bit words */
	uchar	latency;				/* latency timer */
	uchar	header_type;			/* header type */
	uchar	bist;					/* built-in self-test */
	uchar	reserved;				/* filler, for alignment */
	union {
		struct {
			ulong	cardbus_cis;			/* CardBus CIS pointer */
			ushort	subsystem_id;			/* subsystem (add-in card) id */
			ushort	subsystem_vendor_id;	/* subsystem (add-in card) vendor id */
			ulong	rom_base;				/* rom base address, viewed from host */
			ulong	rom_base_pci;			/* rom base addr, viewed from pci */
			ulong	rom_size;				/* rom size */
			ulong	base_registers[6];		/* base registers, viewed from host */
			ulong	base_registers_pci[6];	/* base registers, viewed from pci */
			ulong	base_register_sizes[6];	/* size of what base regs point to */
			uchar	base_register_flags[6];	/* flags from base address fields */
			uchar	interrupt_line;			/* interrupt line */
			uchar	interrupt_pin;			/* interrupt pin */
			uchar	min_grant;				/* burst period @ 33 Mhz */
			uchar	max_latency;			/* how often PCI access needed */
		} h0;
		struct {
			ulong	base_registers[2];		/* base registers, viewed from host */
			ulong	base_registers_pci[2];	/* base registers, viewed from pci */
			ulong	base_register_sizes[2];	/* size of what base regs point to */
			uchar	base_register_flags[2];	/* flags from base address fields */
			uchar	primary_bus;
			uchar	secondary_bus;
			uchar	subordinate_bus;
			uchar	secondary_latency;
			uchar	io_base;
			uchar	io_limit;
			ushort	secondary_status;
			ushort	memory_base;
			ushort	memory_limit;
			ushort  prefetchable_memory_base;
			ushort  prefetchable_memory_limit;
			ulong	prefetchable_memory_base_upper32;
			ulong	prefetchable_memory_limit_upper32;
			ushort	io_base_upper16;
			ushort	io_limit_upper16;
			ulong	rom_base;				/* rom base address, viewed from host */
			ulong	rom_base_pci;			/* rom base addr, viewed from pci */
			uchar	interrupt_line;			/* interrupt line */
			uchar	interrupt_pin;			/* interrupt pin */
			ushort	bridge_control;		
		} h1; 
	} u;
} pci_info;

#endif


// PCI device node.
// the naming is not precise as there is one node per _function_ of a device,
// but as everyone is talking about PCI devices and not PCI functions, we
// follow this nomenclature

// type of PCI device
#define PCI_DEVICE_TYPE "pci"
// directory of PCI drivers
#define PCI_DRIVERS_DIR "pci"

// attributes of PCI device nodes
// bus idx (uint8)
#define PCI_DEVICE_BUS_ITEM "pci/bus"
// device idx (uint8)
#define PCI_DEVICE_DEVICE_ITEM "pci/device"
// function idx (uint8)
#define PCI_DEVICE_FUNCTION_ITEM "pci/function"

// vendor id (uint16)
#define PCI_DEVICE_VENDOR_ID_ITEM "pci/vendor_id"
// device id (uint16)
#define PCI_DEVICE_DEVICE_ID_ITEM "pci/device_id"
// subsystem id (uint16)
#define PCI_DEVICE_SUBSYSTEM_ID_ITEM "pci/subsystem_id"
// subvendor id (uint16)
#define PCI_DEVICE_SUBVENDOR_ID_ITEM "pci/subvendor_id"

// device base class (uint8)
#define PCI_DEVICE_BASE_CLASS_ID_ITEM "pci/class/base_id"
// device subclass (uint8)
#define PCI_DEVICE_SUB_CLASS_ID_ITEM "pci/class/sub_id"
// device api (uint8)
#define PCI_DEVICE_API_ID_ITEM "pci/class/api_id"

// full pci info, compatible to R5 (raw, type pci_info)
#define PCI_DEVICE_PCI_INFO_ITEM "pci/pci_info"


// dynamic consumer patterns for PCI devices
#define PCI_DEVICE_DYNAMIC_CONSUMER_0 \
	PCI_DRIVERS_DIR "/" \
	"vendor %" PCI_DEVICE_VENDOR_ID_ITEM "%|" \
	", device %" PCI_DEVICE_DEVICE_ID_ITEM "%|" \
	", subsystem %" PCI_DEVICE_SUBSYSTEM_ID_ITEM "%|" \
	", subvendor %" PCI_DEVICE_SUBVENDOR_ID_ITEM "%"
	
#define PCI_DEVICE_DYNAMIC_CONSUMER_1 \
	PCI_DRIVERS_DIR "/" \
	"base_class %" PCI_DEVICE_BASE_CLASS_ID_ITEM "%|" \
	", sub_class %" PCI_DEVICE_SUB_CLASS_ID_ITEM "%|" \
	", api %" PCI_DEVICE_API_ID_ITEM "%"


// priority of PCI device drivers
#define PCI_DRIVER_PRIORITY 2000
// priority of PCI infrastructure drivers
#define PCI_SYSTEM_PRIORITY 2100


typedef struct pci_device_info *pci_device;

// interface to be used by PCI device drivers.
typedef struct pci_device_interface {
	// execute I/O read/write accesses
	uint8	(*read_io_8) (pci_device device, int mapped_io_addr);
	void	(*write_io_8) (pci_device device, int mapped_io_addr, uint8 value);
	uint16	(*read_io_16) (pci_device device, int mapped_io_addr);
	void	(*write_io_16) (pci_device device, int mapped_io_addr, uint16 value);
	uint32	(*read_io_32) (pci_device device, int mapped_io_addr);
	void	(*write_io_32) (pci_device device, int mapped_io_addr, uint32 value);

	// read PCI configuration space
	uint32	(*read_pci_config) (
				pci_device device,
				uint8	offset,		/* offset in configuration space */
				uint8	size		/* # bytes to read (1, 2 or 4) */
			);
	// write PCI configuration space
	void	(*write_pci_config) (
				pci_device device, 
				uint8	offset,		/* offset in configuration space */
				uint8	size,		/* # bytes to write (1, 2 or 4) */
				uint32	value		/* value to write */
			);

	// map system memory address as seen by CPU to bus address as seen by PCI device.
	// on x86, PCI devices and CPU use same addresses, but on other
	// architectures, this can be different;
	void *	(*ram_address) (pci_device device, const void *physical_address_in_system_memory);

	// get size of base register or rom
	// (only fails if node attribute is broken)
	status_t(*get_pci_info) (
				pci_device cookie,
				pci_info *pcii		/* PCI info, retrieved from node attribute */
			);

} pci_device_interface;

#define PCI_DEVICE_INTERFACE	"pci/device/v1"


#endif
