//******************************************************************************
//
//	File:		TextView.h
//
//	Description:	editable text view class interface.
//
//	Copyright 1992-96, Be Incorporated
//
//******************************************************************************

#ifndef	_TEXT_VIEW_H
#define	_TEXT_VIEW_H

#ifndef	_INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _LIST_H
#include <List.h>
#endif
#ifndef	_VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BWindow;
class BScrollBar;
class _BTextBuffer_;
class BTextView;

class BTextView : public BView {
	B_DECLARE_CLASS_INFO(BView);
public:
					BTextView(	BRect frame,
								const char *name,
								BRect textRect, 
								ulong resizeMask,
								ulong flags);
virtual				~BTextView();

		const char*	Text();
		void		GetText(char *buffer, long index, long length) const;
		char		CharAt(long index) const;
		void		SetText(const char* text, long length);
		void		SetText(const char* text);
		void		Select(long newStart, long newEnd);
		void		SelectAll();
		void		GoToLine(long line);
		void		Delete();
		void		Insert(const char* text, long length);
		void		Insert(const char* text);
		void		SetAlignment(alignment flag);
		alignment	Alignment() const;
		void		SetSpacing(long spacing);
		long		Spacing() const;
		void		SetTabWidth(float width);
		void		SetMaxChars(long max);
		long		TextLength() const;
		float		LineWidth(long line = 0) const;
		void		SetAutoindent(bool state);
		bool		DoesAutoindent() const;
		void		SetWordWrap(bool state);
		bool		DoesWordWrap() const;
virtual	bool		BreaksAtChar(ulong aChar) const;
virtual	bool		AcceptsChar(ulong aChar) const;
		void		DisallowChar(ulong aChar);
		void		AllowChar(ulong aChar);
		void		SetTextRect(BRect rect);
		void		ScrollToSelection();
		void		MakeResizable(BView* containerView);
		void		MakeSelectable(bool flag = TRUE);
		bool		IsSelectable() const;
		void		MakeEditable(bool flag = TRUE);
		bool		IsEditable() const;
		void		GetSelection(long *start, long *end);
		long		CountLines(void) const;
		float		LineHeight() const;

		// Parent method overrides
virtual	void		AttachedToWindow();
virtual	void		Draw(BRect updateRect);
virtual	void		MouseDown(BPoint where);
virtual	void		WindowActivated(bool state);
virtual	void		MakeFocus(bool focusState = TRUE);
virtual	void		KeyDown(ulong a_key);
virtual	void		Pulse();
virtual void		MessageReceived(BMessage *message);
virtual	bool		MessageDropped(BMessage *message, BPoint pt, BPoint offset);
virtual void		Cut(BClipboard *clip);
virtual void		Copy(BClipboard *clip);
virtual	void		Paste(BClipboard *clip);
virtual void		SetFontName(const char* name);
virtual void		SetSymbolSet(const char* name);
virtual void		SetFontSize(float pointSize);
virtual void		SetFontShear(float degrees);
virtual void		SetFontRotation(float degrees);
	    long		IndexAtPoint(BPoint pt) const;
		long		IndexAtPoint(float h, float v) const;
		void		Highlight(long from, long to);
        long		CurrentLine(void) const;
		BRect		TextRect(void) const;

//-----------------------------------------------------------------------------
private:

friend class BScrollBar;

		void			CalcText(bool inval = TRUE);
		void			Lock(bool state);
		void			ChangeFont();
		void			DeleteChar();
		char*			DeleteSelection();
		char*			CopySelection() const;
		void			InsertTxt(const char* text, long length);
		void			HiliteRange(bool request);
		void			InvertCaret();
		void			OffCaret();
		void			DrawLines(	long lstart,
									long cStart,
									long cEnd,
									long delta);
		long			GetLineNo(long index) const;
		BPoint			GetPoint(long index) const;
		void			xRecalc(long delta,
								long firstLine,
								long firstChar,
								long* lastChar);
		void			Recalc(	long delta,
								long* firstLine,
								long* firstChar,
								long* lastChar);
		void			SetScrollBarRanges();
		void			AttachHorzScrollBar(BScrollBar* hsb);
		void			AttachVertScrollBar(BScrollBar* vsb);
		float			JustOffset(long line) const;
	 	float 			GetWidthEntry(unsigned char c) const;
		float			StringWidth_table(long index, long length) const;
		float			MeasureStringTab(	long line,
											long index,
											long length) const;
		void			DrawStringTab(	long line,
										long index,
										long length,
										float hPos,
										float vPos);
		void			CheckSizeChange();
		bool			IsAllowed(ulong aChar) const;
		void			InsertPasteOrDropped(	const char *theText,
												long len,
												bool doingDrop,
												bool intraDrag,
												BPoint loc);
	
		BRect			fDestRect;
		short 			fLineHeight;
		short 			fFontAscent;
		long 			fSelStart;
		long 			fSelEnd;
		ulong 			fCaretTime;
		BRect			fCaretRect;
		alignment		fJust;
		short 			fSpacing;
		float			fTabWidth;
		long			fMaxChars;
		_BTextBuffer_	*fBuffer;
		long 			fNumLines;
		long*			fLineStarts;
		long			fLinesPtrSize;
		long			fClickIndex;
		long			fNumClicks;

		struct widthEntry {
			float	width;
			bool	filled;
		};
		widthEntry*	fCharWidthTable;

		BView*			fContainerView;
		float			fInitialLineWidth;
		BRect			fInitialContRect;
		float			fInitialDestRight;
		BScrollBar*		fHSB;
		BScrollBar*		fVSB;
		BList*			fDisallowedChars;
		bool			fAutoIndent;	
		bool 			fWrapWords;
		bool			fSelectable;	
		bool 			fEditable;
		bool 			fCaretOn;
		bool 			fHiliteState;
		bool			fActive;
};

inline bool	BTextView::IsAllowed(ulong c) const
	{ return !fDisallowedChars->HasItem((void*)c); }

inline long BTextView::CountLines(void) const
	{ return fNumLines; }

inline BRect BTextView::TextRect(void) const
	{ return fDestRect; }

inline float BTextView::LineHeight(void) const
	{ return fLineHeight; }

//------------------------------------------------------------------------------


#endif
