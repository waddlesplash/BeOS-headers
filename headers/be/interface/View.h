//******************************************************************************
//
//	File:		View.h
//
//	Description:	client view class.
//
//	Written by:	Benoit Schillings
//
//	Copyright 1992-93, Be Incorporated
//
//******************************************************************************

#ifndef	_VIEW_H
#define	_VIEW_H

#ifndef _INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef	_RECT_H
#include "Rect.h"
#endif
#ifndef _EVENT_H
#include "Event.h"
#endif
#ifndef	_OBJECT_H
#include <sys/Object.h>
#endif

#define SHIFT_KEY		0x00000001
#define ALT_KEY			0x00000002
#define CONTROL_KEY		0x00000004

enum {
	ENTERED_VIEW,
	INSIDE_VIEW,
	EXITED_VIEW
};

//------------------------------------------------------------------------------

#define FONT_NAME_LENGTH (32 + 1)
typedef char font_name[FONT_NAME_LENGTH];

typedef struct
	{
		font_name name;
		short	size;
		short	shear;
		short	rotation;
		short	ascent;
		short	descent;
		short	leading;
	} font_info;

/*----------------------------------------------------------------*/

enum { NORMAL_VIEW, MENUBAR_VIEW, CHECK_VIEW, SCROLLBAR_VIEW };
 
/*----------------------------------------------------------------*/

/*
** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**
**  IF YOU CHANGE THESE BIT FLAGS YOU MUST UPDATE _RESIZE_MASK_
**
**	If you don't, bad things will happen.
**
** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

enum { FULL_UPDATE_ON_RESIZE =	0x80000000	/* 31 */,
       RESERVED1 =		0x40000000	/* 30 */,
       WILL_DRAW =		0x20000000	/* 29 */,	// ## temporary
       TICKS_NEEDED =		0x10000000	/* 28 */,
       BORDERED =		0x08000000	/* 27 */,
       FRAME_EVENTS =		0x04000000	/* 26 */,
       RESERVED3 =		0x02000000	/* 25 */,
       RESERVED4 =		0x01000000	/* 24 */,
       RESERVED5 =		0x00800000	/* 23 */,
       RESERVED6 =		0x00400000	/* 23 */,
       RESERVED7 =		0x00200000	/* 22 */ };

#define _RESIZE_MASK_ ~(FULL_UPDATE_ON_RESIZE|RESERVED1|WILL_DRAW|\
		 	TICKS_NEEDED|BORDERED|FRAME_EVENTS|RESERVED3|RESERVED4|\
			RESERVED5|RESERVED6|RESERVED7)

//extern const long FOLLOW_LEFT_TOP;
//extern const long FOLLOW_ALL_SIDES;
//extern const long FOLLOW_LEFT_TOP_RIGHT;
//extern const long FOLLOW_LEFT_TOP_BOTTOM;
//extern const long FOLLOW_RIGHT_BOTTOM;
//extern const long FOLLOW_TOP_RIGHT;
//extern const long FOLLOW_LEFT_RIGHT_BOTTOM;
//extern const long FOLLOW_TOP_RIGHT_BOTTOM;
//extern const long FOLLOW_LEFT_BOTTOM;
//extern const long FOLLOW_NONE;

enum { VIEW_LEFT = 2L,
       VIEW_TOP = 1L,
       VIEW_RIGHT = 4L,
       VIEW_BOTTOM = 3L };

inline long _rule_(long r1, long r2, long r3, long r4)
{ return ((r1 << 18) | (r2 << 12) | (r3 << 6) | r4); };

#define FOLLOW_LEFT_TOP  _rule_(VIEW_TOP, VIEW_LEFT, VIEW_TOP, VIEW_LEFT)
#define FOLLOW_ALL_SIDES  _rule_(VIEW_TOP, VIEW_LEFT, VIEW_BOTTOM, VIEW_RIGHT)
#define FOLLOW_LEFT_TOP_RIGHT  _rule_(VIEW_TOP, VIEW_LEFT, VIEW_TOP, VIEW_RIGHT)
#define FOLLOW_LEFT_TOP_BOTTOM  _rule_(VIEW_TOP, VIEW_LEFT, VIEW_BOTTOM, VIEW_LEFT)
#define FOLLOW_RIGHT_BOTTOM  _rule_(VIEW_BOTTOM, VIEW_RIGHT, VIEW_BOTTOM, VIEW_RIGHT)
#define FOLLOW_TOP_RIGHT  _rule_(VIEW_TOP, VIEW_RIGHT, VIEW_TOP, VIEW_RIGHT)
#define FOLLOW_LEFT_RIGHT_BOTTOM  _rule_(VIEW_BOTTOM, VIEW_LEFT, VIEW_BOTTOM, VIEW_RIGHT)
#define FOLLOW_TOP_RIGHT_BOTTOM  _rule_(VIEW_TOP, VIEW_RIGHT, VIEW_BOTTOM, VIEW_RIGHT)
#define FOLLOW_LEFT_BOTTOM  _rule_(VIEW_BOTTOM, VIEW_LEFT, VIEW_BOTTOM, VIEW_LEFT)
#define FOLLOW_NONE 0

