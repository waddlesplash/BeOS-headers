/* 
** USB_spec.h
**
** Copyright 1999, Be Incorporated. All Rights Reserved.
** Copyright 2003, YellowTab GmbH. All Rights Reserved.
**
** This file contains structures and constants based on
** the USB Specification 2.0
**
*/

#ifndef _USB_SPEC_H
#define _USB_SPEC_H

#include <SupportDefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Device class codes */
#define UDCLASS_IN_INTERFACE	0x00
#define UDCLASS_COMM			0x02

#define UDCLASS_HUB				0x09
#define  UDSUBCLASS_HUB			 0x00
#define   UDPROTO_FSHUB			  0x00
#define   UDPROTO_HSHUBSTT		  0x01
#define   UDPROTO_HSHUBMTT		  0x02

#define UDCLASS_DIAGNOSTIC		0xdc
#define  UDSUBCLASS_REPDD		 1
#define   UDPROTO_USB2COMPL		  1

#define UDCLASS_WIRELESS		0xe0
#define  UDSUBCLASS_RF			 0x01
#define   UDPROTO_BLUETOOTH		  0x01

#define UDCLASS_MISC			0xef
#define  UDSUBCLASS_MSC_COMMON	 2
#define   UDPROTO_MSC_IAD		  1
	
#define UDCLASS_VENDOR			0xff

/* Interface class codes */
#define UICLASS_UNSPEC		0x00

#define UICLASS_AUDIO				0x01
#define  UISUBCLASS_AUDIOCONTROL	 1
#define  UISUBCLASS_AUDIOSTREAM		 2
#define  UISUBCLASS_MIDISTREAM		 3

#define UICLASS_CDC										0x02 /* communication */
#define	 UISUBCLASS_DIRECT_LINE_CONTROL_MODEL			 1
#define  UISUBCLASS_ABSTRACT_CONTROL_MODEL				 2
#define	 UISUBCLASS_TELEPHONE_CONTROL_MODEL				 3
#define	 UISUBCLASS_MULTICHANNEL_CONTROL_MODEL			 4
#define	 UISUBCLASS_CAPI_CONTROLMODEL					 5
#define	 UISUBCLASS_ETHERNET_NETWORKING_CONTROL_MODEL	 6
#define	 UISUBCLASS_ATM_NETWORKING_CONTROL_MODEL		 7
#define   UIPROTO_CDC_AT								  1

#define UICLASS_HID				0x03
#define  UISUBCLASS_BOOT		 1
#define   UIPROTO_BOOT_KEYBOARD	  1
#define   UIPROTO_BOOT_MOUSE	  2

#define UICLASS_PHYSICAL	0x05

#define UICLASS_IMAGE		0x06
#define  UISUBCLASS_IMAGE	 1
#define   UIPROTO_IMAGE		  1

#define UICLASS_PRINTER			0x07
#define  UISUBCLASS_PRINTER		1
#define   UIPROTO_PRINTER_UNI	 1
#define   UIPROTO_PRINTER_BI	 2
#define   UIPROTO_PRINTER_1284	 3

#define UICLASS_MASS			0x08
#define  UISUBCLASS_RBC			 1
#define  UISUBCLASS_SFF8020I	 2
#define  UISUBCLASS_QIC157		 3
#define  UISUBCLASS_UFI			 4
#define  UISUBCLASS_SFF8070I	 5
#define  UISUBCLASS_SCSI		 6
#define   UIPROTO_MASS_CBI_I	  0
#define   UIPROTO_MASS_CBI		  1
#define   UIPROTO_MASS_BBB_OLD	  2		/* Not in the spec anymore */
#define   UIPROTO_MASS_BBB		  80	/* 'P' for the Iomega Zip drive */

#define UICLASS_HUB			0x09
#define  UISUBCLASS_HUB		 0
#define   UIPROTO_FSHUB		  0
#define   UIPROTO_HSHUBSTT	  0 /* Yes, same as previous */
#define   UIPROTO_HSHUBMTT	  1

#define UICLASS_CDC_DATA			0x0a
#define  UISUBCLASS_DATA			 0
#define   UIPROTO_DATA_ISDNBRI		  0x30    /* Physical iface */
#define   UIPROTO_DATA_HDLC			  0x31    /* HDLC */
#define   UIPROTO_DATA_TRANSPARENT	  0x32    /* Transparent */
#define   UIPROTO_DATA_Q921M		  0x50    /* Management for Q921 */
#define   UIPROTO_DATA_Q921			  0x51    /* Data for Q921 */
#define   UIPROTO_DATA_Q921TM		  0x52    /* TEI multiplexer for Q921 */
#define   UIPROTO_DATA_V42BIS		  0x90    /* Data compression */
#define   UIPROTO_DATA_Q931			  0x91    /* Euro-ISDN */
#define   UIPROTO_DATA_V120			  0x92    /* V.24 rate adaption */
#define   UIPROTO_DATA_CAPI			  0x93    /* CAPI 2.0 commands */
#define   UIPROTO_DATA_HOST_BASED	  0xfd    /* Host based driver */
#define   UIPROTO_DATA_PUF			  0xfe    /* see Prot. Unit Func. Desc.*/
#define   UIPROTO_DATA_VENDOR		  0xff    /* Vendor specific */

