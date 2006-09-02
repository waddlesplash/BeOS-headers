#ifndef _USB_DEVICE_H
#define _USB_DEVICE_H

#include <drivers/USB.h>	// usb_device_descriptor
#include <support/List.h>

namespace Z {
namespace USB {
	
class BUSBConfiguration;
class BUSBEndpoint;
class BUSBInterface;

class BUSBDevice 
{
	public:
										BUSBDevice(const char* _path = NULL);
		virtual							~BUSBDevice();
		virtual	status_t				InitCheck();
				status_t			 	SetTo(const char* _path);
	
		// Bus Topology information methods:
	
		// Return the logical path (eg 0/0/1 of the device), or NULL if unconfigured
				const char* 			Location() const;
	
		// Return true if this device is a usb hub	
				bool					IsHub() const;
		
			// Accessors for useful bits in the descriptor
				uint16					USBVersion() const;
				uint8					Class() const;
				uint8					Subclass() const; 
				uint8					Protocol() const;
				uint8					MaxEndpoint0PacketSize() const;
				uint16					VendorID() const;
				uint16					ProductID() const;
				uint16					Version() const;
		const	char*					ManufacturerString() const;
		const	char*					ProductString() const;
		const	char*					SerialNumberString() const;
		
		// Access the raw descriptor
		const	usb_device_descriptor*	Descriptor() const;
			
		// Read a string descriptor from the Device into a buffer
				size_t					GetStringDescriptor(uint32 _index, 
										                    usb_string_descriptor* _desc, 
										                    size_t _length) const;
		
				size_t					GetDescriptor(uint8 _type, uint8 _index, uint16 _lang, 
										              void* _data, size_t _len) const;
	
		// Read a string descriptor, convert it from Unicode to UTF8, return a new char[]
		// containing the string (must be delete'd by the caller)	
				char*					DecodeStringDescriptor(uint32 _index) const;
		
		// Iterate over the possible configurations
				uint32					CountConfigurations() const;
		const	Z::USB::
				BUSBConfiguration*		ConfigurationAt(uint32 _index) const;
	
		// View and select the active configuration
		const	Z::USB::
				BUSBConfiguration*		ActiveConfiguration() const;
				status_t				SetConfiguration(const Z::USB::BUSBConfiguration* _config);
	
		// Initiate a Control (endpoint 0) transaction
				ssize_t					ControlTransfer(uint8 _request_type, uint8 _request, 
										                uint16 _value, uint16 _index, 
										                uint16 _length, void* _data) const;
			
	private:
		virtual	void					_ExpandingUniverse0();
		virtual	void					_ExpandingUniverse1();
		virtual	void					_ExpandingUniverse2();
		virtual	void					_ExpandingUniverse3();
		virtual	void					_ExpandingUniverse4();
		virtual	void					_ExpandingUniverse5();
		virtual	void					_ExpandingUniverse6();
		virtual	void					_ExpandingUniverse7();
		
				ssize_t					InterruptTransfer(const Z::USB::BUSBEndpoint* _endpoint, 
										                  void* _data, 
										                  size_t _length,
										                  bigtime_t timeout = 0) const;
	
				ssize_t					BulkTransfer(const Z::USB::BUSBEndpoint* _endpoint, 
										             void* _data, 
										             size_t _length,
										             bigtime_t timeout = 0) const;
	
				status_t				GetOtherDescr(uint32 _config, 
										              uint32 _interface, 
										              uint32 _index, 
										              usb_descriptor* _descriptor, 
										              size_t _size) const;	
		
				void					Release();
	
				void					PopulateInterface(BUSBInterface* _interface, 
										                  usb_interface_descriptor* _descriptor);
				void					PopulateConfig(BUSBConfiguration* _config, 
										               usb_configuration_descriptor* _descriptor);
				void					PopulateDevice();
		
	private:
				mutable char*					fSerial_string;         // Cache the string descriptors
				mutable char*					fManufacturer_string;
				mutable char*					fProduct_string;
						char*					fLocation;              // Bus Topology info
						bool					fIshub;
						int						fFd;                    // Connection to /dev/bus/usb/...
						usb_device_descriptor	fDescriptor;			// Cache the descriptor
						BUSBConfiguration*		fActive;             	// Current active configuration
						BList					fConfigurations;        // All possible configurations
						uint32					fHeatDeath[8];
		
	friend Z::USB::BUSBEndpoint; // USBEndpoint uses the XxxTransfer() methods
	friend Z::USB::BUSBInterface;	
};

}	// USB
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::USB::BUSBDevice;
#endif

#endif
