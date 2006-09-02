/*
	Copyright (c) 2003-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	Pnp driver file and registration file attributes
	
	
	All drivers must contain resources that describe them.
	Some of them are per-driver, some are per-device. The
	following file defines the names of the resources.
	
	There is an installer that extracts this information and 
	stores it in registration files. Theoretically, this
	data could be stored in attributes as well, but as long
	as no arrays of attributes are supported, this is not possible.
*/

#ifndef _PNP_FILE_ATTR_H
#define _PNP_FILE_ATTR_H


// per-driver information

// Installation directory (required, string)
// Directory where this driver must be located
#define DRIVER_INSTALL_DIR "DREG:install_dir"
// Boot flag (optional, uint8)
// if != 0, this driver is necessary to boot the system
#define DRIVER_BOOT_FLAGS "DREG:boot_flags"

// Name of legacy driver name (optional, string)
// Legacy drivers are R5 drivers that collide with this driver
// and thus must be removed during driver installation;
// there can be multiple entries with this name
#define DRIVER_LEGACY_DRIVER_NAME "DREG:legacy_driver"
// Registration directory to create (optional, string)
// If this driver needs a registration directory for its
// consumers, the name of the directory must be specified here;
// normal drivers don't need this entry
#define DRIVER_REGISTRATION_DIR "DREG:registration_dir"



// per-device information

// registration name (required, string)
#define DRIVER_REG_NAME "DREG:name"
// module name of driver (required, string)
// without "../kernel/pnp" prefix
#define DRIVER_REG_MODULE_NAME "DREG:driver"
// human-readable device name (optional, string)
#define DRIVER_REG_DEVICE_NAME "DREG:hr_device"
// name of ASIC (optional, string)
#define DRIVER_REG_ASIC "DREG:asic"
// further parameters (optional, string)
#define DRIVER_REG_PARAMS "DREG:params"


// MIME-types

// MIME-type of driver registration file
#define DRIVER_REG_MIME "application/x-vnd.driver_reg"
// MIME-type of driver file.
// currently not working as the Tracker resets the type of
// all ELF-files to a standard type
#define DRIVER_MIME "application/x-vnd.driver"


#endif
