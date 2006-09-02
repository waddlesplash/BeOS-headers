/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	PnP devfs driver interface.
	
	
	To publish an /dev entry for a node, define PNP_DEVFS_MODULE_NAME
	as a fixed consumer, publish an interface of type devfs_interface
	and specify the name of the /dev entry via PNP_DEVFS_FILENAME.
	
	Hooks are similar to the original devfs interface, but the open
	hook gets the driver cookie (as returned by init_device() of the
	driver) instead of a filename.
*/

#ifndef _PNP_DEVFS_H
#define _PNP_DEVFS_H

#include <Drivers.h>
#include <drivers/pnp/pnp_driver.h>
#include "r5_wrapper.h"

// changed open hook - gets cookie returned by init_device instead of name
typedef status_t (*pnp_device_open_hook)( void *device_cookie, uint32 flags, 
	void **handle_cookie );
	

	
// Device node publishing an /dev entry


// Attributes:

// name under which the device should be published under /dev (required, string)
#define PNP_DEVFS_FILENAME		"devfs/filename"


#undef free

// interface to be provided by driver
typedef struct devfs_interface {
	pnp_device_open_hook	open;			// called to open the device
	device_close_hook		close;			// called to close the device
	device_free_hook		free;			// called to free the cookie
	device_control_hook		control;		// called to control the device
	device_read_hook		read;			// reads from the device
	device_write_hook		write;			// writes to the device
	device_select_hook		select;			// start select (can be NULL)
	device_deselect_hook	deselect;		// stop select (can be NULL)
	device_readv_hook		readv;			// scatter-gather read from the device (can be NULL)
	device_writev_hook		writev;			// scatter-gather write to the device (can be NULL)
} devfs_interface;

#define free stdfree

#define DEVFS_INTERFACE "devfs/v1"


// fixed consumer to be specified by nodes providing /dev entry
#define PNP_DEVFS_MODULE_NAME	"pnp_core/pnp_devfs"

#endif