//------------------------------------------------------------------------------

class BBitmap;
class BWindow;
class BImageBuffer;
class BRegion;
class BParcel;
class BPoint;
class BPolygon;

class BView : public BObject {

public:
			BView(const BRect *frame, char *name, ulong resizeMask,
			     ulong flags);
			BView();
virtual			~BView();
virtual	void		AttachedToWindow();
virtual	char		*ClassName();

	long		Token();
	char		*Name();
	void		SetName(char *name);
	
	void		AddChild(BView *aView);
	bool		RemoveChild(BView *childView);
	bool		RemoveSelf();
virtual	void		CommandReceived(BCommandEvent *an_event);

	BWindow		*Window();

virtual	void		Draw(BRect *updateRect);
virtual	void		MouseDown(BPoint where);
virtual	void		MouseMoved(BPoint where, ulong code, bool has_parcel);
virtual	void		WindowActivated(bool state);
virtual	void		KeyDown(ulong aKey);
virtual	void		Tick();
	void		SetTicksNeeded(bool state);
virtual	void		FrameMoved(BPoint new_position);
virtual	void		FrameResized(long new_width, long new_height);

virtual	bool		ParcelDropped(BParcel *aParcel);

	void		BeginRectTracking(BRect *startRect);
	void		EndRectTracking();
	
	void		GetMouse(BPoint* location, ulong *buttons);
	ulong		ModifierKeys();
	void		DragParcel(BParcel *aParcel, BRect *dragRect);
	void		DragParcel(BParcel *aParcel, BImageBuffer *anImage, BPoint offset);
	void		DragParcel(BParcel *aParcel, BBitmap *anImage, BPoint offset);

	BView		*FindView(char *name);
	BView		*Parent();
	void		GetBounds(BRect *r);
	void		GetFrame(BRect *r);
	void		ConvertToScreen(BPoint* pt);
	void		ConvertFromScreen(BPoint* pt);
	void		ConvertToScreen(BRect *r);
	void		ConvertFromScreen(BRect *r);
	void		ConvertToParent(BPoint *pt);
	void		ConvertFromParent(BPoint *pt);
	void		ConvertToParent(BRect *r);
	void		ConvertFromParent(BRect *r);
	BPoint		LeftTop();
	void		GetClippingRegion(BRegion*);

	void		SetDrawingMode(drawing_mode mode);
	drawing_mode 	DrawingMode();
	void		SetPenSize(long size);
	void		SetFrontColor(rgb_color a_color);
	void		SetFrontColor(uchar r, uchar g, uchar b, uchar a = 0);
	void		SetBackColor(rgb_color a_color);
	void		SetBackColor(uchar r, uchar g, uchar b, uchar a = 0);

	void		MovePenTo(BPoint pt);
	void		MovePenTo(long x, long y);
	void		MovePenBy(long x, long y);
	void		StrokeLine(BPoint toPt, const pattern *p = &solid_front);
	void		StrokeLine(BPoint pt0, BPoint pt1, const pattern *p = &solid_front);
	void		BeginLineArray(const pattern *p = &solid_front);
	void		AddLine(BPoint pt0, BPoint pt1);
	void		EndLineArray();
	
	void		StrokePolygon(BPolygon *aPolygon, const pattern *p = &solid_front);
	void		StrokePolygon(BPoint *ptArray, long numPts, BRect *bounds = NIL, const pattern *p = &solid_front);
	void		FillPolygon(BPolygon *aPolygon, const pattern *p = &solid_front);
	void		FillPolygon(BPoint *ptArray, long numPts, BRect *bounds = NIL, const pattern *p = &solid_front);

