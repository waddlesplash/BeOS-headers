//******************************************************************************
//
//	File:		View.h
//
//	Description:	client view class.
//
//	Copyright 1992-96, Be Incorporated
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
#ifndef	_HANDLER_H
#include <Handler.h>
#endif
#ifndef _MESSAGE_H
#include <Message.h>
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif
#ifndef _CLIPBOARD_H
#include <Clipboard.h>
#endif
#ifndef	_PICTURE_H
#include <Picture.h>
#endif

struct key_info
	{
	ulong	char_code;
	ulong	key_code;
	ulong	modifiers;
	uchar	key_states[16];
	};

enum {
	B_PRIMARY_MOUSE_BUTTON = 0x01,
	B_SECONDARY_MOUSE_BUTTON = 0x02,
	B_TERTIARY_MOUSE_BUTTON = 0x04
};

enum {
	B_ENTERED_VIEW,
	B_INSIDE_VIEW,
	B_EXITED_VIEW
};

enum {
	B_TRACK_WHOLE_RECT,
	B_TRACK_RECT_CORNER
};

//------------------------------------------------------------------------------


struct font_info
	{
		font_name name;
		float	size;
		float	shear;
		float	rotation;
		float	ascent;
		float	descent;
		float	leading;
	};

struct edge_info
	{
		float	left;
		float	right;
	};

/*----------------------------------------------------------------*/

enum { B_FULL_UPDATE_ON_RESIZE =	0x80000000	/* 31 */,
       _B_RESERVED1_ =				0x40000000	/* 30 */,
       B_WILL_DRAW =				0x20000000	/* 29 */,
       B_PULSE_NEEDED =				0x10000000	/* 28 */,
       B_BORDERED =					0x08000000	/* 27 */,
       B_FRAME_EVENTS =				0x04000000	/* 26 */,
       B_NAVIGABLE =				0x02000000	/* 25 */,
       _B_RESERVED4_ =				0x01000000	/* 24 */,
       _B_RESERVED5_ =				0x00800000	/* 23 */,
       _B_RESERVED6_ =				0x00400000	/* 23 */,
       _B_RESERVED7_ =				0x00200000	/* 22 */ };

#define _RESIZE_MASK_ ~(B_FULL_UPDATE_ON_RESIZE|_B_RESERVED1_|B_WILL_DRAW|\
		 	B_PULSE_NEEDED|B_BORDERED|B_FRAME_EVENTS|B_NAVIGABLE|\
			_B_RESERVED4_|_B_RESERVED5_|_B_RESERVED6_|_B_RESERVED7_)

enum {
	_VIEW_TOP_ = 1L,
	_VIEW_LEFT_ = 2L,
	_VIEW_BOTTOM_ = 3L,
	_VIEW_RIGHT_ = 4L,
	_VIEW_CENTER_ = 5L
};

// the FOLLOW flags take 16 bits in total
inline long _rule_(long r1, long r2, long r3, long r4)
	{ return ((r1 << 12) | (r2 << 8) | (r3 << 4) | r4); };

#define B_FOLLOW_NONE 0
#define B_FOLLOW_ALL_SIDES		_rule_(_VIEW_TOP_, _VIEW_LEFT_, _VIEW_BOTTOM_,\
										_VIEW_RIGHT_)
#define B_FOLLOW_ALL  			B_FOLLOW_ALL_SIDES

#define B_FOLLOW_LEFT			_rule_(0, _VIEW_LEFT_, 0, _VIEW_LEFT_)
#define B_FOLLOW_RIGHT			_rule_(0, _VIEW_RIGHT_, 0, _VIEW_RIGHT_)
#define B_FOLLOW_LEFT_RIGHT		_rule_(0, _VIEW_LEFT_, 0, _VIEW_RIGHT_)
#define B_FOLLOW_H_CENTER		_rule_(0, _VIEW_CENTER_, 0, _VIEW_CENTER_)

