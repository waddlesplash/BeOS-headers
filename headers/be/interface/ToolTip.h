/***************************************************************************
//
//	File:			ToolTip.h
//
//	Description:	Support classes for showing tool tips.
//
//	Copyright 2000, Be Incorporated, All Rights Reserved.
//
***************************************************************************/

#ifndef _TOOL_TIP_H
#define _TOOL_TIP_H

#include <MessageFilter.h>
#include <Messenger.h>

#include <Font.h>
#include <GraphicsDefs.h>
#include <Rect.h>
#include <Point.h>

#include <Locker.h>
#include <String.h>

class BView;
namespace BPrivate {
class TipWindow;
}

// Information about how to display the tool tip.  Not needed unless
// you want to do something special besides "show my text outside of
// the view frame".

class BToolTipInfo {
public:
						BToolTipInfo();
virtual					~BToolTipInfo();
	
	// Set the text to be displayed by the tool tip.  This
	// must be a non-empty string.
		void			SetText(const char* text);
		const char*		Text() const;
	
	// Set the font to use for the tool tip, if you don't want
	// the default.
		void			SetFont(const BFont* font);
		const BFont*	Font() const;
	
	// Set the background color of the tool tip, if you don't
	// want the default.
		void			SetFillColor(rgb_color color);
		rgb_color		FillColor() const;
	
	// Set the text color of the tool tip, if you don't want the
	// default.
		void			SetTextColor(rgb_color color);
		rgb_color		TextColor() const;
	
	// Indicate whether this is an "inline" tool tip.  An inline
	// tip won't disappear when the mouse moves inside of it.
		void			SetInline(bool state);
		bool			Inline() const;
	
	// Set the text origin (left edge and baseline) relative
	// to the tool tip region.  In this mode, the tool tip will
	// be placed so that its text lines up with this point.
		void			SetOrigin(BPoint origin);
		void			ClearOrigin();
		bool			HasOrigin() const;
		BPoint			Origin() const;
	
private:
	/* FBC */
virtual	void			_ReservedToolTipInfo1();
virtual	void			_ReservedToolTipInfo2();
virtual	void			_ReservedToolTipInfo3();
virtual	void			_ReservedToolTipInfo4();
virtual	void			_ReservedToolTipInfo5();
virtual	void			_ReservedToolTipInfo6();
virtual	void			_ReservedToolTipInfo7();
virtual	void			_ReservedToolTipInfo8();
virtual	void			_ReservedToolTipInfo9();
virtual	void			_ReservedToolTipInfo10();
virtual	void			_ReservedToolTipInfo11();
virtual	void			_ReservedToolTipInfo12();
virtual	void			_ReservedToolTipInfo13();
virtual	void			_ReservedToolTipInfo14();
virtual	void			_ReservedToolTipInfo15();
virtual	void			_ReservedToolTipInfo16();
		uint32			_reservedToolTipInfo[16];
		
		BString			fText;
		BFont			fFont;
		rgb_color		fFillColor;
		rgb_color		fTextColor;
		BPoint			fOrigin;
		bool			fInline;
		bool			fHasOrigin;
	
	// Not implemented, for now.
		void			SetView(BView* view);
		BView*			View() const;
		BView*			DetachView();
		BView*			fView;
};

class BToolTip {
public:
						BToolTip();
virtual					~BToolTip();
	
	// Return the default BToolTip instance.
static	BToolTip*		Default();
	
	// Prepare to start showing a tip.  This is the point where
	// the cursor enters a screen area with a tool tip.  The
	// tool tip timer is started, and when it has elapsed a
	// B_REQUEST_TOOL_INFO message is sent to 'who' to get the
	// information for showing the tip.  All other methods are
	// keyed off the same 'who' target.
virtual	status_t		ShowTip(BMessenger who);
	
	// Update state based on cursor movement.  If 'who' is still
	// the shown tip (and the mouse has moved enough) this will
	// either restart the display timer or hide the tip, depending
	// on whether it is currently visible.
virtual	status_t		CursorMoved(BMessenger who,
									BPoint where, BPoint delta);
	
	// Make the tip visible.  These are usually called in response
	// to a B_REQUEST_TOOL_INFO message.  You should call
	// NewToolTipInfo() to get a new info object with default
	// values, make any changes you like, and hand that in to
	// SetToolTipInfo().  The latter will take care of deleting the
	// object.
	//
	// You can also call this without being in response to a
	// B_REQUEST_TOOL_INFO message, in which case the tool tip will
	// be made visible immediately.
virtual	BToolTipInfo*	NewToolTipInfo() const;
virtual	status_t		SetToolTipInfo(	BMessenger who,
										BRect region, BToolTipInfo* info);
	
	// Finish the tool tip for this target.  If it is currently
	// visible, it will be made hidden before going away.
virtual status_t		HideTip(BMessenger who);
	
	// Like above but hide immediately, do not pass go, do not
	// collect $200.
virtual	status_t		KillTip(BMessenger who);
	
	// Call this when your target object goes invalid, just to be
	// sure everything is cleaned up.
virtual	status_t		RemoveOwner(BMessenger who);
	
private:
		/* FBC */
virtual	void			_WatchMyToolTip1();
virtual	void			_WatchMyToolTip2();
virtual	void			_WatchMyToolTip3();
virtual	void			_WatchMyToolTip4();
virtual	void			_WatchMyToolTip5();
virtual	void			_WatchMyToolTip6();
virtual	void			_WatchMyToolTip7();
virtual	void			_WatchMyToolTip8();
virtual	void			_WatchMyToolTip9();
virtual	void			_WatchMyToolTip10();
virtual	void			_WatchMyToolTip11();
virtual	void			_WatchMyToolTip12();
virtual	void			_WatchMyToolTip13();
virtual	void			_WatchMyToolTip14();
virtual	void			_WatchMyToolTip15();
virtual	void			_WatchMyToolTip16();
		uint32			_watchMyData[8];
	
friend class BPrivate::TipWindow;
	
		BPrivate::TipWindow* Tip();
		void			WindowGone(BPrivate::TipWindow* w);
	
		BLocker			fAccess;
	
		BPrivate::TipWindow* fTip;
		BMessenger		fCurrentOwner;
};

#endif
