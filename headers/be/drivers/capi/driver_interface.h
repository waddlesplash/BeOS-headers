/*
 * This file is part of the CAPI library
 *
 * Copyright (c) 2001, 2002 Marcus Overhagen <marcus@overhagen.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 */


#define IOCTL_CAPI_GET_PROFILE		0x9900
/* parameter: pointer to */
struct capi_get_profile_iocl
{
	void *Buffer;
	uint32 CtrlNr;
};


#define IOCTL_CAPI_WAIT_FOR_SIGNAL	0x9901
/* parameter: pointer to bigtime_t timeout */

#define IOCTL_CAPI_GET_APPLID		0x9902
/* parameter: pointer to uint32 ApplID */

#define IOCTL_CAPI_GET_RECEIVEPORT	0x9903
/* parameter: pointer to port_id */

#define IOCTL_CAPI_SEND_MESSAGE		0x9904
/* parameter: pointer to ioctl_transfer */


#define PORT_INFO		0x101
#define PORT_MESSAGE	0x102
#define PORT_DATA		0x103
struct port_transfer
{
	int32 SizeMessage;
	int32 SizeData;		// -1 means not present
};


struct ioctl_transfer
{
	int32 SizeMessage;
	void *Message;
	int32 SizeData; 	// -1 means not present
	void *Data;
};