#define B_FOLLOW_TOP			_rule_(_VIEW_TOP_, 0, _VIEW_TOP_, 0)
#define B_FOLLOW_BOTTOM			_rule_(_VIEW_BOTTOM_, 0, _VIEW_BOTTOM_, 0)
#define B_FOLLOW_TOP_BOTTOM		_rule_(_VIEW_TOP_, 0, _VIEW_BOTTOM_, 0)
#define B_FOLLOW_V_CENTER		_rule_(_VIEW_CENTER_, 0, _VIEW_CENTER_, 0)

//------------------------------------------------------------------------------

class BWindow;
class BBitmap;
class BRegion;
class BPoint;
class BPolygon;
class BScrollBar;
struct _view_attr_;
struct _array_data_;
struct _array_hdr_;

class BView : public BHandler {

public:
						BView(	BRect frame,
								const char *name,
								ulong resizeMask,
								ulong flags);
virtual					~BView();

virtual	void			AttachedToWindow();
virtual	void			AllAttached();
virtual	void			DetachedFromWindow();
virtual	void			AllDetached();

virtual	void			AddChild(BView *aView);
virtual	bool			RemoveChild(BView *childView);
		long			CountChildren() const;
		BView			*ChildAt(long index) const;
		BView			*NextSibling() const;
		BView			*PreviousSibling() const;
		bool			RemoveSelf();

		BWindow			*Window() const;

virtual	void			Draw(BRect updateRect);
virtual	void			MouseDown(BPoint where);
virtual	void			MouseMoved(	BPoint where,
									ulong code,
									BMessage *a_message);
virtual	void			WindowActivated(bool state);
virtual	void			KeyDown(ulong aKey);
virtual	void			Pulse();
virtual	void			FrameMoved(BPoint new_position);
virtual	void			FrameResized(float new_width, float new_height);

		void			BeginRectTracking(	BRect startRect,
											ulong style = B_TRACK_WHOLE_RECT);
		void			EndRectTracking();
	
		void			GetMouse(	BPoint* location,
									ulong *buttons,
									bool checkMessageQueue = TRUE) const;
		long			GetKeys(key_info *info, bool checkMessageQueue);
		void			DragMessage(BMessage *aMessage,
									BRect dragRect,
									BHandler *reply_to = NULL);
		void			DragMessage(BMessage *aMessage,
									BBitmap *anImage,
									BPoint offset,
									BHandler *reply_to = NULL);

		BView			*FindView(const char *name) const;
		BView			*Parent() const;
		BRect			Bounds() const;
		BRect			Frame() const;
		void			ConvertToScreen(BPoint* pt) const;
		BPoint			ConvertToScreen(BPoint pt) const;
		void			ConvertFromScreen(BPoint* pt) const;
		BPoint			ConvertFromScreen(BPoint pt) const;
		void			ConvertToScreen(BRect *r) const;
		BRect			ConvertToScreen(BRect r) const;
		void			ConvertFromScreen(BRect *r) const;
		BRect			ConvertFromScreen(BRect r) const;
		void			ConvertToParent(BPoint *pt) const;
		BPoint			ConvertToParent(BPoint pt) const;
		void			ConvertFromParent(BPoint *pt) const;
		BPoint			ConvertFromParent(BPoint pt) const;
		void			ConvertToParent(BRect *r) const;
		BRect			ConvertToParent(BRect r) const;
		void			ConvertFromParent(BRect *r) const;
		BRect			ConvertFromParent(BRect r) const;
		BPoint			LeftTop() const;
		void			GetClippingRegion(BRegion *region) const;
virtual	void			ConstrainClippingRegion(BRegion *region);

virtual	void			SetDrawingMode(drawing_mode mode);
		drawing_mode 	DrawingMode() const;

virtual	void			SetPenSize(float size);
		float			PenSize() const;

virtual	void			SetViewColor(rgb_color c);
		void			SetViewColor(uchar r, uchar g, uchar b, uchar a = 0);
		rgb_color		ViewColor() const;

virtual	void			SetHighColor(rgb_color a_color);
		void			SetHighColor(uchar r, uchar g, uchar b, uchar a = 0);
		rgb_color		HighColor() const;

virtual	void			SetLowColor(rgb_color a_color);
		void			SetLowColor(uchar r, uchar g, uchar b, uchar a = 0);
		rgb_color		LowColor() const;

