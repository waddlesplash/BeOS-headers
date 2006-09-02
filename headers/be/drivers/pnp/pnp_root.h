/* 
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	PnP root module interface
	
	
	This module creates a driver root node that automatically loads standard
	bus managers (PCI and ISA). It is calles by pnp_boot_helper but should 
	probably be moved into kernel for simplification.
	
	In the future, we want to check hardware configuration before we
	start loading ISA and PCI bus manager.
*/

#ifndef PNP_ROOT_H
#define PNP_ROOT_H

#include <pnp/pnp_driver.h>


// type of pnp root device
#define PNP_ROOT_TYPE "pnp/root"
// registration directory of pnp root drivers
// (put all drivers under "universal" and use unique connection names)
#define PNP_ROOT_DRIVERS_DIR "root"

// interface of PnP root creator
typedef struct pnp_root_interface {
	// create PnP root devices
	void			(*init_root)( void );
	// destroy PnP root device
	void			(*destroy_root)( void );
	// rescan PnP root device and all children
	void			(*rescan_root)( bool rescan_busses );
} pnp_root_interface;

#define PNP_ROOT_INTERFACE "pnp/root"

#define PNP_ROOT_MODULE_NAME "pnp_core/pnp_root/v1"


#endif
