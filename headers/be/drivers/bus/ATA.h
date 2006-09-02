/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.
	
	Part of ATA bus manager
	

	ATA bus manager interface.
	
	Every ATA host adapter consists of one or channels (like primary and
	secondary channel). For every channel, a managed node must be registered.
	As a fixed consumer, the ATA bus manager must be specified, and the
	Manager Interface must be ATA_BUS_CHANNEL_INTERFACE. 
*/

#ifndef _ATA_H
#define _ATA_H

#include <bus_manager.h>
#include <iovec.h>
#include <lendian_bitfield.h>
#include <pnp/pnp_driver.h>
#include "r5_wrapper.h"
#include <KernelExport.h>

// ATA task file.
// contains the command block interpreted under different conditions with
// first byte being first command register, second byte second command register
// etc.; for lba48, registers must be written twice, therefore there
// are twice as many bytes as registers - the first eight bytes are those
// that must be written first, the second eight bytes are those that
// must be written second.
typedef union {
	struct {
		uint8	features;
		uint8	sector_count;
		uint8	sector_number;
		uint8	cylinder_0_7;
		uint8	cylinder_8_15;
		LBITFIELD8_3(
			head				: 4,
			device				: 1,
			mode				: 3
		);
		uint8	command;
	} chs;
	struct {
		uint8	features;
		uint8	sector_count;
		uint8	lba_0_7;
		uint8	lba_8_15;
		uint8	lba_16_23;
		LBITFIELD8_3(
			lba_24_27			: 4,
			device				: 1,
			mode				: 3
		);
		uint8	command;
	} lba;
	struct {
		LBITFIELD8_3(
			dma					: 1,
			ovl					: 1,
			_0_res2				: 6
		);
		LBITFIELD8_2(
			_1_res0				: 3,
			tag					: 5
		);
		uint8	_2_res;
		uint8	byte_count_0_7;
		uint8	byte_count_8_15;
		LBITFIELD8_6(
			lun					: 3,
			_5_res3				: 1,
			device				: 1,
			_5_one5				: 1,
			_5_res6				: 1,
			_5_one7				: 1
		);
		uint8	command;
	} packet;
	struct {
		LBITFIELD8_5(
			ili					: 1,
			eom					: 1,
			abrt				: 1,
			_0_res3				: 1,
			sense_key			: 4
		);
		LBITFIELD8_4(
			cmd_or_data			: 1,	// 1 - cmd, 0 - data
			input_or_output	 	: 1,	// 0 - input (to device), 1 - output
			release				: 1,
			tag					: 5
		);
		uint8	_2_res;
		uint8	byte_count_0_7;
		uint8	byte_count_8_15;
		LBITFIELD8_5(
			_4_res0				: 4,
			device				: 1,
			_4_obs5				: 1,
			_4_res6				: 1,
			_4_obs7				: 1
		);
		LBITFIELD8_7(
			chk					: 1,
			_7_res1 				: 2,
			drq					: 1,
			serv				: 1,
			dmrd				: 1,
			drdy				: 1,
			bsy					: 1
		);
	} packet_res;
	struct {
		uint8	sector_count;
		LBITFIELD8_4(					// only <tag> is defined for write
			cmd_or_data			: 1,	// 1 - cmd, 0 - data
			input_or_output		: 1,	// 0 - input (to device), 1 - output
			release				: 1,
			tag					: 5
		);
		uint8	lba_0_7;
		uint8	lba_8_15;
		uint8	lba_16_23;
		LBITFIELD8_3(
			lba_24_27			: 4,
			device				: 1,
			mode				: 3
		);
		uint8	command;
	} queued;
	struct {
		// low order bytes
		uint8	features;
		uint8	sector_count_0_7;
		uint8	lba_0_7;
		uint8	lba_8_15;
		uint8	lba_16_23;
		LBITFIELD8_3(
			_5low_res0			: 4,
			device				: 1,
			mode				: 3
		);
		uint8	command;
		
		// high order bytes
		uint8	_0high_res;
		uint8	sector_count_8_15;
		uint8	lba_24_31;
		uint8	lba_32_39;
		uint8	lba_40_47;
	} lba48;
	struct {
		// low order bytes
		uint8	sector_count_0_7;
		LBITFIELD8_4(
			cmd_or_data			: 1,	// 1 - cmd, 0 - data
			input_or_output	 	: 1,	// 0 - input (to device), 1 - output
			release				: 1,
			tag					: 5
		);
		uint8	lba_0_7;
		uint8	lba_8_15;
		uint8	lba_16_23;
		LBITFIELD8_3(
			_5low_res0				: 4,
			device					: 1,
			mode					: 3
		);
		uint8	command;
		
		// high order bytes
		uint8	sector_count_8_15;
		uint8	_1high_res;
		uint8	lba_24_31;
		uint8	lba_32_39;
		uint8	lba_40_47;
	} queued48;
	struct {
		uint8	_0_res[3];
		uint8	ver;			// RMSN version
		LBITFIELD8_3(
			pena	: 1,		// previously enabled
			lock	: 1,		// capable of locking
			pej		: 1			// can physically eject
		);
	} set_MSN_res;
	struct {
		uint8	r[7+5];
	} raw;
	struct {
		uint8	features;
		uint8	sector_count;
		uint8	sector_number;
		uint8	cylinder_low;
		uint8	cylinder_high;
		uint8	device_head;
		uint8	command;
	} write;
	struct {
		uint8	error;
		uint8	sector_count;
		uint8	sector_number;
		uint8	cylinder_low;
		uint8	cylinder_high;
		uint8	device_head;
		uint8	status;
	} read;
} ata_task_file;