		void			MovePenTo(BPoint pt);
		void			MovePenTo(float x, float y);
		void			MovePenBy(float x, float y);
		BPoint			PenLocation() const;
		void			StrokeLine(	BPoint toPt,
									pattern p = B_SOLID_HIGH);
		void			StrokeLine(	BPoint pt0,
									BPoint pt1,
									pattern p = B_SOLID_HIGH);
		void			BeginLineArray(long count);
		void			AddLine(BPoint pt0, BPoint pt1, rgb_color col);
		void			EndLineArray();
	
		void			StrokePolygon(	const BPolygon *aPolygon,
									    bool  closed = TRUE,
										pattern p = B_SOLID_HIGH);
		void			StrokePolygon(	const BPoint *ptArray,
										long numPts,
									    bool  closed = TRUE,
										pattern p = B_SOLID_HIGH);
		void			StrokePolygon(	const BPoint *ptArray,
										long numPts,
										BRect bounds,
									    bool  closed = TRUE,
										pattern p = B_SOLID_HIGH);
		void			FillPolygon(const BPolygon *aPolygon,
									pattern p = B_SOLID_HIGH);
		void			FillPolygon(const BPoint *ptArray,
									long numPts,
									pattern p = B_SOLID_HIGH);
		void			FillPolygon(const BPoint *ptArray,
									long numPts,
									BRect bounds,
									pattern p = B_SOLID_HIGH);
	
		void			StrokeTriangle(	BPoint pt1,
										BPoint pt2,
										BPoint pt3,
										BRect bounds,
										pattern p = B_SOLID_HIGH);
		void			StrokeTriangle(	BPoint pt1,
										BPoint pt2,
										BPoint pt3,
										pattern p = B_SOLID_HIGH);
		void			FillTriangle(	BPoint pt1,
										BPoint pt2,
										BPoint pt3,
										pattern p = B_SOLID_HIGH);
		void			FillTriangle(	BPoint pt1,
										BPoint pt2,
										BPoint pt3,
										BRect bounds,
										pattern p = B_SOLID_HIGH);

		void			StrokeRect(BRect r, pattern p = B_SOLID_HIGH);
		void			FillRect(BRect r, pattern p = B_SOLID_HIGH);
		void			InvertRect(BRect r);

		void			StrokeRoundRect(BRect r,
										float xRadius,
										float yRadius,
										pattern p = B_SOLID_HIGH);
		void			FillRoundRect(	BRect r,
										float xRadius,
										float yRadius,
										pattern p = B_SOLID_HIGH);

		void			StrokeEllipse(	BPoint center,
										float xRadius,
										float yRadius,
										pattern p = B_SOLID_HIGH);
		void			StrokeEllipse(BRect r, pattern p = B_SOLID_HIGH);
		void			FillEllipse(BPoint center,
									float xRadius,
									float yRadius,
									pattern p = B_SOLID_HIGH);
		void			FillEllipse(BRect r, pattern p = B_SOLID_HIGH);
				
		void			StrokeArc(	BPoint center,
									float xRadius,
									float yRadius,
									float start_angle,
									float arc_angle,
									pattern p = B_SOLID_HIGH);
		void			StrokeArc(	BRect r,
									float start_angle,
									float arc_angle,
									pattern p = B_SOLID_HIGH);
		void			FillArc(BPoint center,
								float xRadius,
								float yRadius,
								float start_angle,
								float arc_angle,
								pattern p = B_SOLID_HIGH);
		void			FillArc(BRect r,
								float start_angle,
								float arc_angle,
								pattern p = B_SOLID_HIGH);
			
