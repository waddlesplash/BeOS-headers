/*
	Copyright (c) 2003-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.


	PnP manager; Takes care of registration and loading of PnP drivers
	
	Read pnp_driver.h first to understand the basic idea behind PnP drivers.
	
	To register a driver node, use register_driver. If the device got lost, 
	use unregister_driver (note: if the parent node is removed, your node 
	get removed automatically as your driver has obviously nothing to work 
	with anymore). To get access to a (parent) device, use load_driver/
	unload_driver.
	
	To let the manager find a consumer (see pnp_driver.h), you can either
	specify its name directly during registration, using a 
	PNP_DRIVER_FIXED_CONSUMER attribute, or let the manager search the 
	appropriate consumer(s) via a PNP_DRIVER_DYNAMIC_CONSUMER attribute. 
	
	Searching of dynamic consumers is done as follows:
	
	- First, the manager searches for a Specific driver in the base 
	  directory (see below)
	- If no Specific driver is found, all Generic drivers stored under
	  "generic" sub-directory are informed in turn until one returns success
	- Finally, _all_ Universal drivers, stored in the "universal" sub-
	  directory, are informed

	Specification of the base directory and of the names of Specific 
	drivers is done via a file name pattern given by a 
	PNP_DRIVER_DYNAMIC_CONSUMER attribute. 
	
	First, all substrings of the form "%attribute_name%" are replaced by the 
	content of the attribute "attribute_name" as follows:
	
	- if the attribute contains an integer value, its content is converted to hex 
	  (lowercase) with a fixed length according to the attribute's value range
	- the content of string attributes is quoted by " and invalid characters 
	  (i.e. /%" and all characters outside 32..126) are replaced by their
	  unsigned decimal value, delimited by %
	- other attribute types cannot be used
	
	Second, the resulting name is split into chunks according to the presence 
	of | characters (you can escape % and | with a ^ character). These
	characters are only delimiters and get removed before further processing.
	The directory before the first | character is the base directory (see 
	above). It contains the "generic" and the "universal" subdirectories. 
	The names of the specific drivers are created by first taking the entire
	file name, then by removing the last chunk, then by removing the last
	two chunks and so on until only the first chunk is left. 

	As add-ons can contain multiple modules, the module name of a dynamic
	consumer is constructed by appending the content of the PNP_DRIVER_TYPE 
	attribute to the driver's file name, seperated by a slash character;
	the module name of fixed consumers is specified directly via 
	PNP_DRIVER_FIXED_CONSUMER.
	
	E.g. given a dynamic consumer pattern of 
	"pci/vendor=%vendor_id%|, device=%device_id%" for a device with the 
	attributes vendor_id=0x123 and device_id=0xabcd (both being uint16), the
	PnP manager tries the specific drivers "pci/vendor=0123, device=abcd" and
	(if the first one fails/doesn't exist) "pci/vendor=0123". If they both
	refuse to handle the device, all drivers under "pci/generic" are tried
	until one accepts the device. Finally, all drivers under "pci/universal" 
	are	loaded, whatever happened before.

	In practise, you should try to use specific drivers as much as possible.
	If detection based on device IDs is impossible (e.g. because the bus 
	doesn't support them at all), you can put the driver under "generic".
	Generic drivers can also be used to specify wrappers that try to load old-
	style drivers if no new driver can be found. Also, they can be used to
	report an error or invoke an user program that tries downloading a
	proper Specific driver. Universal drivers are mainly used for 
	informational purposes, e.g. to publish data about each found device,
	or to provide raw access to all devices.
	
	If the device uses physical address space or I/O space or ISA DMA 
	channels (called I/O resources), the driver has to acquire these 
	resources. During hardware detection (usually via probe()), 
	acquire_io_resources() must be called to get exclusive access.
	If no hardware could be found, they must be released via 
	release_io_resources(). If detection was successful, the list of 
	the (acquired) resources must be passed to register_device().
	Resources can either belong to one hardware detection or to a device.
	If a hardware detection collides with another, it has to wait; 
	if it collides with a device whose driver is not loaded, the
	driver loading is blocked. When detection fails, i.e. if 
	release_io_resources() is called, all blocked drivers can be loaded
	again. If the detection fails, i.e. the resources are transferred
	via register_device(), all blocked devices are unregistered and
	pending load requests aborted. If a hardware detection collides
	with a device whose driver is loaded, acquire_io_resources() fails
	with B_BUSY. As this makes a hardware rescan impossible if the 
	driver is loaded, you should define	PNP_DRIVER_NO_LIVE_RESCAN 
	for nodes that use I/O resources (see below).
	
	To search for new drivers for a given device node, use rescan(). This
	marks all consumer devices as being verified and calls probe() 
	of all consumers drivers (see above) to let them rescan the parent 
	for devices. The <depth> parameter determines the nesting level, e.g.
	2 means that first the consumers are scanned and then the consumers
	of the consumers.
	
	Normally, all devices can be rescanned. If a driver cannot handle
	a rescan safely when it is loaded (i.e. used by a consumer), it
	must set PNP_DRIVER_NO_LIVE_RESCAN, in which case the device is
	ignored during rescan if the driver is loaded and attempts
	to load the driver during a rescan are blocked until the rescan
	is finished. If rescanning a device is not possible at all, it must
	have set PNP_DRIVER_NEVER_RESCAN to always ignore it.
	
	To distinguish between new devices, lost devices and redetected
	devices, consumer devices should provide a connection code and a
	device identifier. They are specified by PNP_DRIVER_CONNECTION and
	PNP_DRIVER_CONNECTION respectively, and are expanded in the same way
	as PNP_DRIVER_DYNAMIC_CONSUMER. It is assumed that there can be only
	one device per connection and that a device can be uniquely identify
	by a device identifier. If a consumer device is registered on the 
	same connection as an existing device but with a different device 
	identifier, the old device gets unregistered automatically. If both 
	connection and device identifier are the same, registration is 
	handled as a redetection and ignored (unless a different type or 
	driver module is specified - in this case, the device is replaced). 
	Devices that were not redetected during a rescan get unregistered
	unless they were ignored (see above).
*/

