//******************************************************************************
//
//	File:		View.h
//
//	Description:	client view class.
//
//	Copyright 1992-94, Be Incorporated
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
#ifndef	_OBJECT_H
#include <support/Object.h>
#endif
#ifndef _MESSAGE_H
#include <app/Message.h>
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

#define SHIFT_KEY			0x00000001
#define ALT_KEY				0x00000002
#define CONTROL_KEY			0x00000004
#define CAPS_LOCK			0x00000008
#define SCROLL_LOCK			0x00000010
#define NUM_LOCK			0x00000020
#define LEFT_SHIFT_KEY		0x00000040
#define RIGHT_SHIFT_KEY		0x00000080
#define LEFT_ALT_KEY		0x00000100
#define RIGHT_ALT_KEY		0x00000200
#define LEFT_CONTROL_KEY	0x00000400
#define RIGHT_CONTROL_KEY	0x00000800

struct key_info
	{
	ulong	char_code;
	ulong	key_code;
	ulong	modifiers;
	uchar	key_states[16];
	};

enum {
	ENTERED_VIEW,
	INSIDE_VIEW,
	EXITED_VIEW
};

enum track_style {
	TRACK_WHOLE_RECT,
	TRACK_RECT_CORNER
};

//------------------------------------------------------------------------------

#define FONT_NAME_LENGTH 32
typedef char font_name[FONT_NAME_LENGTH + 1];

struct font_info
	{
		font_name name;
		short	size;
		short	shear;
		short	rotation;
		short	ascent;
		short	descent;
		short	leading;
	};

struct edge_info
	{
		short	left;
		short	right;
	};

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
       PULSE_NEEDED =		0x10000000	/* 28 */,
       BORDERED =		0x08000000	/* 27 */,
       FRAME_EVENTS =		0x04000000	/* 26 */,
       RESERVED3 =		0x02000000	/* 25 */,
       RESERVED4 =		0x01000000	/* 24 */,
       RESERVED5 =		0x00800000	/* 23 */,
       RESERVED6 =		0x00400000	/* 23 */,
       RESERVED7 =		0x00200000	/* 22 */ };

#define _RESIZE_MASK_ ~(FULL_UPDATE_ON_RESIZE|RESERVED1|WILL_DRAW|\
		 	PULSE_NEEDED|BORDERED|FRAME_EVENTS|RESERVED3|RESERVED4|\
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
class BPoint;
class BPolygon;

class BView : public BObject {
	DECLARE_CLASS_INFO(BObject);

public:
						BView(	BRect frame,
								const char *name,
								ulong resizeMask,
								ulong flags);
						BView();
virtual					~BView();

virtual	void			AttachedToWindow();

		const char		*Name() const;
		void			SetName(const char *name);
	
virtual	void			AddChild(BView *aView);
virtual	bool			RemoveChild(BView *childView);
		long			CountChildren() const;
		BView			*ChildAt(long index) const;
		bool			RemoveSelf();
virtual	void			MessageReceived(BMessage *an_event);

		BWindow			*Window() const;

virtual	void			Draw(BRect updateRect);
virtual	void			MouseDown(BPoint where);
virtual	void			MouseMoved(BPoint where, ulong code, BMessage *a_message);
virtual	void			WindowActivated(bool state);
virtual	void			KeyDown(ulong aKey);
virtual	void			Pulse();
virtual	void			FrameMoved(BPoint new_position);
virtual	void			FrameResized(long new_width, long new_height);

virtual	bool			MessageDropped(BMessage *aMessage);
	
		void			BeginRectTracking(BRect startRect,
										track_style style = TRACK_WHOLE_RECT);
		void			EndRectTracking();
	
		void			GetMouse(BPoint* location, ulong *buttons) const;
		void			GetKeys(key_info *info, bool CheckEventQueue);
		ulong			Modifiers() const;
		void			DragMessage(BMessage *aMessage, BRect dragRect);
		void			DragMessage(BMessage *aMessage,
									BImageBuffer *anImage,
									BPoint offset);
		void			DragMessage(BMessage *aMessage,
									BBitmap *anImage,
									BPoint offset);

