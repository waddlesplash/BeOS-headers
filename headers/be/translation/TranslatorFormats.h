//******************************************************************************
//
//      File:           TranslatorFormats.h
//
//      Description:    Defines for common "lowest common denominator" formats 
//                      used in the Translation Kit.
//
//      Copyright 1998, Be Incorporated, All Rights Reserved.
//      Copyright 1995-1997, Jon Watte
//
//******************************************************************************


#ifndef _TRANSLATOR_FORMATS_H
#define _TRANSLATOR_FORMATS_H


#if !defined(_SUPPORT_DEFS_H)
	#include <SupportDefs.h>
#endif	/* _SUPPORT_DEFS_H */
#if !defined(_INTERFACE_DEFS_H)
	#include <InterfaceDefs.h>
#endif	/* _INTERFACE_DEFS_H */

/*	extensions used in the extension BMessage. Use of these 	*/
/*	are described in the documentation.	*/

#define kCommentExtension		"/comment"
#define kTimeExtension			"/time"
#define kFrameExtension			"/frame"
#define kBitsRectExtension		"bits/Rect"
#define kBitsSpaceExtension		"bits/space"
#define kHeaderExtension		"/headerOnly"
#define kDataExtension			"/dataOnly"
#define kNoisChannelExtension	"nois/channel"
#define kNoisMonoExtension		"nois/mono"
#define kNoisMarkerExtension	"nois/marker"
#define kNoisLoopExtension		"nois/loop"


/*	For each data group, there is a "standard" format that	*/
/*	all translators should support.	*/
/*      These type codes are lower-case because they are already	*/
/*	established standards in the Be developer community.	*/
enum TranslatorGroups {
	B_TRANSLATOR_BITMAP			=	'bits',		/*	TranslatorBitmap	*/
	B_TRANSLATOR_PICTURE		=	'pict',		/*	BPicture data	*/
	B_TRANSLATOR_TEXT			=	'TEXT',		/*	B_ASCII_TYPE	*/
	B_TRANSLATOR_SOUND			=	'nois',		/*	TranslatorSound	*/
	B_TRANSLATOR_MIDI			=	'midi',		/*	standard MIDI	*/
	B_TRANSLATOR_MEDIA			=	'mhi!',		/*	a stream of stuff	*/
	B_TRANSLATOR_NONE			=	'none'
};
#define kAnyType 0


/*	This is the standard bitmap format	*/
/*	Note that data is always in big-endian format in the stream!	*/
struct TranslatorBitmap {
	uint32		magic;		/*	B_TRANSLATOR_BITMAP	*/
	BRect		bounds;
	uint32		rowBytes;
	color_space	colors;
	uint32		dataSize;
};	/*	data follows, padded to rowBytes	*/

/*	This is the standard sound format	*/
/*	Note that data is always in big-endian format in the stream!	*/
struct TranslatorSound {
	uint32		magic;		/*	B_TRANSLATOR_SOUND	*/
	uint32		channels;	/*	Left should always be first	*/
	float		sampleFreq;	/*	16 bit linear is assumed	*/
	uint32		numFrames;
};	/*	data follows	*/

#endif /* _TRANSLATOR_FORMATS_H	*/