#ifndef _PNP_MANAGER_H
#define _PNP_MANAGER_H

#include <module.h>
#include <pnp/pnp_driver.h>


// type of I/O resource
enum {
	IO_MEM = 1,
	IO_PORT = 2,
	ISA_DMA_CHANNEL = 3
};


// I/O resource description
typedef struct {
	// type of I/O resource
	uint type;

	// I/O memory: first physical address (32 bit)
	// I/O port: first port address (16 bit)
	// ISA DMA channel: channel number (0-7)
	uint32 base;
	// I/O memory: size of address range (32 bit)
	// I/O port: size of port range (16 bit)
	// ISA DMA channel: must be 1
	uint32 len;
} io_resource;


// handle of acquired I/O resource
typedef struct io_resource_info *io_resource_handle;

// handle of node attribute
typedef struct pnp_node_attr_info *pnp_node_attr_handle;


// interface of PnP manager for driver.
typedef struct pnp_manager_interface {
	// load driver of parent device.
	//		node			- node, whose parents driver is to be loaded
	//		interface_name	- whished interface of parent node's driver
	//		manager_cookie	- cookie of <node>'s driver
	//		*interface		- interface of parent node's driver as requested
	//		*cookie			- cookie of parent node's driver
	// <manager_cookie> is only passed if <node> is the managing consumer;
	// loading/unloading can be nested - only first load/ last unload
	// is actually executed
	status_t	(*load_parent) (
					pnp_node_handle		node,
					const char			*interface_name,
					void				*manager_cookie,
					const void			**interface,
					void				**cookie
				);
	// unload driver of parent device.
	//		node			- node, whose parents driver is to be unloaded
	status_t	(*unload_parent) (
					pnp_node_handle		node,
					const char			*interface_name
				);

	// get interface of manager.
	//		node			- node of managed device (_not_ manager node)
	// must only be called by drivers of managed devices
	status_t	(*get_manager_interface)(
					pnp_node_handle		node,
					const char			*interface_name,
					const void			**manager_interface
				);
	// put interface of manager.
	status_t	(*put_manager_interface)(
					pnp_node_handle		node,
					const char			*interface_name
				);
				
	// load driver.
	// 		node 	- node whose driver is to be loaded
	// 		cookie	- device cookie issued by loaded driver
	// usually, you really want load_parent(); managers must not
	// use this function as this leaves no way to distinguish between
	// "loaded by manager" and "loaded by someone else"
	status_t	(*load_driver) (
					pnp_node_handle		node,
					const char			*interface_name,
					const void			**interface,
					void				**cookie
				);
	// unload driver.
	// usually, you really want unload_parent()
	status_t	(*unload_driver) (
					pnp_node_handle		node,
					const char			*interface_name
				);
				
	// rescan node for new dynamic drivers.
	// 		node 			- node whose consumers are to be re-searched
	// 		depth 			- recursive depth (>= 1)
	//		rescan_busses	- if true, rescan busses too
	// if rescan_busses is false, busses are ignored as rescanning them is
	// often time-consuming and is only necessary if they have no 
	// hotplug detection
	status_t 	(*rescan) (
					pnp_node_handle 	node, 
					int					depth,
					bool				rescan_busses
				);
	
	// register device.
	// 		parent 			- parent node
	// 		attributes 		- NULL-terminated array of node attributes
	// 		io_resources 	- NULL-terminated array of I/O resources (can be NULL)
	// 		*node 			- new node handle (can be NULL)
	// on return, io_resources are _always_ invalid: on success I/O 
	// resources belong to node, on fail they are released;
	// if device is already registered, B_OK is returned but *node is NULL;
	// if node!=NULL, you must release the node via release_node() when you
	// don't need it anymore
	status_t	(*register_device) (
					pnp_node_handle		parent,
					const pnp_node_attr	*attrs,
					const io_resource_handle *io_resources,
					pnp_node_handle		*node
				);
	// unregister device.
	// consumers are recursively unregistered.
	// if a node contains PNP_MANAGER_ID_GENERATOR/PNP_MANAGER_AUTO_ID
	// pairs, the id specified this way is freed too
	status_t	(*unregister_device) (
					pnp_node_handle		node
				);
				
	// acquire I/O resources.
	// 		resources 	- NULL-terminated array of resources to acquire
	//		priority	- priority of driver (ask bus manager for proper value)
	// 		handles 	- NULL-terminated array of handles (one per resource); 
	//           		  array must be provided by caller
	// returns B_BUSY if a resource is used by a loaded driver:
	// used during probing; if device is found, <handles> should be forwarded
	// to register_device(); if device is not found, <handles> should be freed
	// via release_io_resources()
	status_t	(*acquire_io_resources) (
					const io_resource	*resources,
					int					priority,
					io_resource_handle	*handles
				);
	// release I/O resources.
	// 		handles 	- NULL-terminated array of resource handles
	// only to be called if hardware detection fails, not if register_device fails
	// (see register_device())
	status_t	(*release_io_resources) (
					const io_resource_handle *handles
				);

	// acquire node.
	// if you want store a node somewhere, you must acquire it to make
	// sure it won't get destroyed. when you don't need the node anymore,
	// call release_node() for it. acquiring a node implicitily acquires
	// all direct and indirect parent nodes.
	// (a loaded driver doesn't need to explicitly acquire its node as this is
	// done/undone implicitly during load/unload)
	void		(*acquire_node) (
					pnp_node_handle		node
				);
	// release node returned by find_device() or acquire_node().
	void 		(*release_node) (
					pnp_node_handle		node
				);
	// get parent device of node.
	// you must _not_ release the node via release_node
	pnp_node_handle (*get_parent)(
					pnp_node_handle		node 
				);				
	// find device by node content.
	// the given attributes must identify a device node;
	// 		parent 		- parent node (-1 for don't-care)
	//		previous	- node to start from (excluding <previous>)
	// 		attrs 		- NULL-terminated list of attributes (can be NULL)
	// return: NULL if no device device found.
	// the returned node must either be released via release_node() or
	// be used to find next device by feeding it as <previous>
	pnp_node_handle (*find_device) ( 
					pnp_node_handle		parent,
					pnp_node_handle		previous,
					const pnp_node_attr	*attrs 
				);
				
	// helpers to extract attribute by name.
	// if <recursive> is true, parent nodes are scanned if 
	// attribute isn't found in current node; unless you've declared
	// the attribute yourself, use recursive search to handle
	// intermittent nodes, e.g. defined by filter drivers, transparently.
	// for raw and string attributes, you get a copy that must 
	// be freed by caller 
	status_t	(*get_attr_uint8)(
					pnp_node_handle		node,
					const char			*name,
					uint8				*value,
					bool				recursive
				);
	status_t	(*get_attr_uint16)(
					pnp_node_handle		node,
					const char			*name,
					uint16				*value,
					bool				recursive
				);
	status_t	(*get_attr_uint32)(
					pnp_node_handle		node,
					const char			*name,
					uint32				*value,
					bool				recursive
				);
	status_t	(*get_attr_uint64)(
					pnp_node_handle		node,
					const char			*name,
					uint64				*value,
					bool				recursive
				);
	status_t	(*get_attr_string)(
					pnp_node_handle		node,
					const char			*name,
					char				**value,
					bool				recursive
				);
	status_t	(*get_attr_raw)(
					pnp_node_handle		node,
					const char			*name,
					void				**data,
					size_t				*len,
					bool				recursive
				);

	// get next attribute of node.
	// on call, *<attr_handle> must contain handle of an attribute;
	// on return, *<attr_handle> is replaced by the next attribute or
	// NULL if it was the last;
	// to get the first attribute, <attr_handle> must point to NULL;
	// the returned handle must be released by either passing it to
	// another get_next_attr() call or by using release_attr()
	// directly
	status_t	(*get_next_attr)(
					pnp_node_handle		node,
					pnp_node_attr_handle *attr_handle
				);
				
	// release attribute handle <attr_handle> of <node>.
	// see get_next_attr
	status_t	(*release_attr)(
					pnp_node_handle		node,
					pnp_node_attr_handle attr_handle
				);
				
	// retrieve attribute data with handle given.
	// <attr> is only valid as long as you don't release <attr_handle> 
	// implicitely or explicitely
	status_t	(*retrieve_attr)(
					pnp_node_attr_handle attr_handle,
					const pnp_node_attr	**attr
				);
			
	// change/add attribute <attr> of/to node.
	// warning: most standard attributes cannot be altered
	status_t	(*write_attr)(
					pnp_node_handle		node,
					const pnp_node_attr	*attr
				);
				
	// remove attribute of node by name
	// 		name	- is name of attribute
	status_t	(*remove_attr)(
					pnp_node_handle		node,
					const char 			*name
				);

	// create unique id.
	// 		generator 	- name of id set
	// if result >= 0 - unique id
	//    result < 0 - error code
	// if the returned id is used as a node attribute, it can be freed
	// automatically via PNP_MANAGER_ID_GENERATOR when node is deleted
	int32		(*create_id)( 
					const char 			*generator
				);
	// free unique id.
	status_t	(*free_id)(
					const char			*generator,
					uint32				id
				);
} pnp_manager_interface;

#define PNP_MANAGER_INTERFACE "pnp_manager"


// standard attributes:

// if you are using an id generator (see create_id), you can let the 
// manager automatically free the id when the node is deleted by setting 
// the following attributes:
// name of generator (string)
#define PNP_MANAGER_ID_GENERATOR "id_generator"
// generated id (uint32)
#define PNP_MANAGER_AUTO_ID "auto_id"
	
// module name of PnP manager
#define PNP_MANAGER_MODULE_NAME "pnp_core/pnp_manager/v1"


#endif
