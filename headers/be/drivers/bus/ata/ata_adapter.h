/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	Generic ATA host adapter library.
	
	
	Module to simplify writing an ATA host adapter driver.
	
	The interface is not very abstract, i.e. the actual driver is
	free to access any host adapter or channel data of this library.
*/

#ifndef _ATA_ADAPTER_H
#define _ATA_ADAPTER_H

#include <bus/PCI.h>
#include <bus/ATA.h>
#include <pnp/pnp_manager.h>


// one Physical Region Descriptor (PRD)
// (one region must not cross 64K boundary; 
//  the PRD table must not cross a 64K boundary)
typedef struct prd_entry {
	uint32 address;				// physical address of block (must be even)
	uint16 count;				// size of block, 0 stands for 65536 (must be even)
	uint8 res6;
	LBITFIELD8_2(
		res7_0 : 7,
		EOT : 1					// 1 for last entry
	);
} prd_entry;


// command register
typedef struct ata_bm_command {
	LBITFIELD8_4(
		start_stop	: 1,		// start BM by changing from 0 to 1; 
								// stop BM by changing from 1 to 0
		res0_1		: 2,
		from_device	: 1,		// true - read from device, false - write to device
		res0_4		: 4
	);
} ata_bm_command;


// status register
typedef struct ata_bm_status {
	LBITFIELD8_7(
		active		: 1,		// 1, if BM is active
		error		: 1,		// 1, if error occured; write 1 to reset
		interrupt	: 1,		// 1, if INTRQ was raised, write 1 to reset
		res0_3		: 2,
		device0_dma	: 1,		// 1, if BIOS/driver has setup DMA for device 0
		device1_dma	: 1,		// 1, if BIOS/driver has setup DMA for device 1
		simplex		: 1			// 1, if only one channel can use DMA at a time
	);
} ata_bm_status;


// offset of bus master registers
enum {
	ata_bm_command_reg	= 0,	// see ata_bm_command
	ata_bm_status_reg	= 2,	// see ata_bm_status
	ata_bm_prdt_address	= 4		// offset of PRDT register; content must be dword-aligned
};

// bit mask in class_api of PCI configuration
// (for adapters that can run in compatability mode)
enum {
	ata_api_primary_native		= 1,	// primary channel is in native mode
	ata_api_primary_fixed		= 2,	// primary channel can be switched to native mode
	ata_api_secondary_native	= 4,	// secondary channel is in native mode
	ata_api_secondary_fixed		= 8		// secondary channel can be switched to native mode
};


// (maximum) size of S/G table
// there are so many restrictions that we want to keep it inside one page
// to be sure that we fulfill them all; the -1 is for the termination entry
#define ATA_ADAPTER_MAX_SG_COUNT (B_PAGE_SIZE / sizeof( prd_entry ) - 1)


// channel node items

// number of channels (uint8)
#define ATA_ADAPTER_NUM_CHANNELS "ata_adapter/num_channels"
// io address of command block (uint16)
#define ATA_ADAPTER_COMMAND_BLOCK_BASE "ata_adapter/command_block_base"
// io address of control block (uint16)
#define ATA_ADAPTER_CONTROL_BLOCK_BASE "ata_adapter/control_block_base"
// interrupt number (uint8)
// can also be defined in host adapter node if both channels use same IRQ!
#define ATA_ADAPTER_INTNUM "ata_adapter/irq"
// id indicating primary/secondary/... channel (uint8)
#define ATA_ADAPTER_CHANNEL_ID "ata_adapter/channel_id"


// host adapter node items

// io address of bus master registers (uint16)
#define ATA_ADAPTER_BUS_MASTER_BASE "ata_adapter/bus_master_base"


// info about one channel
typedef struct ata_channel_info {
	const pci_device_interface *pci;	// mirrored from host adapter info
	pci_device device;
	
	struct ata_adapter_info* adapter;
	ata_bm_status bm_status;
	uint8 id;
	
	uint16 command_block_base;	// io address command block
	uint16 control_block_base; // io address control block
	uint16 bus_master_base;
	int intnum;				// interrupt number	
	
	uint32 lost;			// != 0 if device got removed, i.e. if it must not
							// be accessed anymore
	
	const ata_bus_for_channel_interface *ata;
	ata_bus ata_bus;
	pnp_node_handle node;
	
	int32 (*inthand)( void *arg );
	
	area_id prd_area;
	prd_entry *prdt;
	uint32 prdt_phys;
	uint32 dmaing;
} ata_channel_info;