		BView			*FindView(const char *name) const;
		BView			*Parent() const;
		BRect			Bounds() const;
		BRect			Frame() const;
		void			ConvertToScreen(BPoint* pt) const;
		void			ConvertFromScreen(BPoint* pt) const;
		void			ConvertToScreen(BRect *r) const;
		void			ConvertFromScreen(BRect *r) const;
		void			ConvertToParent(BPoint *pt) const;
		void			ConvertFromParent(BPoint *pt) const;
		void			ConvertToParent(BRect *r) const;
		void			ConvertFromParent(BRect *r) const;
		BPoint			LeftTop() const;
		void			GetClippingRegion(BRegion*) const;
virtual	void			SetClippingRegion(BRegion*);

virtual	void			SetDrawingMode(drawing_mode mode);
		drawing_mode 	DrawingMode() const;

virtual	void			SetPenSize(long size);
		long			PenSize();

virtual	void			SetFrontColor(rgb_color a_color);
		void			SetFrontColor(uchar r, uchar g, uchar b, uchar a = 0);
		rgb_color		FrontColor();

virtual	void			SetBackColor(rgb_color a_color);
		void			SetBackColor(uchar r, uchar g, uchar b, uchar a = 0);
		rgb_color		BackColor();

		void			MovePenTo(BPoint pt);
		void			MovePenTo(long x, long y);
		void			MovePenBy(long x, long y);
		BPoint			PenLocation();
		void			StrokeLine(	BPoint toPt,
									const pattern *p = &solid_front);
		void			StrokeLine(	BPoint pt0,
									BPoint pt1,
									const pattern *p = &solid_front);
		void			BeginLineArray(const pattern *p = &solid_front);
		void			AddLine(BPoint pt0, BPoint pt1);
		void			EndLineArray();
	
		void			StrokePolygon(	const BPolygon *aPolygon,
										const pattern *p = &solid_front);
		void			StrokePolygon(	const BPoint *ptArray,
										long numPts,
										const pattern *p = &solid_front);
		void			StrokePolygon(	const BPoint *ptArray,
										long numPts,
										BRect bounds,
										const pattern *p = &solid_front);
		void			FillPolygon(const BPolygon *aPolygon,
									const pattern *p = &solid_front);
		void			FillPolygon(const BPoint *ptArray,
									long numPts,
									const pattern *p = &solid_front);
		void			FillPolygon(const BPoint *ptArray,
									long numPts,
									BRect bounds,
									const pattern *p = &solid_front);
	
		void			StrokeTriangle(	BPoint pt1,
										BPoint pt2,
										BPoint pt3,
										BRect bounds,
										const pattern *p = &solid_front);
		void			StrokeTriangle(	BPoint pt1,
										BPoint pt2,
										BPoint pt3,
										const pattern *p = &solid_front);
		void			FillTriangle(	BPoint pt1,
										BPoint pt2,
										BPoint pt3,
										const pattern *p = &solid_front);
		void			FillTriangle(	BPoint pt1,
										BPoint pt2,
										BPoint pt3,
										BRect bounds,
										const pattern *p = &solid_front);

		void			StrokeRect(BRect r, const pattern *p = &solid_front);
		void			FillRect(BRect r, const pattern *p = &solid_front);
		void			InvertRect(BRect r);

		void			StrokeRoundRect(BRect r,
										long xRadius,
										long yRadius,
										const pattern *p = &solid_front);
		void			FillRoundRect(	BRect r,
										long xRadius,
										long yRadius,
										const pattern *p = &solid_front);

		void			StrokeEllipse(	BPoint center,
										long xRadius,
										long yRadius,
										const pattern *p = &solid_front);
		void			StrokeEllipse(BRect r, const pattern *p = &solid_front);
		void			FillEllipse(BPoint center,
									long xRadius,
									long yRadius,
									const pattern *p = &solid_front);
		void			FillEllipse(BRect r, const pattern *p = &solid_front);
				
