//******************************************************************************
//
//      File:           TranslationDefs.h
//
//      Description:    Miscellaneous basic definitions for the Translation Kit
//
//      Copyright 1998, Be Incorporated, All Rights Reserved.
//      Copyright 1995-1997, Jon Watte
//
//******************************************************************************

#if !defined(_TRANSLATION_DEFS_H)
#define _TRANSLATION_DEFS_H

#if !defined(_BE_BUILD_H)
#include <BeBuild.h>
#endif /* _BE_BUILD_H */
#if !defined(_SUPPORT_DEFS_H)
#include <SupportDefs.h>
#endif /* _SUPPORT_DEFS_H */


typedef unsigned long translator_id;


/*	when you export this struct, end with an empty	*/
/*	record that has 0 for "type"	*/

/*	This should go into Errors.h	*/

enum B_TRANSLATION_ERROR {
	B_TRANSLATION_BASE_ERROR = (int)0x80004800,
	B_NO_TRANSLATOR = B_TRANSLATION_BASE_ERROR,	/*	no translator exists for data	*/
	B_ILLEGAL_DATA,	/*	data is not what it said it was	*/
/* aliases */
	B_NOT_INITIALIZED = B_NO_INIT
};


/*	These are defines, because they reflect the state at which the app was compiled	*/
#define B_TRANSLATION_CURRENT_VERSION	170
#define B_TRANSLATION_MIN_VERSION		161

#if __POWERPC__
#pragma export on
#endif

extern const char * B_TRANSLATOR_MIME_TYPE;

struct translation_format {
	uint32		type;				// B_ASCII_TYPE, ...
	uint32		group;				// B_TRANSLATOR_BITMAP, B_TRANSLATOR_TEXT, ...
	float		quality;			// format quality 0.0-1.0
	float		capability;			// translator capability 0.0-1.0
	char		MIME[251];			// MIME string
	char		name[251];			// only descriptive	
};


/*	This struct is different from the format struct for a reason:	*/
/*	to separate the notion of formats from the notion of translations	*/

struct translator_info {			// Info about a specific translation
	uint32			type;			// B_ASCII_TYPE, ...
	translator_id	translator;		// Filled in by BTranslationRoster
	uint32			group;			// B_TRANSLATOR_BITMAP, B_TRANSLATOR_TEXT, ...
	float			quality;		// Quality of format in group 0.0-1.0
	float			capability;		// How much of the format do we do? 0.0-1.0
	char			name[251];
	char			MIME[251];
};

#if __POWERPC__
#pragma export reset
#endif

#endif /* _TRANSLATION_DEFS_H */