	void		StrokeTriangle(BPoint pt1, BPoint pt2, BPoint pt3, BRect *bounds = NIL, const pattern *p = &solid_front);
	void		FillTriangle(BPoint pt1, BPoint pt2, BPoint pt3, BRect *bounds = NIL, const pattern *p = &solid_front);

	void		StrokeRect(BRect *r, const pattern *p = &solid_front);
	void		FillRect(BRect *r, const pattern *p = &solid_front);
	void		InvertRect(BRect *r);

	void		StrokeEllipse(BPoint center, long xRadius, long yRadius, const pattern *p = &solid_front);
	void		StrokeEllipse(BRect *r, const pattern *p = &solid_front);
	void		FillEllipse(BPoint center, long xRadius, long yRadius, const pattern *p = &solid_front);
	void		FillEllipse(BRect *r, const pattern *p = &solid_front);
		
	void		CopyBits(BRect *src, BRect *dst);
	void		DrawBitmap(BBitmap *aBitmap, BRect *srcRect, BRect *dstRect);
	void		DrawBitmap(BImageBuffer *anImage, BRect *srcRect, BRect *dstRect);
	void		DrawBitmap(BBitmap *aBitmap, BPoint where);
	void		DrawBitmap(BImageBuffer *anImage, BPoint where);
	void		DrawBitmap(BBitmap *aBitmap, BRect *dstRect);
	void		DrawBitmap(BImageBuffer *anImage, BRect *dstRect);

virtual void		SetFontName(const char* name);
virtual void		SetFontSize(long pointSize);
virtual void		SetFontShear(long degrees);
virtual void		SetFontRotation(long degrees);
	void		DrawChar(char aChar);
	void		DrawString(const char *aString);
	void		DrawString(const char *aString, long length);
	long		StringWidth(char *aString);
	long		StringWidth(char *aString, long length);
	void		GetFontInfo(font_info*);
	long		CountFonts();
	void		GetFontName(long index, font_name* name);

	void		Invalidate(BRect * invalRect);
	void		Invalidate();

	void		SetFlags(ulong flags);
	ulong		Flags();
	void		SetResizingMode(ulong mode);
	ulong		ResizingMode();
	void		MoveBy(long dh, long dv);
	void		MoveTo(BPoint where);
	void		MoveTo(long x, long y);
	void		ResizeBy(long dh, long dv);
	void		ResizeTo(long width, long height);
	void		ScrollBy(long dh, long dv);
	void		ScrollTo(BPoint where);
	void		ScrollTo(long x, long y);
virtual	void		MakeFocus(bool focusState = TRUE);
	bool		IsFocus();

	void		Show();
	void		Hide();
	bool		IsHidden();
	
	void		Flush();
	void		Sync();

	bool		LoadFromResource(long resID, char *resBuf = (char *) 0);
virtual long		ResourceDataLength();
virtual void		GetResourceData(void *buf);
virtual void		SetResourceData(void *buf, long len);

//------------------------------------------------------------------------------

friend class BListView;
friend class BScrollBar;
friend class BScrollView;
friend class BRadioButton;
friend class EditView;
friend class BWindow;
friend class BImageBuffer;
friend class TMenuBar;
friend class TMenu;
friend class PropWindow;

private:
	long		GetID(void) { return id; };
	void		SetID(long newID) { id = newID; };
	bool		SaveAsResource(long resID);
	void		UpdateFrame();
	void		StrokeLineToNoPat(BPoint pt);
	void		StrokeRectNoPat(BRect *r);
	bool		remove_from_list(BView *a_view);
	bool		do_owner_check();
	void		set_owner(BWindow *the_owner);
	void		do_activate(long msg);
	void		end_draw();
	void		flush();
	void		lock();
	void		unlock();
	void		movesize(long code, long h, long v);
	void		handle_tick();
	char		*test_area(long length);

	long		server_token;
	long		client_token;

	BRect		f_bound;
	long		f_type;
	long		tview_class;
	long		origin_h;
	long		origin_v;

	char*		view_name;

	BWindow*	owner;
	BView*		parent;
	BView*		next_sibling;
	BView*		first_child;

	short 		fShowLevel;

	long		id;
	long		resType;
};

inline char		*BView::ClassName() { return "BView"; };
inline long		BView::Token() { return server_token; };
inline ulong		BView::Flags() { return(f_type & _RESIZE_MASK_); };
inline ulong		BView::ResizingMode() { return(f_type & ~(_RESIZE_MASK_)); };

//------------------------------------------------------------------------------

#endif
