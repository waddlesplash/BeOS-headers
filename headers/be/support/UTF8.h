/******************************************************************************

	File:			UTF8.h

	Description:	UTF-8 conversion functions.

	Copyright 1997, Be Incorporated

******************************************************************************/


#ifndef _UTF8_H
#define _UTF8_H

#include <SupportDefs.h>


enum {
	B_ISO1_CONVERSION,
	B_ISO2_CONVERSION,
	B_ISO3_CONVERSION,
	B_ISO4_CONVERSION,
	B_ISO5_CONVERSION,
	B_ISO6_CONVERSION,
	B_ISO7_CONVERSION,
	B_ISO8_CONVERSION,
	B_ISO9_CONVERSION,
	B_ISO10_CONVERSION,
	B_MAC_ROMAN_CONVERSION,
	B_SJIS_CONVERSION,
	B_EUC_CONVERSION
};


status_t convert_to_utf8(uint32		srcEncoding, 
						 const char	*src, 
						 int32		*srcLen, 
						 char		*dst, 
						 int32		*dstLen);

status_t convert_from_utf8(uint32		dstEncoding,
						   const char	*src, 
						   int32		*srcLen, 
						   char			*dst, 
						   int32		*dstLen);


#endif			// #ifndef _UTF8_H
