/*
	Copyright (c) 2003-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.

	PnP drivers interfaces


	Every device is described by a PnP node with PnP Node Attributes
	associated to it. Devices are organized in a hierarchy, e.g. a devfs 
	device is a hard disk device that is connected to a controller, which 
	is a PCI device, that is connected to a PCI bus. Every device is 
	connected to its lower-level device	via a parent link stored in its 
	node. The higher-level is called the consumer of the lower-level device. 
	If the lower-level device gets removed, all its consumers are removed too. 
	
	In our example, the hierarchy is
	
	  devfs device -> hard disk -> controller -> PCI device -> PCI bus
	  
	If the PCI bus is removed, everything up to including the devfs device
	is removed too.
	
	The driver hierarchy is constructed bottom-up, i.e. the lower-level
	driver defines possible consumers via the attributes of the node it
	registers. Registration of devices and the search for appropriate consumers 
	is done via the pnp_manager (see pnp_manager.h).

	When a potential consumer is found, it gets informed via its probe interface
	about the new lower-level device and can either refuse its handling or 
	accept it. On accept, it has to create a new node with the lower-level device 
	node as its parent. To simplify the test, each node must have a type and
	the probe interface explicitily defines which node types are supported.
	Further, the driver description (see pnp_file_attr.h) can associate an 
	ASIC name and a human-readable name with various parent nodes. These names 
	(for ASIC: its index in the list of ASIC names) are passed to the probe 
	function.
	
	If a hardware/driver rescan is initiated, all consumers are notified
	of possible parents _again_, i.e. there is no difference between
	initial tree construction and a rescan. To avoid registering a node
	twice, each node has a connection and a device id attribute.
	If a node with the same parent, connection and device id attribute
	is already registered, a redetection is assumed and the new registration
	discarded. If only the device id is different it is assumed that the
	device has been replaced and the old node gets unregistered automatically.
	During rescan, all affected nodes are marked as to be verified. Those
	that are not re-registered during the rescan are assumed to be removed
	and are unregistered after the rescan. 
	
	Initialization of drivers is done on demand on a per-node basis. If the driver
	is initialized for the node, it said to be "loaded", else it is "unloaded".
	(Un)loading of drivers is usually requested as part of the (un)-
	initialization of a child node driver, leading to a recursive loading
	down to the root node driver. A driver is loaded/initialized only once 
	per node, further load request (e.g. by multiple consumers) are ignored 
	by means of a load counter. 
	
	All node-specific functions	of a driver must use a cookie to identify 
	the node. As the cookie	becomes invalid if the driver is unloaded, the driver
	must either be able to construct all data during load or store them as 
	attributes of the node. Still, nodes and their attributes are destroyed 
	when the system is shut down, i.e. are not reboot-persistent.

	If not only a consumer calls its parent node driver's interface but
	the parent driver the consumer too, the parent is said to be "managed" and 
	the	consumer is the "manager". In this case, both nodes must have special
	manager attributes defined. The system makes sure that the manager is always
	loaded first and assumes that the manager loads the managed node. If
	someone wants to load a managed node, the system loads the manager instead.
	
	If a node is unregistered, all its child nodes are recursively unregistered 
	automatically. The driver of a node to be unregistered is notified 
	(device_removed), so it can abort all running operations and 
	refuse new requests. The driver is not initialized just to call the
	device_removed hook, so the passed node cookie can be NULL. As soon as both
	the node is unregistered and the driver uninitialized, device_cleanup is
	called.
	
	In terms of synchronization, loading/unloading/remove/cleanup-notifications
	are executed synchroniously, i.e. if e.g. a device is to be unloaded 
	but	the drive currently handles a remove-notification, the unloading 
	is delayed until the nofication callback returns.
*/

#ifndef _PNP_DRIVER_H
#define _PNP_DRIVER_H

#include <pnp/pnp_module.h>
#include <TypeConstants.h>


// handle of PnP node
typedef struct pnp_node_info *pnp_node_handle;


// attribute of device node
typedef struct {
	const char		*name;
	type_code		type;			// for supported types, see value
	union {
		uint8		ui8;			// B_UINT8_TYPE
		uint16		ui16;			// B_UINT16_TYPE
		uint32		ui32;			// B_UINT32_TYPE
		uint64		ui64;			// B_UINT64_TYPE
		const char	*string;		// B_STRING_TYPE
		struct {					// B_RAW_TYPE
			void	*data;
			size_t	len;
		} raw;
	} value;
} pnp_node_attr;


// basic interface of PnP driver (required)
typedef struct pnp_driver_basic_interface {
	// initialize driver for given device node.
	// 		node 				- node of device
	// 		manager_cookie 		- cookie of managing consumer
	// 		cookie 				- cookie issued by this driver
	// <manager_cookie> is only valid if node is managed
	status_t	(*init_driver) (
					pnp_node_handle	node,
					void			*manager_cookie,
					void			**cookie
				);
	// uninitialize driver for given device.
	status_t	(*uninit_driver) (
					void			*cookie
				);
	// a device node, registered by this driver, got removed.
	// if the driver wasn't loaded when this happenes, no (un)init_device 
	// is called and thus <cookie> is NULL;
	void		(*device_removed) ( 
					pnp_node_handle	node,
					void			*cookie
				);
	// a device node, registered by this driver, got removed and
	// the driver got unloaded
	void		(*device_cleanup) ( 
					pnp_node_handle	node
				);
} pnp_driver_basic_interface;

