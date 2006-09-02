#ifndef _USB_CONFIGURATION
#define _USB_CONFIGURATION

#include <drivers/USB.h>	// usb_configuration_descriptor
#include <support/List.h>

namespace Z {
namespace USB {
	
class BUSBDevice;
class BUSBInterface;

class BUSBConfiguration
{
public:	
	// Connectivity functions (this Configuration belongs to a Device)
	const	Z::USB::BUSBDevice*				Device() const;
	
	// Iterators for the Interfaces provided by this Configuration
			uint32							CountInterfaces() const;
	const	Z::USB::BUSBInterface*			InterfaceAt(uint32 _index) const;
	
	// Access the raw descriptor
	const	usb_configuration_descriptor*	Descriptor() const;

		
private:
	virtual		void	_ExpandingUniverse0();
	virtual		void	_ExpandingUniverse1();
	virtual		void	_ExpandingUniverse2();
	virtual		void	_ExpandingUniverse3();
	virtual		void	_ExpandingUniverse4();
	virtual		void	_ExpandingUniverse5();
	virtual		void	_ExpandingUniverse6();
	virtual		void	_ExpandingUniverse7();


	friend Z::USB::BUSBDevice;
	friend Z::USB::BUSBInterface;
	
									BUSBConfiguration(uint32 _index, 
									                 Z::USB::BUSBDevice*	_device);
	virtual							~BUSBConfiguration();
	
private:
	Z::USB::BUSBDevice*				fDevice;
	uint32							fConfiguration_num;
	usb_configuration_descriptor	fDescriptor;
	BList							fInterfaces;
	uint32							fHeatDeath[8];
};

}	// USB
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::USB::BUSBConfiguration;
#endif

#endif

