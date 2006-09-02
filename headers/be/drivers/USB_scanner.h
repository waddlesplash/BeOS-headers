/*******************************************************************************
/
/	File:		USB_scanner.h
/
/	Description:	Generic interface for USB scanner devices.
/	For more information, see SANE (Scanner Access Now Easy").
/
/	Copyright 2003, YellowTab GmbH, All Rights Reserved.
/
*******************************************************************************/

#ifndef USB_SCANNER_H
#define USB_SCANNER_H

#include <drivers/Drivers.h>
#include <drivers/USB_spec.h>

#define B_SCANNER_IOCTL_VENDOR		B_DEVICE_OP_CODES_END+1
#define B_SCANNER_IOCTL_PRODUCT		B_DEVICE_OP_CODES_END+2
#define B_SCANNER_IOCTL_CTRLMSG		B_DEVICE_OP_CODES_END+3

struct usb_scanner_ioctl_ctrlmsg
{
	usb_request	req;
	void*		data;
};

#endif /* USB_SCANNER_H */