#define PNP_DRIVER_BASIC_INTERFACE "driver/basic/v1"


// probe interface of PnP driver (optional)
// this interface is an array, terminated with <type>=NULL; so one module
// can support multiple parent node types;
// this interface is optional as the driver registering a node doesn't need to 
// be the driver for the node; obviously, this only makes sense when these two
// drivers are closely coupled, e.g. located in one add-on
typedef struct pnp_driver_probe_interface {
	// supported type of parent node.
	// compared with the beginning of the parent type, i.e. "usb" matches "usb/v1";
	// to match any parent type, specify ""
	const char 	*filter;
	// null-terminated list of valid ASIC names.
	// the ASIC name specified in the driver description is
	// compared to this list and its index passed to probe().
	// can be NULL to ignore ASIC name.
	const char	**asic_names;
	// parent was added or is rescanned.
	// check whether this parent is supported and register 
	// any consumer device. 
	// <name> is the device name as specified by driver descriptor
	// <asic> is the index of the asic name in asic_names.
	// <params> params as specified by driver descriptor.
	// Dynamic consumers must return B_OK if they support this parent. 
	// All other return values are ignored.
	status_t	(*probe) ( 
					pnp_node_handle	parent,
					const char 		*type,
					const char		*device_name,
					uint32			asic,
					const char		*params
				);
} pnp_driver_probe_interface;

#define PNP_DRIVER_PROBE_INTERFACE "driver/probe/v1"


// device interface proxy (optional)
// like a module interface proxy, but this time it's device-specific
typedef struct pnp_driver_proxy_interface {
	// get interface of given name.
	// 	cookie - device cookie
	status_t	(*get_interface)( 
					void		*cookie,
					const char	*interface_name,
					void		**interface
				);
	// free memory of specified interface
	void		(*free_interface)(
					void		*cookie,
					const char	*interface_name,
					void		*interface
				);	
} pnp_driver_proxy_interface;

#define PNP_DRIVER_PROXY_INTERFACE "driver/proxy/v1"


// standard attributes:

// module name of driver (required, string)
#define PNP_DEVICE_DRIVER "module"
// type of driver (required if there are dynamic consumers, string)
#define PNP_DEVICE_TYPE "type"
// human-readable name of device (optional, string)
#define PNP_DEVICE_NAME "name"
// name of ASIC (optional, string)
#define PNP_DEVICE_ASIC "asic"
// module name of fixed consumer - see pnp_manager.h (optional, string)
// append "/0", "/1" etc. if there are multiple fixed consumers
#define PNP_DEVICE_FIXED_CONSUMER "consumer/fixed"
// dynamic consumers pattern - see pnp_manager.h (optional, string)
// append "/0", "/1" etc. if there are multiple dynamic consumers
#define PNP_DEVICE_DYNAMIC_CONSUMER "consumer/dynamic"

// device is managed (optional, uint8)
// if != 0, this is a managed device, i.e. it cooperates with a managing 
// consumer ("the manager") and thus can only be used in conjunction with its
// manager. The node of the manager must have defined PNP_DEVICE_IS_MANAGER. There
// can be at most one manager per managed device; if there is none, the driver
// of the device cannot be loaded. If anyone but the manager tries to load
// the device driver, the manager is loaded instead (which _must_ load the
// driver). If the manager is unregistered (but not unloaded) and a new manager
// registered instead, the new manager cannot load the device' driver until
// the old manager is unloaded.
#define PNP_DEVICE_NEEDS_MANAGER "needs_manager"
// this is a managing consumer (optional, uint8)
// if != 0, this consumer manages its parent; must not be defined if parent
// is not a managed device
// (see PNP_DEVICE_NEEDS_MANAGER);
#define PNP_DEVICE_IS_MANAGER "is_manager"

// connection of parent the device is attached to (optional, string)
// there can be only one device per connection
#define PNP_DEVICE_CONNECTION "connection"
// pattern device identifier (optional, string)
// it is expanded (see pnp_manager.h) and used to detect replaced devices
#define PNP_DEVICE_DEVICE_IDENTIFIER "device_identifier"
// driver must not be loaded during rescan (optional, uint8)
// if != 0, driver must not be loaded during rescan 
//          nor can rescan be started when driver is loaded
// if the device uses I/O resources, you _must_ set this
// flag as the rescan would always fail if the driver is loaded
// due to resource contention
#define PNP_DEVICE_NO_LIVE_RESCAN "no_live_rescan"
// never rescan this device (optional, uint8)
// if != 0, device is never checked during rescan
#define PNP_DEVICE_NEVER_RESCAN "never_rescan"
// keep driver loaded (optional, uint8)
// if != 0, the driver is loaded automatically whenever the node
// is registered, and unloaded whenever the node is unregistered.
// if = 1, driver is temporarily unloaded during rescan
// if = 2, driver is not unloaded during rescan
// avoid the second case (2) as this makes replacing the driver
// impossible without a reboot. 
// for a managed device, this flag must not be set
#define PNP_DRIVER_ALWAYS_LOADED "always_loaded"
// don't send remove notification (optional, uint8)
// if != 0, the device_removed callback is not called
// apart from a slight speedup on device removal (which should be insignificant),
// this allows a module to (un)register a device in its post_init/pre_init
// functions - without it, you get a deadlock during unregister because
// the pnp_manager tries to load the module during unregister to notify it
#define PNP_DRIVER_NO_REMOVE_NOTIFICATION "no_remove_notification"

#endif