#define UICLASS_SMARTCARD	0x0b

/*#define UICLASS_FIRM_UPD	0x0c*/

#define UICLASS_SECURITY	0x0d

#define UICLASS_VIDEO		0x0e

#define UICLASS_DIAGNOSTIC	0xdc

#define UICLASS_WIRELESS		0xe0
#define  UISUBCLASS_RF			 0x01
#define   UIPROTO_BLUETOOTH		  0x01

#define UICLASS_APPL_SPEC				0xfe
#define  UISUBCLASS_FIRMWARE_DOWNLOAD	 1
#define  UISUBCLASS_IRDA				 2
#define  UISUBCLASS_USBTMC				 3
#define   UIPROTO_IRDA					  0

#define UICLASS_VENDOR		0xff

/* request types (target & direction) for  send_request() */
/* cf USB Spec Rev 2.0, table 9-2, p 248 */
#define USB_REQTYPE_DEVICE_IN         0x80
#define USB_REQTYPE_DEVICE_OUT        0x00
#define USB_REQTYPE_INTERFACE_IN      0x81
#define USB_REQTYPE_INTERFACE_OUT     0x01
#define USB_REQTYPE_ENDPOINT_IN       0x82
#define USB_REQTYPE_ENDPOINT_OUT      0x02
#define USB_REQTYPE_OTHER_OUT         0x03
#define USB_REQTYPE_OTHER_IN          0x83

/* request types for send_request() */
/* cf USB Spec Rev 2.0, table 9-2, p 248 */
#define USB_REQTYPE_STANDARD          0x00
#define USB_REQTYPE_CLASS             0x20
#define USB_REQTYPE_VENDOR            0x40
#define USB_REQTYPE_RESERVED          0x60
#define USB_REQTYPE_MASK              0x9F

/* standard request values for send_request() */
/* cf USB Spec Rev 2.0, table 9-4, p 251 */
#define USB_REQUEST_GET_STATUS           0
#define USB_REQUEST_CLEAR_FEATURE        1
#define USB_REQUEST_SET_FEATURE          3
#define USB_REQUEST_SET_ADDRESS          5
#define USB_REQUEST_GET_DESCRIPTOR       6
#define USB_REQUEST_SET_DESCRIPTOR       7
#define USB_REQUEST_GET_CONFIGURATION    8
#define USB_REQUEST_SET_CONFIGURATION    9
#define USB_REQUEST_GET_INTERFACE       10
#define USB_REQUEST_SET_INTERFACE       11
#define USB_REQUEST_SYNCH_FRAME         12

/* used by {set,get}_descriptor() */
/* cf USB Spec Rev 2.0, table 9-5, p 251 */
#define USB_DESCRIPTOR_DEVICE            1
#define USB_DESCRIPTOR_CONFIGURATION     2
#define USB_DESCRIPTOR_STRING            3
#define USB_DESCRIPTOR_INTERFACE         4
#define USB_DESCRIPTOR_ENDPOINT          5
#define USB_DESCRIPTOR_DEVICE_QUALIFIER  6
#define USB_DESCRIPTOR_OTHER_SPEED_CONFIGURATION  7
#define USB_DESCRIPTOR_INTERFACE_POWER   8

/* used by {set,clear}_feature() */
/* cf USB Spec Rev 2.0, table 9-6, p 252 */
#define USB_FEATURE_DEVICE_REMOTE_WAKEUP	1
#define USB_FEATURE_ENDPOINT_HALT			0
#define USB_FEATURE_TEST_MODE               2

typedef struct {
/* cf USB Spec Rev 2.0, table 9-2, p 248 */
	uint8 request_type;
	uint8 request;
	uint16 value;
	uint16 index;
	uint16 length;
} _PACKED usb_request;

typedef struct {
/* cf USB Spec Rev 2.0, figure 9-4/5/6, p 255/256 */
	uint16		status;
} _PACKED usb_device_status;

/* Device status flags */
#define USB_DEVICE_STATUS_SELF_POWERED		0x0001
#define USB_DEVICE_STATUS_REMOTE_WAKEUP		0x0002
/* Endpoint status flags */
#define USB_ENDPT_STATUS_HALT				0x0001