		void			StrokeArc(	BPoint center,
									long xRadius,
									long yRadius,
									long start_angle,
									long arc_angle,
									const pattern *p = &solid_front);
		void			StrokeArc(	BRect r,
									long start_angle,
									long arc_angle,
									const pattern *p = &solid_front);
		void			FillArc(BPoint center,
								long xRadius,
								long yRadius,
								long start_angle,
								long arc_angle,
								const pattern *p = &solid_front);
		void			FillArc(BRect r,
								long start_angle,
								long arc_angle,
								const pattern *p = &solid_front);
			
		void			CopyBits(BRect src, BRect dst);
		void			DrawBitmap(	const BBitmap *aBitmap,
									BRect srcRect,
									BRect dstRect);
		void			DrawBitmap(	const BImageBuffer *anImage,
									BRect srcRect,
									BRect dstRect);
		void			DrawBitmap(const BBitmap *aBitmap, BPoint where);
		void			DrawBitmap(const BImageBuffer *anImage, BPoint where);
		void			DrawBitmap(const BBitmap *aBitmap, BRect dstRect);
		void			DrawBitmap(const BImageBuffer *anImage, BRect dstRect);
	
virtual void			SetFontName(const char* name);
virtual void			SetFontSize(long pointSize);
virtual void			SetFontShear(long degrees);
virtual void			SetFontRotation(long degrees);
		void			GetFontInfo(font_info *info) const;
		long			StringWidth(const char *aString) const;
		long			StringWidth(const char *aString, long length) const;
		void			GetCharEscapements(	char charArray[],
											long numChars,
											short escapementArray[],
											float* escapementUnits) const;
		void			GetCharEdges(	char charArray[],
										long numChars,
										edge_info edgeArray[]) const;
		long			CountFonts() const;
		void			GetFontName(long index, font_name* name) const;
		void			DrawChar(char aChar);
		void			DrawString(const char *aString);
		void			DrawString(const char *aString, long length);

		void			Invalidate(BRect invalRect);
		void			Invalidate();

virtual	void			SetFlags(ulong flags);
		ulong			Flags() const;
virtual	void			SetResizingMode(ulong mode);
		ulong			ResizingMode() const;
		void			MoveBy(long dh, long dv);
		void			MoveTo(BPoint where);
		void			MoveTo(long x, long y);
		void			ResizeBy(long dh, long dv);
		void			ResizeTo(long width, long height);
		void			ScrollBy(long dh, long dv);
		void			ScrollTo(BPoint where);
		void			ScrollTo(long x, long y);
virtual	void			MakeFocus(bool focusState = TRUE);
		bool			IsFocus() const;
	
virtual	void			Show();
virtual	void			Hide();
		bool			IsHidden() const;
	
		void			Flush() const;
		void			Sync() const;

		bool			LoadFromResource(long resID, char *resBuf = (char *) 0);
virtual long			ResourceDataLength() const;
virtual void			GetResourceData(void *buf) const;
virtual void			SetResourceData(const void *buf, long len);

// ------------------------------------------------------------------

private:

friend class BListView;
friend class BScrollBar;
friend class BRadioButton;
friend class BWindow;
friend class BImageBuffer;

		long		Token()	const;
		bool		SaveAsResource(long resID);
		void		UpdateFrame();
		void		StrokeLineToNoPat(BPoint pt);
		void		StrokeRectNoPat(BRect r);
		bool		remove_from_list(BView *a_view);
		bool		remove_self();
		bool		do_owner_check() const;
		void		set_owner(BWindow *the_owner);
		void		do_activate(long msg);
		void		end_draw();
/*		void		flush() const;*/
		void		check_lock() const;
		void		lock();
		void		unlock();
		void		movesize(long code, long h, long v);
		void		handle_tick();
		char		*test_area(long length);

		long		server_token;
		long		client_token;
		BRect		f_bound;
		long		f_type;
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

inline ulong	BView::Flags() const
	{ return(f_type & _RESIZE_MASK_); }

inline ulong	BView::ResizingMode() const
	{ return(f_type & ~(_RESIZE_MASK_)); }

//------------------------------------------------------------------------------

#endif
