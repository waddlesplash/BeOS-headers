/*
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	PnP module loader interface

	
	Usually, you don't need to talk to the loader explicitly
	but provide a dependency list in the module header.
	
	Further, the module loader provides an old-style 
	interface to be used by old-style modules.
*/

#ifndef _PNP_MODULE_LOADER_H
#define _PNP_MODULE_LOADER_H

#include <pnp/pnp_module.h>

// interface of PnP module loader.
typedef struct pnp_module_loader_interface {
	// get interface of PnP module	
	//		name			- name of module
	//		interface_name	- name of interface
	//		*interface		- interface of module
	status_t	(*get_interface) (
					const char 			*name,
					const char			*interface_name,
					const void			**interface
				);
	// release interface of PnP module
	status_t	(*put_interface) (
					const char			*name,
					const char			*interface_name
				);

	// get PnP module	
	//		name			- name of module
	//		*module			- header of module
	// usually, you want to use get_interface()
	status_t	(*get_module) (
					const char 			*name,
					const module_header	**header
				);
	// release PnP module
	status_t	(*put_module) (
					const char			*name
				);
} pnp_module_loader_interface;

#define PNP_MODULE_LOADER_INTERFACE "module_loader/v1"
	

// module header of PnP module loader for legacy modules.
typedef struct pnp_module_loader_header {
	module_header header;

	// get interface of PnP module	
	//		name			- name of module
	//		interface_name	- name of interface
	//		*interface		- interface of module
	status_t	(*get_interface) (
					const char 			*name,
					const char			*interface_name,
					const void			**interface
				);
	// release interface of PnP module
	status_t	(*put_interface) (
					const char			*name,
					const char			*interface_name
				);

	// get PnP module	
	//		name			- name of module
	//		*module			- header of module
	// usually, you want to use get_interface()
	status_t	(*get_module) (
					const char 			*name,
					const module_header	**header
				);
	// release PnP module
	status_t	(*put_module) (
					const char			*name
				);
				
	// internal use: lock module loader
	status_t	(*lock_loader) ( void );
					
	// internal use: unlock module loader, if possible
	status_t	(*unlock_loader) ( void );
} pnp_module_loader_header;


// the module manager resides in the PnP manager right now
#define PNP_MODULE_LOADER_MODULE_NAME \
	"pnp_core/pnp_manager/module_loader/v1"


#endif