// content of "mode" field
enum {
	ata_mode_chs = 5,
	ata_mode_lba = 7
};

// mask for ata_task_file fields to be written
typedef enum {
	ata_mask_features	 		= 0x01,
	ata_mask_sector_count		= 0x02,

	// CHS
	ata_mask_sector_number		= 0x04,
	ata_mask_cylinder_low		= 0x08,
	ata_mask_cylinder_high		= 0x10,
	
	// LBA
	ata_mask_LBA_low			= 0x04,
	ata_mask_LBA_mid			= 0x08,
	ata_mask_LBA_high			= 0x10,

	// packet
	ata_mask_byte_count			= 0x18,
	
	// packet and dma queued result
	ata_mask_error				= 0x01,
	ata_mask_ireason			= 0x02,

	ata_mask_device_head		= 0x20,
	ata_mask_command			= 0x40,
	
	ata_mask_status				= 0x40,

	// for 48 bits, the following flags tell which registers to load twice
	ata_mask_features_48		= 0x80 | ata_mask_features,
	ata_mask_sector_count_48	= 0x100 | ata_mask_sector_count,
	ata_mask_LBA_low_48			= 0x200 | ata_mask_LBA_low,
	ata_mask_LBA_mid_48			= 0x400 | ata_mask_LBA_mid,
	ata_mask_LBA_high_48		= 0x800 | ata_mask_LBA_high,
	
	ata_mask_HOB				= 0xf80

	//ata_mask_all			= 0x7f
} ata_reg_mask;

// status register
enum {
	ata_status_err		= 0x01,		// error
	ata_status_index	= 0x02,		// obsolete
	ata_status_corr		= 0x04,		// obsolete
	ata_status_drq		= 0x08,		// data request
	ata_status_dsc		= 0x10,		// reserved
	ata_status_service	= 0x10,		// ready to service device
	ata_status_dwf		= 0x20,		// reserved
	ata_status_dma		= 0x20,		// reserved
	ata_status_dmrd		= 0x20,		// packet: DMA ready
	ata_status_df		= 0x20,		// packet: disk failure
	ata_status_drdy		= 0x40,		// device ready
	ata_status_bsy		= 0x80		// busy
} ata_status_mask;

// device control register
enum {
									// bit 0 must be zero
	ata_devctrl_nien	= 0x02,		// disable INTRQ
	ata_devctrl_srst	= 0x04,		// software device reset
	ata_devctrl_bit3	= 0x08,		// don't know, but must be set
									// bits inbetween are reserved
	ata_devctrl_hob		= 0x80		// read high order byte (for 48-bit lba)
} ata_devcntrl_mask;

// error register - most bits are command specific
enum {
	// always used
	ata_error_abrt		= 0x04,		// command aborted
	
	// used for Ultra DMA modes
	ata_error_icrc		= 0x80,		// interface CRC error

