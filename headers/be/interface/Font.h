/*******************************************************************************
/
/	File:			Font.h
/
/   Description:    BFont objects represent individual font styles.
/                   Global font cache and font info functions defined below.
/
/	Copyright 1997-98, Be Incorporated, All Rights Reserved
/
/******************************************************************************/

#ifndef _FONT_H
#define _FONT_H

#include <BeBuild.h>
#include <SupportDefs.h>
#include <InterfaceDefs.h>

/*----------------------------------------------------------------*/
/*----- BFont defines and structures -----------------------------*/

#define B_FONT_FAMILY_LENGTH 63
typedef char font_family[B_FONT_FAMILY_LENGTH + 1];
#define B_FONT_STYLE_LENGTH 63
typedef char font_style[B_FONT_STYLE_LENGTH + 1];

enum {
	B_CHAR_SPACING		= 0,
	B_STRING_SPACING	= 1,
	B_BITMAP_SPACING	= 2,
	B_FIXED_SPACING		= 3
};

enum font_direction {
	B_FONT_LEFT_TO_RIGHT = 0,
	B_FONT_RIGHT_TO_LEFT = 1
};

enum {
	B_DISABLE_ANTIALIASING = 0x00000001
};

enum {
	B_TRUNCATE_END       = 0,
	B_TRUNCATE_BEGINNING = 1,
	B_TRUNCATE_MIDDLE    = 2,
	B_TRUNCATE_SMART     = 3
};

enum {
	B_UNICODE_UTF8    = 0,
	B_ISO_8859_1      = 1,
	B_ISO_8859_2      = 2,
	B_ISO_8859_3      = 3,
	B_ISO_8859_4      = 4,
	B_ISO_8859_5      = 5,
	B_ISO_8859_6      = 6,
	B_ISO_8859_7      = 7,
	B_ISO_8859_8      = 8,
	B_ISO_8859_9      = 9,
	B_ISO_8859_10     = 10,
	B_MACINTOSH_ROMAN = 11
};

enum {
	B_SCREEN_FONT_CACHE      = 0x0001,
	B_PRINTING_FONT_CACHE    = 0x0002,
	B_DEFAULT_CACHE_SETTING  = 0x0004,
	B_APP_CACHE_SETTING      = 0x0008
};

enum {
	B_HAS_TUNED_FONT         = 0x0001,
	B_IS_FIXED               = 0x0002
};

struct edge_info {
	float	left;
	float	right;
};

struct font_height {
	float	ascent;
	float	descent;
	float	leading;
};

struct escapement_delta {
	float	nonspace;
	float	space;
};

struct font_cache_info {
    int32    sheared_font_penalty;
    int32    rotated_font_penalty;
	float    oversize_threshold;
	int32    oversize_penalty;
	int32    cache_size;
	float    spacing_size_threshold;
};

struct tuned_font_info {
	float    size;
	float    shear; 
	float    rotation;
	uint32   flags;
	uint16   face;
};

/*----------------------------------------------------------------*/
/*----- BFont class ----------------------------------------------*/

class BFont {
public:
						BFont();
						BFont(const BFont &font);	
						BFont(const BFont *font);			

		void			SetFamilyAndStyle(const font_family family, 
										  const font_style style);
		void			SetFamilyAndStyle(uint32 code);
		void			SetSize(float size);
		void			SetShear(float shear);
		void			SetRotation(float rotation);
		void			SetSpacing(uint8 spacing);
		void			SetEncoding(uint8 encoding);
		void			SetFace(uint16 face);
		void			SetFlags(uint32 flags);

		void			GetFamilyAndStyle(font_family *family,
										  font_style *style) const;
		uint32			FamilyAndStyle() const;
		float			Size() const;
		float			Shear() const;
		float			Rotation() const;
		uint8			Spacing() const;
		uint8			Encoding() const;
		uint16			Face() const;
		uint32			Flags() const;
		font_direction	Direction() const; 
		int32			CountTuned() const;
		void			GetTunedInfo(int32 index, tuned_font_info *info) const;

		void            GetTruncatedStrings(const char *stringArray[], 
											int32 numStrings, 
											uint32 mode,
											float width, 
											char *resultArray[]) const;

		float			StringWidth(const char *string) const;
		float			StringWidth(const char *string, int32 length) const;
		void			GetStringWidths(const char *stringArray[], 
										const int32 lengthArray[], 
										int32 numStrings, 
										float widthArray[]) const;

		void			GetEscapements(const char charArray[], 
									   int32 numChars,
									   float escapementArray[]) const;
		void			GetEscapements(const char charArray[], 
									   int32 numChars,
									   escapement_delta *delta, 
									   float escapementArray[]) const;
		void			GetEdges(const char charArray[], 
								 int32 numBytes,
								 edge_info edgeArray[]) const;
		void			GetHeight(font_height *height) const;
		
		BFont&			operator=(const BFont &font); 
		bool			operator==(const BFont &font) const;
		bool			operator!=(const BFont &font) const; 

		void			PrintToStream() const;
	
/*----- Private or reserved -----------------------------------------*/
private:

friend class BApplication;
friend class BView;
friend void _font_control_(BFont*, int32, void*);

		uint16			fFamilyID;
		uint16			fStyleID;
		float			fSize;
		float			fShear;
		float			fRotation;
		uint8			fSpacing;
		uint8			fEncoding;
		uint16			fFace;
		uint32			fFlags;
		font_height		fHeight;
		uint32			_reserved[3];

		void            SetPacket(void *packet) const;
		void            GetTruncatedStrings64(const char *stringArray[], 
											  int32 numStrings, 
											  uint32 mode,
											  float width, 
											  char *resultArray[]) const;
};

/*----------------------------------------------------------------*/
/*----- BFont related declarations -------------------------------*/

extern _IMPEXP_BE const BFont* be_plain_font;
extern _IMPEXP_BE const BFont* be_bold_font;
extern _IMPEXP_BE const BFont* be_fixed_font;

_IMPEXP_BE int32       count_font_families();
_IMPEXP_BE status_t    get_font_family(int32 index, font_family *name,
							uint32 *flags = NULL);
_IMPEXP_BE int32       count_font_styles(font_family name);
_IMPEXP_BE status_t    get_font_style(font_family family, int32 index,
							font_style *name, uint32 *flags = NULL);
_IMPEXP_BE bool        update_font_families(bool check_only);
_IMPEXP_BE status_t    get_font_cache_info(uint32 id, void  *set);
_IMPEXP_BE status_t    set_font_cache_info(uint32 id, void  *set);

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#endif /* _FONT_H */
