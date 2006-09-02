#ifndef _USB_ENDPOINT_H
#define _USB_ENDPOINT_H

#include <drivers/USB.h>	// usb_endpoint_descriptor

namespace Z {
namespace USB {

class BUSBDevice;
class BUSBInterface;
class BUSBConfiguration;

class BUSBEndpoint
{
public:
	// Connectivity functions (this endpoint belongs to an Interface that
	// belongs to a Configuration that belongs to a Device)
	const	Z::USB::BUSBInterface*		Interface() const;
	const	Z::USB::BUSBConfiguration*	Configuration() const;
	const 	Z::USB::BUSBDevice*			Device() const;

	// Raw descriptor data	
	const	usb_endpoint_descriptor*	Descriptor() const;
	
	// Descriptor Accessor Functions
			bool						IsBulk() const;
			bool						IsInterrupt() const;
			bool						IsIsochronous() const;
			bool						IsInput() const;
			bool						IsOutput() const;
			uint16						MaxPacketSize() const;
			uint8						Interval() const;

	// Initiate a USB Transaction	
			ssize_t						InterruptTransfer(void* _data, size_t _length, bigtime_t timeout = 0) const;
			ssize_t						BulkTransfer(void* _data, size_t _length, bigtime_t timeout = 0) const;
	
private:
	virtual		void	_ExpandingUniverse0();
	virtual		void	_ExpandingUniverse1();
	virtual		void	_ExpandingUniverse2();
	virtual		void	_ExpandingUniverse3();
	virtual		void	_ExpandingUniverse4();
	virtual		void	_ExpandingUniverse5();
	virtual		void	_ExpandingUniverse6();
	virtual		void	_ExpandingUniverse7();

	friend Z::USB::BUSBDevice;          // Only created by a USBDevice
	friend Z::USB::BUSBInterface;       // Only destroyed by a containing USBInterface

							BUSBEndpoint(uint32 _index, Z::USB::BUSBInterface* _interface);
	virtual					~BUSBEndpoint();
private:
	Z::USB::	
	BUSBInterface*			fInterface;
	usb_endpoint_descriptor	fDescriptor;
	uint32					fEndpoint_num;
	uint32					fHeatDeath[8];
};

}	// USB
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::USB::BUSBEndpoint;
#endif

#endif