	// used by reading data transfers
	ata_error_unc		= 0x40,		// uncorrectable data error
	// used by writing data transfers
	ata_error_wp		= 0x40,		// media write protect

	// used by all data transfer commands
	ata_error_mc		= 0x20,		// medium changed
	ata_error_idnf		= 0x10,		// CHS translation not init./ invalid CHS address
	ata_error_mcr		= 0x08,		// media change requested
	ata_error_nm		= 0x02,		// no media (for removable media devices)
} ata_error_mask;



// ATA bus node


// channel cookie, issued by ata bus manager
typedef struct ata_bus_info *ata_bus;

// interface for channel drivers.
// must be specified as Manager Interface for ATA channel nodes
typedef struct ata_bus_for_channel_interface {
	// IRQ was raised.
	// 		status	- status read from host adapter (_not_ alt_status, as 
	//				  reading normal status acknowledges IRQ request of device)
	// must be called directly from IRQ handler; handling of interrupt 
	// sharing is up to the channel driver
	status_t	(*irq_handler)( 
		ata_bus 		bus, 
		uint8 			status 
	);
} ata_bus_for_channel_interface;

#define ATA_BUS_FOR_CHANNEL_INTERFACE "ata/bus/for_channel/v1"

// name of ATA bus manager.
// must be specified as fixed consumer of ATA channel nodes
#define ATA_BUS_MANAGER_MODULE_NAME "ata/ata_bus_manager/bus/v1"



// ATA channel node


// attributes:

// node type
#define ATA_CHANNEL_TYPE "ata/channel"
// maximum number of devices connected to host adapter (uint8, optional, default:2)
#define ATA_CHANNEL_MAX_DEVICES_ITEM "ata/max_devices"
// set to not-0 if DMA is supported (uint8, optional, default:0)
// (if so, publish necessary blkdev restriction too)
#define ATA_CHANNEL_CAN_DMA_ITEM "ata/can_DMA"
// set to not-0 if CQ is supported (uint8, optional, default:1)
#define ATA_CHANNEL_CAN_CQ_ITEM "ata/can_CQ"

// channel cookie to be defined by host adapter driver
typedef struct ata_channel_info *ata_channel_cookie;


// interface of channel drivers.
// used by ATA bus manager
typedef struct ata_channel_interface {
	// write task file.
	//		tf		- task file, i.e. command block registers
	//		mask	- bitmask which command registers are to be written
	status_t	(*write_command_block_regs)(
					ata_channel_cookie	channel, 
					ata_task_file		*tf, 
					ata_reg_mask		mask
				);
	// read task file.
	// see write_command_block_regs()
	status_t 	(*read_command_block_regs)(
					ata_channel_cookie	channel, 
					ata_task_file		*tf, 
					ata_reg_mask 		mask
				);
	// read alternate status.
	// 		return	- content of alternate status register
	uint8		(*get_altstatus)(
					ata_channel_cookie channel
				);
	// write device control register.
	//		val		- new content of device control register
	status_t	(*write_device_control)(
					ata_channel_cookie	channel, 
					uint8 				val
				);

	// write data in PIO mode.
	//		data		- pointer to data
	//		count		- number of words (i.e. 16 bit values) to write
	//		force_16bit	- if true, don't write 32 bits at once
	status_t	(*write_pio)(
					ata_channel_cookie	channel, 
					uint16 *			data, 
					int					count, 
					bool				force_16bit 
				);
	// read data in PIO mode.
	// see write_pio()
	status_t	(*read_pio)(
					ata_channel_cookie	channel, 
					uint16				*data,
					int					count,
					bool				force_16bit 
				);

	// prepare DMA transmission.
	//		sg_list			- scatter/gather list, containing physical addresses
	//		sg_list_count	- number of S/G entries
	//		write			- if true, DMA transmission writes data to device
	status_t	(*prepare_dma)(
					ata_channel_cookie	channel, 
					const physical_entry *sg_list, 
					size_t				sg_list_count,
					bool				write
				);
	// start DMA transmission.
	status_t	(*start_dma)(
					ata_channel_cookie channel
				);
	// finish DMA transmission.
	// the channel driver must verify that transmission was successful and
	// return proper error codes
	status_t	(*finish_dma)(
					ata_channel_cookie channel
				);
} ata_channel_interface;

#define ATA_CHANNEL_INTERFACE	"ata/channel/v1"


#endif
