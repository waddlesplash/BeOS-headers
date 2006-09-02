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

#ifndef _CAPI_H
#define _CAPI_H

#ifdef __cplusplus
	extern "C" {
#endif

/* Register application with COMMON-ISDN-API */
status_t 
CAPI_REGISTER(uint32 MessageBufferSize, 	/* Size of Message Buffer */
			  uint32 maxLogicalConnection, 	/* Maximum number of logical connections */
			  uint32 maxBDataBlocks, 		/* Number of data blocks available simultaneously */
			  uint32 maxBDataLen, 			/* Maximum size of a data block */
			  uint32 * pApplID ); 			/* Location to return assigned application identification number */

/* Release application from COMMON-ISDN-API */
status_t
CAPI_RELEASE(uint32 ApplID); 				/* number assigned by the function CAPI_REGISTER */

/* Transfer message to COMMON-ISDN-API */
status_t 
CAPI_PUT_MESSAGE(uint32 ApplID, 			/* number assigned by the function CAPI_REGISTER */
				void * pCAPIMessage); 		/* Pointer to the message being passed to COMMON-ISDN-API */

/* Retrieve message from COMMON-ISDN-API */
status_t 
CAPI_GET_MESSAGE(uint32 ApplID, 			/* number assigned by the function CAPI_REGISTER */
				void ** ppCAPIMessage);		/* Pointer to the memory location where COMMON-ISDN-API
											   should place the pointer to the retrieved message */

/* Get manufacturer information from COMMON-ISDN-API */
status_t
CAPI_GET_MANUFACTURER(char * SzBuffer);		/* Pointer to a buffer of 64 bytes */

/* Get version information from COMMON-ISDN-API */
status_t 
CAPI_GET_VERSION(uint32 * pCAPIMajor,
				 uint32 * pCAPIMinor,
				 uint32 * pManufacturerMajor,
				 uint32 * pManufacturerMinor);

/* Get serial number of COMMON-ISDN-API */
status_t 
CAPI_GET_SERIAL_NUMBER(char * Buffer);		/* Pointer to a buffer of 8 bytes */

/* Get capability information from COMMON-ISDN-API */
status_t 
CAPI_GET_PROFILE(void *Buffer,				/* Pointer to a buffer of 64 bytes */
				 uint32 CtrlNr);			/* Number of Controller. If 0, only the number of 
				 							   installed controllers is returned to the application. */

/* Check whether COMMON-ISDN-API & hardware is installed */
status_t 
CAPI_INSTALLED(void);

/* Wait for COMMON-ISDN-API message to get available */
status_t 
CAPI_WAIT_FOR_SIGNAL(uint32 ApplID,			
					 bigtime_t timeout);

#ifdef __cplusplus
	}
#endif

#endif