// info about host adapter
typedef struct ata_adapter_info {
	const pci_device_interface *pci;
	pci_device device;
	
	uint16 bus_master_base;
	
	uint32 lost;			// != 0 if device got removed, i.e. if it must not
							// be accessed anymore
	
	ata_channel_info* channels[4]; // for now, no more then 4 channels are allowed
	uint8 num_channels;
	uint8 intnum;	// signals if this adapter is in native mode, i.e. has two irqs assigned iso one
	
	pnp_node_handle node;
} ata_adapter_info;


// interface of IDE adapter library.
typedef struct ata_adapter_interface {
	// function calls that can be forwarded from channel driver
	status_t (*write_command_block_regs)
		(ata_channel_info *channel, ata_task_file *tf, ata_reg_mask mask);
	status_t (*read_command_block_regs)
		(ata_channel_info *channel, ata_task_file *tf, ata_reg_mask mask);

	uint8 (*get_altstatus) (ata_channel_info *channel);
	status_t (*write_device_control) (ata_channel_info *channel, uint8 val);	

	status_t (*write_pio) (ata_channel_info *channel, uint16 *data, int count, bool force_16bit );
	status_t (*read_pio) (ata_channel_info *channel, uint16 *data, int count, bool force_16bit );

	status_t (*prepare_dma)(ata_channel_info *channel, 
							const physical_entry *sg_list, size_t sg_list_count,
	                        bool to_device );
	status_t (*start_dma)(ata_channel_info *channel);
	status_t (*finish_dma)(ata_channel_info *channel);
	
	
	// default functions that should be replaced by a more specific version
	// (copy them from source code of this library and modify them at will)
	int32 (*inthand)( void *arg );
	
	// functions that must be called by init/uninit etc. of channel driver
	status_t (*init_channel)( pnp_node_handle node, ata_bus _ata_bus, 
		ata_channel_info **cookie, size_t total_data_size,
		int32 (*inthand)( void *arg ) );
	status_t (*uninit_channel)( ata_channel_info *channel );
	void (*channel_removed)( pnp_node_handle node, ata_channel_info *channel );

	// publish channel node
	status_t (*publish_channel)( pnp_node_handle adapter_node, 
		const char *channel_module_name,
		uint16 command_block_base, uint16 control_block_base,
		uint8 intnum, bool can_dma, uint8 id, const char *name, 
		io_resource_handle *resources, pnp_node_handle *node );
	// verify channel configuration and publish node on success
	status_t (*detect_channel)( 	
		const pci_device_interface *pci, pci_device _pci_device,
		pnp_node_handle adapter_node, 
		const char *channel_module_name, bool channel_can_dma,
		uint16 command_block_base, uint16 control_block_base, uint16 bus_master_base,
		uint8 intnum, uint8 id, const char *name, pnp_node_handle *node,
		bool supports_compatibility_mode );

	// functions that must be called by init/uninit etc. of host adapter driver
	status_t (*init_adapter)( pnp_node_handle node, void *user_cookie, 
		ata_adapter_info **cookie, size_t total_data_size );
	status_t (*uninit_adapter)( ata_adapter_info *adapter );
	void (*adapter_removed)( pnp_node_handle node, ata_adapter_info *adapter );

	// publish adapter node
	status_t (*publish_adapter)( 	
		pnp_node_handle parent, 
		uint16 bus_master_base,	io_resource_handle *resources, 
		const char *adapter_driver, const char *adapter_driver_type,
		const char *adapter_name, const char *asic_name,
		bool can_dma, bool can_cq, uint32 dma_alignment, uint32 dma_boundary,
		uint32 max_sg_block_size, pnp_node_handle *node );
	// verify adapter configuration and publish node on success
	status_t (*detect_adapter)( 	
		const pci_device_interface *pci, pci_device _pci_device,
		pnp_node_handle parent,	uint16 bus_master_base,	
		const char *adapter_driver, const char *adapter_driver_type,
		const char *adapter_name, const char *asic_name,
		bool can_dma, bool can_cq, uint32 dma_alignment, uint32 dma_boundary,
		uint32 max_sg_block_size, pnp_node_handle *node );
	// standard master probe for adapter that registers adapter and channel nodes
	status_t (*probe_adapter)( pnp_node_handle parent,
		const char *adapter_driver, const char *adapter_driver_type,
		const char *adapter_name, const char *asic_name,
		const char *channel_module_name,
		bool can_dma, bool can_cq, uint32 dma_alignment, uint32 dma_boundary,
		uint32 max_sg_block_size, bool supports_compatibility_mode );
} ata_adapter_interface;

#define ATA_ADAPTER_INTERFACE "ata_adapter/v1"
#define ATA_ADAPTER_MODULE_NAME "ata/generic/ata_adapter/v1"


#endif
