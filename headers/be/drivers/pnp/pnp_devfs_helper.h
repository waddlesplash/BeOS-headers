/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	Part of PnP devfs
	
	
	Interface of PnP devfs for helper device driver.
	The location is not perfect, we should create some internal include 
	directory for files likes this.
*/

#ifndef PNP_DEVFS_HELPER_H
#define PNP_DEVFS_HELPER_H

#include <module.h>
#include <pnp/pnp_devfs.h>


// name of helper device
// (needed by pnp_devfs to tell devfs to update its devices list)
#define PNP_DEVFS_HELPER_NAME "pnp_devfs_helper"


// interface for helper driver.
// function calls are simply passed through
typedef struct pnp_devfs_helper_interface {
	const char**	(*publish_devices) ();
	device_hooks*	(*find_device) (const char* name);
} pnp_devfs_helper_interface;

#define PNP_DEVFS_HELPER_INTERFACE "devfs/helper"

#endif
