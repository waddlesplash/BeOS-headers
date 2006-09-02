/*
	Copyright (c) 2002-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	PnP modules

	
	The new module system distinguishes between modules and interfaces:
	the module_info structure is fixed and instead all functions provided 
	by a module they are grouped into named interfaces. The module
	header contains a pointer to the array of published interfaces,
	terminated by an empty entry. 
	
	Further, dependencies between modules can be defined directly:
	the module header contains a pointer to an array of depedencies
	which consist of the target module name, the interface name
	and a pointer where the interface is to be stored.
	
	There are two standard interfaces handled by the module loader:
	
	1. module_basic_interface
	
	Contains an init and and uninit function that are called when
	all dependencies are resolved, i.e. init after the interfaces
	are retrieved, uninit before the interfaces are released. If you
	need to initialize something before the depedencies are resolved
	(e.g. to avoid cross dependencies), you can still use std_ops
	but this should normally not be necessary.
	
	2. module_proxy_interface
	
	Interfaces can be defined dynamically. Before the list of
	published interfaces is walked by the module loader, 
	get_interface() of the proxy interface is called. If
	this function doesn't return an interface, the normal
	interface list is searched for it. If noone uses an
	interface created by get_interface() anymore, release_interface() 
	is called which normally consists of a simply free() call.
	Obviously, you cannot define a dynamic proxy interface.

	
	Restrictions:
	PnP modules must not be loaded via standard get_module/put_module
	calls, but via the PnP module loader. Further, dependant modules
	must have a pnp_module_info interface as the loader cannot
	distinguish between normal modules and PnP modules. So, if
	you need a non-PnP module, you must use the good old get_module()/
	put_module() functions. Note that the module_basic_interface interface 
	is optional but std_ops must be defined even if you don't need it 
	(this is a restriction of the R5 kernel module loader).
	
	Future:
	This loader should be moved into the kernel and all modules
	should be of this new type (we could also use different export
	names for the modules list, like "pnp_module" instead of 
	"module" to mix old and new modules). Further, std_ops should
	be allowed to be NULL or even moved to a new interface as most 
	modules don't need it and provide an empty function to make the 
	loader happy.
*/

#ifndef _PNP_MODULE_H
#define _PNP_MODULE_H

#include <module.h>
#include "r5_wrapper.h"


// interface descriptor.
typedef struct module_interface_desc {
	// name of interface
	const char 	*name;
	// pointer to interface
	const void	*interface;
} module_interface_desc;


// module dependency.
typedef struct module_dependency {
	// module name
	const char 		*name;
	// interface name (can be NULL to retrieve module header)
	const char		*interface_name;
	// reference to interface pointer / module header pointer
	const void		**interface;
} module_dependency;


// public info structure of PnP module.
// NULL-terminated pointer list must be exported as "modules" by add-on
typedef struct module_header {
	module_info						minfo;
	// header version (see below)
	uint32							version;
	// list of module dependencies (optional)
	// all modules in this list are automatically loaded and a 
	// pointer to the specified interface stored in *interface;
	// end of list is declared by name=NULL
	const struct module_dependency *dependencies;
	// list of interface descriptors
	// last entry must have "name=NULL"
	const struct module_interface_desc *interfaces;
} module_header;

// current header version
#define CUR_MODULE_HEADER_VERSION 1


// standard interface of a module (optional)
typedef struct module_basic_interface {
	// called after this and all dependant modules are loaded (optional)
	status_t	(*post_init)( void );
	// called before unloading this and dependant modules (optional)
	status_t	(*pre_uninit)( void );
} module_basic_interface;

#define MODULE_BASIC_INTERFACE "module/basic/v1"


// module interface proxy (optional)
// if a modules has a non-static interface, it must publish this
// proxy. the module loader always asks the proxy for an interface first.
// exception: the loader doesn't ask the proxy for the proxy interface
typedef struct module_proxy_interface {
	// get interface of given name.
	//		interface_name	- name of interface
	//		*interface		- pointer to interface
	status_t	(*get_interface)( 
					const char	*interface_name,
					void		**interface
		);
	// free interface of given name.
	// free memory occupied by specified interface
	void		(*free_interface)(
					const char	*interface_name,
					void		*interface
				);
} module_proxy_interface;

#define MODULE_INTERFACE_PROXY "module/interface_proxy/v1"


#endif
