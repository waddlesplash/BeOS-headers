#ifndef _USB_INTERFACE
#define _USB_INTERFACE

#include <drivers/USB.h>	// usb_interface_descriptor
#include <support/List.h>

namespace Z {
namespace USB {

class BUSBConfiguration;
class BUSBEndpoint;
class BUSBDevice;

class BUSBInterface
{
public:
	// Connectivity functions (this Interface belongs to a Configuration which
	// belongs to a Device)
	const	Z::USB::BUSBConfiguration*	Configuration() const;
	const	Z::USB::BUSBDevice*			Device() const;

	// Iterate over the Endpoints defined by this Interface
			uint32						CountEndpoints() const;
	const	Z::USB::BUSBEndpoint*		EndpointAt(uint32 _index) const;

			status_t					OtherDescriptorAt(uint32 _index, 
										                  usb_descriptor* _descriptor, 
										                  size_t _size) const;
	
	// Access the raw descriptor
	const	usb_interface_descriptor*	Descriptor() const;

	// Accessors for useful bits in the descriptor	
			uint8						Class() const;
			uint8						Subclass() const;
			uint8						Protocol() const;
			const char*					InterfaceString() const;

private:
	virtual		void	_ExpandingUniverse0();
	virtual		void	_ExpandingUniverse1();
	virtual		void	_ExpandingUniverse2();
	virtual		void	_ExpandingUniverse3();
	virtual		void	_ExpandingUniverse4();
	virtual		void	_ExpandingUniverse5();
	virtual		void	_ExpandingUniverse6();
	virtual		void	_ExpandingUniverse7();

	friend Z::USB::BUSBDevice;           // only created by USBDevice
	friend Z::USB::BUSBConfiguration;    // only destroyed by the containing Configuration


								BUSBInterface(uint32 _index, Z::USB::BUSBConfiguration* _config);
	virtual						~BUSBInterface();
	
private:
	Z::USB::
	BUSBConfiguration*			fConfiguration;
	usb_interface_descriptor	fDescriptor;
	uint32						fInterface_num;
	BList						fEndpoints;
	uint32						fHeatDeath[8];
};

}	// USB
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::USB::BUSBInterface;
#endif

#endif