		void			CopyBits(BRect src, BRect dst);
		void			DrawBitmapAsync(	const BBitmap *aBitmap,
											BRect srcRect,
											BRect dstRect);
		void			DrawBitmapAsync(const BBitmap *aBitmap);
		void			DrawBitmapAsync(const BBitmap *aBitmap, BPoint where);
		void			DrawBitmapAsync(const BBitmap *aBitmap, BRect dstRect);
		void			DrawBitmap(	const BBitmap *aBitmap,
									BRect srcRect,
									BRect dstRect);
		void			DrawBitmap(const BBitmap *aBitmap);
		void			DrawBitmap(const BBitmap *aBitmap, BPoint where);
		void			DrawBitmap(const BBitmap *aBitmap, BRect dstRect);
	
virtual void			SetFontName(const char* name);
virtual void			SetFontSize(float pointSize);
virtual void			SetFontShear(float degrees);
virtual void			SetFontRotation(float degrees);
virtual void			SetSymbolSet(const char* name);
		void			GetFontInfo(font_info *info) const;
		float			StringWidth(const char *aString) const;
		float			StringWidth(const char *aString, long length) const;
		void			GetCharEscapements(	char charArray[],
											long numChars,
											float escapementArray[],
											float* escapementUnits) const;
		void			GetCharEdges(	char charArray[],
										long numChars,
										edge_info edgeArray[]) const;
		void			DrawChar(char aChar);
		void			DrawChar(char aChar, BPoint location);
		void			DrawString(const char *aString);
		void			DrawString(const char *aString, BPoint location);
		void			DrawString(const char *aString, long length);
		void			DrawString(	const char *aString,
									long length,
									BPoint location);

		void			Invalidate(BRect invalRect);
		void			Invalidate();

		void			BeginPicture(BPicture *a_picture);
		void			BeginPicture_pr(BPicture *a_picture, BRect r);
		BPicture		*EndPicture();
		void			DrawPicture(const BPicture *a_picture);
		void			DrawPicture(const BPicture *a_picture, BPoint where);

virtual	void			SetFlags(ulong flags);
		ulong			Flags() const;
virtual	void			SetResizingMode(ulong mode);
		ulong			ResizingMode() const;
		void			MoveBy(float dh, float dv);
		void			MoveTo(BPoint where);
		void			MoveTo(float x, float y);
		void			ResizeBy(float dh, float dv);
		void			ResizeTo(float width, float height);
		void			ScrollBy(float dh, float dv);
		void			ScrollTo(BPoint where);
		void			ScrollTo(float x, float y);
virtual	void			MakeFocus(bool focusState = TRUE);
		bool			IsFocus() const;
	
virtual	void			Show();
virtual	void			Hide();
		bool			IsHidden() const;
	
		void			Flush() const;
		void			Sync() const;

		BScrollBar		*ScrollBar(orientation posture) const;

virtual	void			HandlersRequested(BMessage *msg);
		bool			IsPrinting() const;
		void			SetScale(float scale) const;
// ------------------------------------------------------------------

private:

friend class BScrollBar;
friend class BWindow;
friend class BBitmap;
friend class BPrintJob;

		bool		SaveAsResource(long resID);
		void		StrokeLineToNoPat(BPoint pt);
		void		StrokeRectNoPat(BRect r);
		bool		remove_from_list(BView *a_view);
		bool		remove_self();
		bool		do_owner_check() const;
		void		set_owner(BWindow *the_owner);
		void		do_activate(long msg);
		void		end_draw();
		void		check_lock() const;
		void		movesize(long code, long h, long v);
		void		handle_tick();
		char		*test_area(long length);
		void		remove_comm_array();
		_array_hdr_	*new_comm_array(long cnt);
		BView		*RealParent() const;
		void		SetScroller(BScrollBar *sb);
		void		UnsetScroller(BScrollBar *sb);
		void		RealScrollTo(BPoint);
		void		init_cache();
		void		set_cached_attributes();

		long			server_token;
		BRect			f_bound;
		long			f_type;
		float			origin_h;
		float			origin_v;

		BWindow*		owner;
		BView*			parent;
		BView*			next_sibling;
		BView*			prev_sibling;
		BView*			first_child;

		short 			fShowLevel;
		bool			top_level_view;
		BPicture		*cpicture;
		_array_data_	*comm;
		rgb_color		high_color;
		rgb_color		low_color;
		rgb_color		view_color;

		BScrollBar		*fVerScroller;
		BScrollBar		*fHorScroller;
		bool			f_is_printing;
		bool			attached;
		_view_attr_		*attr_cache;
};

inline ulong	BView::Flags() const
	{ return(f_type & ~(_RESIZE_MASK_)); }

inline ulong	BView::ResizingMode() const
	{ return(f_type & (_RESIZE_MASK_)); }

//------------------------------------------------------------------------------

#endif
