#ifndef _USB_DEFS_H
#define _USB_DEFS_H

namespace Z {
namespace USB {


#define B_USB_DEVICE_ADDED		'_uba'
#define B_USB_DEVICE_REMOVED	'_ubr'

// The name of the BMessage pointer field to the USBDevice class
extern const char*	gkDevice;

}	// USB
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::USB::gkDevice;
#endif

#endif
