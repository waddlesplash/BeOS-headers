//******************************************************************************
//
//	File:		TextView.h
//
//	Description:	editable text view class interface.
//
//	Copyright 1992-94, Be Incorporated
//
//******************************************************************************

#ifndef	_TEXT_VIEW_H
#define	_TEXT_VIEW_H

#ifndef	_INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef _LIST_H
#include <support/List.h>
#endif
#ifndef	_VIEW_H
#include "View.h"
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

//------------------------------------------------------------------------------

class BWindow;
class BScrollBar;
//class BList;

class BTextView : public BView {
	DECLARE_CLASS_INFO(BView);
public:
					BTextView(	BRect frame,
								const char *name,
								BRect textRect, 
								ulong resizeMask,
								ulong flags);
virtual				~BTextView();

		const char*	Text() const;
		void		SetText(const char* text, long length);
		void		SetText(const char* text);
		void		Select(long newStart, long newEnd);
		void		SelectAll();
		void		GoToLine(long line);
		void		Cut();
		void		Copy();
		void		Paste();
		void		PasteFile(const char *filePathName);
		void		Delete();
		void		Insert(const char* text, long length);
		void		Insert(const char* text);
		void		SetAlignment(alignment flag);
		alignment	Alignment() const;
		void		SetSpacing(long spacing);
		long		Spacing() const;
		void		SetTabWidth(long width);
		void		SetMaxChars(long max);
		long		TextLength() const;
		long		LineWidth(long line = 0) const;
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
		// Parent method overrides
virtual	void		AttachedToWindow();
virtual	void		Draw(BRect updateRect);
virtual	void		MouseDown(BPoint where);
virtual	void		WindowActivated(bool state);
virtual	void		MakeFocus(bool focusState = TRUE);
virtual	void		KeyDown(ulong a_key);
virtual	void		Pulse();
virtual void		SetFontName(const char* name);
virtual void		SetFontSize(long pointSize);
virtual void		SetFontShear(long degrees);
virtual void		SetFontRotation(long degrees);
	    long		IndexAtPoint(BPoint pt) const;
		long		IndexAtPoint(long h, long v) const;
		void		Highlight(long from, long to);

//-----------------------------------------------------------------------------
private:

friend class BScrollBar;

		void		CalcText();
		void		Lock(bool state);
		void		ChangeFont();
		void		DeleteChar();
		char*		DeleteSelection();
		char*		CopySelection();
		void		InsertTxt(const char* text, long length);
		void		HiliteRange(bool request);
		void		InvertCaret();
		void		OffCaret();
		void		DrawLines(long lstart, long cStart, long cEnd, long delta);
		long		GetLineNo(long index) const;
		BPoint		GetPoint(long index) const;
		void		Recalc(	long delta,
							long* firstLine,
							long* firstChar,
							long* lastChar);
		void		SetScrollBarRanges();
		void		AttachHorzScrollBar(BScrollBar* hsb);
		void		AttachVertScrollBar(BScrollBar* vsb);
		short		JustOffset(long line) const;
	 	long 		GetWidthEntry(char c) const;
		long		StringWidth_table(long index, long length) const;
		long		MeasureStringTab(long line, long index, long length) const;
		void		DrawStringTab(	long line,
									long index,
									long length,
									long hPos,
									long vPos);
		void		CheckSizeChange();
		bool		IsAllowed(ulong aChar) const;
	
		BRect		fDestRect;
		short 		fLineHeight;
		short 		fFontAscent;
		BPoint 		fSelPoint;
		long 		fSelStart;
		long 		fSelEnd;
		ulong 		fCaretTime;
		BRect		fCaretRect;
		alignment	fJust;
		short 		fSpacing;
		short		fTabWidth;
		long		fMaxChars;
		long		fTextLength;
		char*		fText;
		long		fTextPtrSize;
		long 		fNumLines;
		long*		fLineStarts;
		long		fLinesPtrSize;
		ulong		fClickTime;
		long		fClickIndex;
		long		fNumClicks;
		typedef struct {
			short	width;
			bool	filled;
		} widthEntry;
		widthEntry*	fCharWidthTable;
		BView*		fContainerView;
		long		fInitialLineWidth;
		BRect		fInitialContRect;
		long		fInitialDestRight;
		BScrollBar*	fHSB;
		BScrollBar*	fVSB;
		BList*		fDisallowedChars;
		bool		fAutoIndent;	
		bool 		fWrapWords;
		bool		fSelectable;	
		bool 		fEditable;
		bool 		fCaretOn;
		bool 		fHiliteState;
		bool		fActive;
};

inline bool	BTextView::IsAllowed(ulong c) const
	{ return !fDisallowedChars->HasItem((void*)c); }

//------------------------------------------------------------------------------


#endif
