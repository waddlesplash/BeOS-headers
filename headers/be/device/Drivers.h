/* ++++++++++
	Drivers.h
	Copyright (c) 1991-1996 by Be, Incorporated.  All Rights Reserved.
	public driver-related API
+++++ */

#ifndef _DRIVERS_H
#define _DRIVERS_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ---
	device_info: the kernel maintains one of these for each open instance of
	a device, and passes it to the driver as an argument to each call.
	
	The private_data field is for the driver's private use, and typically is
	used to stash information (or a pointer to information) for the device.
	The kernel never accesses this field.
--- */


typedef struct {
	struct device_entry	*entry;			/* -> device entry point info */
	void				*private_data;	/* private data for device */
} device_info;


/* ---
	these hooks are how the kernel accesses the device
--- */

typedef long (*device_open_hook) (device_info *info, ulong flags);
typedef long (*device_close_hook) (device_info *info);
typedef long (*device_control_hook) (device_info *info, ulong op, void *data);
typedef long (*device_io_hook) (device_info *info, void *data,
			  ulong numBytes, ulong position);

/* ---
	the device_entry is a descriptor for the device, giving its name and
	its entry points.
--- */

typedef struct device_entry {
	const char			*name;			/* name of the device, "/dev/..." */
	device_open_hook	 open;			/* called to open the device */
	device_close_hook	 close;			/* called to close the device */
	device_control_hook	 control;		/* called to control the device */
	device_io_hook		 read;			/* reads from the device */
	device_io_hook		 write;			/* writes to the device */
} device_entry;


/* ---
	The kernel looks for these global names when loading a driver:

 		"devices"				for a static array of device_entry structures
 		"publish_device_names"	returns char** list of names
		"find_device_entry"		returns the device_entry for a given name
 		"init_driver"			called when the driver is loaded

	A driver should define either
		"devices", or
		"publish_device_names" and "find_device_entry"

	"init_driver" is optional.
--- */

extern device_entry	devices[];

extern char**		publish_device_names (const char *device_name);
extern device_entry	*find_device_entry (const char *device_name);
extern long			init_driver (void);


/* ---
	Be-defined opcodes for the control call.  Drivers should support
	these only if it makes sense for that driver.

	Also defined here is the starting point for drivers to number
	their own private control call opcodes.
--- */

enum {
	B_GET_SIZE = 1,					/* get # bytes */
									/*   returns unsigned long in *data */

	B_SET_SIZE,						/* set # bytes */
									/*   passed unsigned long in data */

	B_SET_NONBLOCKING_IO,			/* set to non-blocking i/o */

	B_SET_BLOCKING_IO,				/* set to blocking i/o */

	B_GET_READ_STATUS,				/* check if can read w/o blocking */
									/*   returns unsigned long in *data */

	B_GET_WRITE_STATUS,				/* check if can write w/o blocking */
									/*   returns unsigned long in *data */

	B_GET_GEOMETRY,					/* get info about device geometry */
									/*   returns struct geometry in *data */

	B_FORMAT,						/* low-level device format */

	B_DEVICE_OP_CODES_END = 9999	/* end of Be-defined contol id's */
};


/* ---
	geometry structure for the B_GET_GEOMETRY opcode
--- */

typedef struct {
	ulong	bytes_per_sector;		/* sector size in bytes */
	ulong	sectors_per_track;		/* # sectors per track */
	ulong	cylinder_count;			/* # cylinders */
	ulong	head_count;				/* # heads */
	bool	removable;				/* non-zero if removable */
	bool	read_only;				/* non-zero if read only */
	bool	write_once;				/* non-zero if write-once */
} device_geometry;


#ifdef __cplusplus
}
#endif

#endif /* _DRIVERS_H */
