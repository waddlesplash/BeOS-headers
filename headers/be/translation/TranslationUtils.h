//******************************************************************************
//
//      File:           TranslationUtils.h
//
//      Description:    Utility functions for using Translation Kit
//
//      Copyright 1998, Be Incorporated, All Rights Reserved.
//      Copyright 1995-1997, Jon Watte
//
//******************************************************************************

#if !defined(_TRANSLATION_UTILS_H)
#define _TRANSLATION_UTILS_H

#if !defined(_TRANSLATION_DEFS_H)
	#include <TranslationDefs.h>
#endif	/* _TRANSLATION_DEFS_H */
#if !defined(_SUPPORT_DEFS_H)
	#include <SupportDefs.h>
#endif /* _SUPPORT_DEFS_H */


class BBitmap;
class BTranslatorRoster;
class BPositionIO;

/* This class is a little different from many other classes. */
/* You don't create an instance of it; you just call its various */
/* static member functions for utility-like operations. */

class BTranslationUtils
{
		BTranslationUtils();
		~BTranslationUtils();
		BTranslationUtils(
				const BTranslationUtils &);
		BTranslationUtils & operator=(
				const BTranslationUtils &);

public:

/***	BITMAP getters - allocate the BBitmap; you call delete on it!	***/

		/*	Get bitmap - first try as file name, then as B_TRANSLATOR_BITMAP */
		/*	resource type from app file -- can be of any kind for which a */
		/*	translator is installed (TGA, etc) */
static	BBitmap * GetBitmap(
				const char * name,
				BTranslatorRoster * use = NULL);
		/*	Get bitmap - from app resource file only */
static	BBitmap * GetBitmap(
				uint32 type,
				int32 id,
				BTranslatorRoster * use = NULL);
static	BBitmap * GetBitmap(
				uint32 type,
				const char * name,
				BTranslatorRoster * use = NULL);
		/*	Get bitmap - from file only	*/
static	BBitmap * GetBitmapFile(
				const char * name,
				BTranslatorRoster * use = NULL);
		/*	Get bitmap - from open file (or BMemoryIO) */
static	BBitmap * GetBitmap(
				BPositionIO * stream,	/*	not NULL	*/
				BTranslatorRoster * use = NULL);

};

#endif /* _TRANSLATION_UTILS_H */

