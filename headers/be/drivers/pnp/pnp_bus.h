/*
	Copyright (c) 2003-04, Thomas Kurschel. All rights reserved.
	Distributed under the terms of the MIT License.


	Required interface of PnP bus drivers
	
	Busses consist of two node layers: the lower layer defines the bus,
	the upper layer defines the abstract devices connected to the bus. 
	Both layers are handled by a bus manager. Actual device nodes are 
	on top of abstract device nodes.
	
	E.g. if we have a PCI bus with an IDE controller on it, we get
	
	IDE controller -> PCI device -> PCI bus
	
	with: 
		IDE controller = actual device node
		PCI device = abstract device node
		PCI bus = bus node
		
	The PCI bus manager establishes both the PCI devices and the PCI busses.
	
	Abstract device nodes act as a gateway between actual device nodes
	and the corresponding bus node. They are constructed by the bus 
	node driver via	its rescan() hook. To identify a bus node, define
	PNP_BUS_IS_BUS as an attribute of it. As a result, the PnP manager
	will call the rescan() method of the bus driver whenever the
	bus is to be rescanned. Afterwards, all possible dynamic consumers
	are informed as done for normal nodes.
	
	Normally, potential device drivers are notified immediately when 
	rescan() registers a new abstract device node. But sometimes, device
	drivers need to know _all_ devices connected to the bus for correct
	detection. To ensure this, the bus node must define 
	PNP_BUS_NOTIFY_CONSUMERS_AFTER_RESCAN. In this case, scanning for
	consumers is postponed until rescan() has finished.

	If hot-plugging of devices can be detected automatically (e.g. USB), 
	you should define PNP_DRIVER_ALWAYS_LOADED, so the bus driver is 
	always loaded and thus capable of handling hot-plug events generated 
	by the bus controller hardware.
*/
		
#ifndef _PNP_BUS_H
#define _PNP_BUS_H

#include <pnp/pnp_driver.h>

// interface of PnP bus (required)
typedef struct pnp_bus_interface {
	// (re)scan bus and register all devices (required)
	// driver is always loaded during this call, but other hooks may
	// be called concurrently
	status_t (*rescan) ( 
				void	*cookie 
	);
} pnp_bus_interface;

#define PNP_BUS_INTERFACE "driver/bus/v1"


// bus attributes:

// PnP bus identification (required, uint8)
// define this to let the PnP manager know that this is a PnP bus
// the actual content is ignored
#define PNP_BUS_IS_BUS "bus/is_bus"

// defer searching for consumers (optional, uint8)
// if != 0, probe() of consumers is called after rescan() of bus
//    else, probe() of consumers is called during rescan() of bus
// normally, consumers are informed about a new device as soon as
// it is registered by rescan(), i.e. not all devices may have been
// detected and registered yet;
// with this flag, detection of consumers is postponed until 
// rescan() has finished, i.e. when all devices are registered
#define PNP_BUS_DEFER_PROBE "bus/defer_probe"


// device attributes:

// this is a device detected during bus scan (required, uint8)
// all devices detected during a bus scan must have this flag set to 1;
// else, they get discarded during a pure driver scan as they aren't
// registered by a consument but the bus driver itself
#define PNP_BUS_DEVICE "bus_device"

#endif