typedef struct { 
	/* cf USB Spec Rev 2.0, table 9-8, p 262 */
	uint8 length;
	uint8 descriptor_type;          /* USB_DESCRIPTOR_DEVICE */
	uint16 usb_version;             /* USB_DESCRIPTOR_DEVICE_LENGTH */
	uint8 device_class;
	uint8 device_subclass;
	uint8 device_protocol;
	uint8 max_packet_size_0;
	uint16 vendor_id;
	uint16 product_id;
	uint16 device_version;
	uint8 manufacturer;
	uint8 product;
	uint8 serial_number;
	uint8 num_configurations;
} _PACKED usb_device_descriptor;

typedef struct {
	/* cf USB Spec Rev 2.0, table 9-9, p 264 */
	uint8 length;
	uint8 descriptor_type;			/* USB_DESCRIPTOR_DEVICE_QUALIFIER */
	uint16 usb_version;				/* USB_DESCRIPTOR_DEVICE_QUALIFIER_LENGTH */
	uint8 device_class;
	uint8 device_subclass;
	uint8 device_protocol;
	uint8 max_packet_size_0;
	uint8 num_configurations;
	uint8 reserved;
} _PACKED usb_device_qualifier_descriptor;
	
typedef struct {
	/* cf USB Spec Rev 2.0, table 9-10, p 265 */
	uint8 length;
	uint8 descriptor_type;          /* USB_DESCRIPTOR_CONFIGURATION */
	uint16 total_length;            /* USB_DESCRIPTOR_CONFIGURATION_LENGTH */
	uint8 number_interfaces;
	uint8 configuration_value;
	uint8 configuration;
	uint8 attributes;
	uint8 max_power;
} _PACKED usb_configuration_descriptor;

/* Bitvalues for usb_configuration_descriptor.attributes */
/* cf USB Spec Rev 2.0, table 9-10, p 266 */
#define USB_CFG_ATTR_BUS_POWERED	0x80
#define USB_CFG_ATTR_SELF_POWERED	0x40
#define USB_CFG_ATTR_REMOTE_WAKEUP	0x20

typedef struct {
	/* cf USB Spec Rev 2.0, table 9-11, p 267 */
	uint8 length;
	uint8 descriptor_type;			/* USB_DESCRIPTOR_OTHER_SPEED_CONFIGURATION */
	uint16 total_length;
	uint8 number_interfaces;
	uint8 configuration_value;
	uint8 configuration;
	uint8 attributes;
	uint8 max_power;
} _PACKED usb_other_speed_configuration_descriptor;	

typedef struct {
	/* cf USB Spec Rev 2.0, table 9-12, p 268 */
	uint8 length;
	uint8 descriptor_type;          /* USB_DESCRIPTOR_INTERFACE */
	uint8 interface_number;         /* USB_DESCRIPTOR_INTERFACE_LENGTH  */
	uint8 alternate_setting;
	uint8 num_endpoints;
	uint8 interface_class;
	uint8 interface_subclass;
	uint8 interface_protocol;
	uint8 interface;
} _PACKED usb_interface_descriptor;

typedef struct {
	/* cf USB Spec Rev 2.0, table 9-13, p 269 */
	uint8 length;
	uint8 descriptor_type;          /* USB_DESCRIPTOR_ENDPOINT */
	uint8 endpoint_address;         /* USB_DESCRIPTOR_ENDPOINT_LENGTH */
	uint8 attributes;
	uint16 max_packet_size;
	uint8 interval;
} _PACKED usb_endpoint_descriptor;

#define USB_EP_ATTR_TYPE				0x03u 
#define USB_EP_ATTR_TYPE_CONTROL 		0x00u 
#define USB_EP_ATTR_TYPE_ISOCHRONOUS 	0x01u 
#define USB_EP_ATTR_TYPE_BULK 			0x02u 
#define USB_EP_ATTR_TYPE_INTERRUPT 		0x03u 

#define USB_EP_ADDR_NUMBER_MASK			0x0Fu
#define USB_EP_ADDR_DIR_MASK			0x80u
#define USB_EP_ADDR_DIR_IN				0x80u
#define USB_EP_ADDR_DIR_OUT				0x00u

typedef struct {
	/* cf USB Spec Rev 2.0, table 9-15/16, p 273/274 */
	uint8 length;                   /* USB_DESCRIPTOR_STRING */
	uint8 descriptor_type;
	uchar string[1];
} _PACKED usb_string_descriptor;

typedef struct {
	uint8 length;
	uint8 descriptor_type;
	uint8 data[1];
} _PACKED usb_generic_descriptor;

typedef union {
	usb_generic_descriptor generic;
	usb_device_descriptor device;
	usb_device_qualifier_descriptor qualifier;
	usb_other_speed_configuration_descriptor otherspeed;
	usb_interface_descriptor interface;
	usb_endpoint_descriptor endpoint;
	usb_configuration_descriptor configuration;
	usb_string_descriptor string;
} usb_descriptor;

#ifdef __cplusplus
}
#endif

#endif
