//******************************************************************************
//
//	File:		Event.h
//
//	Description:	Event manager object.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1993, Be Incorporated
//
//******************************************************************************

#ifndef	_EVENT_H
#define	_EVENT_H

#ifndef	_PARCEL_H
#include "Parcel.h"
#endif
#ifndef	_OBJECT_H
#include <sys/Object.h>
#endif

class	BView;

//------------------------------------------------------------------------------

class	BEvent	: BObject {
public:
	long		what;
	ulong		when;
	long		context;

			BEvent();
virtual			~BEvent();

virtual	void		PrintToStream();

private:
friend	class	BEventQueue;
	BEvent		*link;
};

//------------------------------------------------------------------------------

class	BCommandEvent	: public BEvent {
public:
	BView		*target;
	long		data[5];

			BCommandEvent();
virtual			~BCommandEvent();
};

//------------------------------------------------------------------------------

class	BSysEvent : public BEvent {
public:
		union {
			struct
			{
				BView	*who;
				long	x;
				long	y;
				ulong	buttons;
				ulong	sequence;
			} mouseDown;
//-------
			struct
			{
				BView	*who;
				long	x;
				long	y;
				ulong	buttons;
			} mouseUp;
//-------
			struct
			{
				BView	*who;
				long	value;
			} valueChanged;
//-------
			struct
			{
				ulong	key;
				ulong	modifiers;
			} keyDown;
//-------
			struct
			{
				ulong	key;
				ulong	modifiers;
			} keyUp;
//-------
			struct
			{
				long	width;
				long	height;
			} windowResized;
//-------
			struct
			{
				long	x;
				long	y;
			} windowMoved;
//-------
			struct
			{
				BView	*who;
				long	width;
				long	height;
			} viewResized;
//-------
			struct
			{
				BView	*who;
				long	x;
				long	y;
			} viewMoved;
//-------
			struct
			{
				bool	isActive;
			} activation;
//-------
			struct
			{
				bool	isForced;
			} closeRequested;
//-------
			struct 
			{
				BParcel	*parcel;
				long	x;
				long	y;
			} parcelDropped;
//-------
			struct 
			{
				long	x;
				long	y;
				ulong	area;
				bool	hasParcel;
			} mouseMoved;
//-------
			struct
			{
				long		width;
				long		height;
				color_space	mode;
			} screenChanged;
//-------
			struct
			{
			} tick;
//-------
			struct
			{
				long	data[13];
			} _default_;
		};

	void		BSysEvent();
virtual	void		PrintToStream();
};

#endif
