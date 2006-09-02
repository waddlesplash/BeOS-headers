#ifndef _USB_ROSTER
#define _USB_ROSTER

#include <app/Messenger.h>

namespace Z {
namespace USB {

class BUSBRosterLooper;
class BUSBDevice;


class BUSBRoster
{
public:
	// If there is a BMessenger specified, it will be sent B_USB_DEVICE_ADDED 
	// and B_USB_DEVICE_REMOVED messages with a pointer named gkDevice to the 
	//  USBDevice class as defined in USBDefs.h
							BUSBRoster(BMessenger _target = BMessenger());
	virtual					~BUSBRoster();
	
	// DeviceAdded() is called when a new device appears on the Bus.
	// If the result is not B_OK, the USBDevice instance is deleted and
	// there will be no DeviceRemoved notification.
	virtual		status_t	DeviceAdded(Z::USB::BUSBDevice* _device);
	
	// DeviceRemoved() is called when a device is disconnected from the Bus.
	// The USBDevice WILL BE deleted after this method returns.
	virtual		void		DeviceRemoved(Z::USB::BUSBDevice* _device);
		
				void		SetTarget(BMessenger _target);
				BMessenger&	GetTarget();
				void		Start();
				void		Stop();

private:
	virtual		void	_ExpandingUniverse0();
	virtual		void	_ExpandingUniverse1();
	virtual		void	_ExpandingUniverse2();
	virtual		void	_ExpandingUniverse3();
	virtual		void	_ExpandingUniverse4();
	virtual		void	_ExpandingUniverse5();
	virtual		void	_ExpandingUniverse6();
	virtual		void	_ExpandingUniverse7();
	

private:
	Z::USB::
	BUSBRosterLooper*	fRLooper;
	BMessenger			fTarget;
	uint32				fHeatDeath[8];
};

}	// USB
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::USB::BUSBRoster;
#endif

#endif
