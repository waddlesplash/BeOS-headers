//******************************************************************************
//
//	File:		TextView.h
//
//	Description:	editable text view class interface.
//
//	Written by:	Eric Knight
//
//	Copyright 1992-93, Be Incorporated
//
//******************************************************************************

#ifndef	_TEXT_VIEW_H
#define	_TEXT_VIEW_H

#ifndef	_INTERFACE_DEFS_H
#include "InterfaceDefs.h"
#endif
#ifndef	_VIEW_H
#include "View.h"
#endif

//------------------------------------------------------------------------------

enum { ALIGN_LEFT,
       ALIGN_RIGHT,
       ALIGN_CENTER };

//------------------------------------------------------------------------------

class BWindow;
class BScrollBar;

class BTextView : public BView {
public:
			BTextView(BRect *frame, char *name, BRect* textRect, 
				  ulong resizeMask, ulong flags);
virtual			~BTextView();
virtual	char		*ClassName();

	char*		Text();
	void		SetText(char* text, long length);
	void		Select(long newStart, long newEnd);
	void		SelectAll();
	void		Cut();
	void		Copy();
	void		Paste();
	void		PasteFile(char *filePathName);
	void		Delete();
	void		Insert(char* text, long length);
	void		SetAlignment(long flag);
	long		Alignment();
	void		SetSpacing(long spacing);
	long		Spacing();
	void		SetTabWidth(long width);
	void		SetMaxChars(long max);
	long		TextLength();
	long		LineWidth(long line = 0);
	void		SetAutoindent(bool state);
	bool		DoesAutoindent();
	void		SetWordWrap(bool state);
	bool		DoesWordWrap();
virtual void		SetFontName(char* name);
virtual void		SetFontSize(long pointSize);
virtual void		SetFontShear(long degrees);
virtual void		SetFontRotation(long degrees);
virtual	bool		BreaksAtChar(long charPos);
virtual	bool		AcceptsChar(ulong aChar);
	void		SetTextRect(BRect *rect);
	void		ScrollToSelection();
	void		MakeResizable(BView* containerView);
	void		MakeSelectable(bool flag = TRUE);
	bool		IsSelectable();
	void		MakeEditable(bool flag = TRUE);
	bool		IsEditable();
	long		SelectionStart();
	long		SelectionEnd();

		// Parent method overrides
virtual	void		AttachedToWindow();
virtual	void		Draw(BRect* updateRect);
virtual	void		MouseDown(BPoint where);
virtual	void		WindowActivated(bool state);
virtual	void		MakeFocus(bool focusState = TRUE);
virtual	void		KeyDown(ulong a_key);
virtual	void		Tick();
		// End method overrides
		
//------------------------------------------------------------------------------

private:
		void	CalcText();
		void	Lock(bool state);
		void	ChangeFont();
		void	DeleteChar();
		char*	DeleteSelection();
		char*	CopySelection();
		void	InsertTxt(char* text, long length);
		void	HiliteRange(bool request);
		void	InvertCaret();
		void	OffCaret();
		void	InvertRange(long from, long to);
		void	DrawLines(long lstart, long cStart, long cEnd, long delta);
		long	GetLineNo(long index);
		BPoint	GetPoint(long index);
		long	GetIndex(BPoint pt);
		long	GetIndex(long h, long v);
		void	Recalc(long delta, long* firstLine, long* firstChar, long* lastChar);
		void	SetScrollBarRanges();
		void	GetScrollBars(BScrollBar** hBar, BScrollBar** vBar);
		short	JustOffset(long line);
	inline 	long 	GetWidthEntry(char c);
		long	StringWidth_table(long index, long length);
		long	MeasureStringTab(long line, long index, long length);
		void	DrawStringTab(long line, long index, long length, long hPos, long vPos);
		void	CheckSizeChange();

		BRect		fDestRect;
		short 		fLineHeight;
		short 		fFontAscent;
		BPoint 		fSelPoint;
		long 		fSelStart;
		long 		fSelEnd;
		ulong 		fCaretTime;
		BRect		fCaretRect;
		bool 		fCaretOn;
		bool 		fHiliteState;
		bool		fActive;
		short 		fJust;
		short 		fSpacing;
		short		fTabWidth;
		long		fMaxChars;
		long		fTextLength;
		char*		fText;
		long		fTextPtrSize;
		bool		fAutoIndent;	
		bool 		fWrapWords;
		bool		fSelectable;	
		bool 		fEditable;
		long 		fNumLines;
		long*		fLineStarts;
		long		fLinesPtrSize;
		typedef struct {
			short	width;
			bool	filled;
		} widthEntry;
		widthEntry*	fCharWidthTable;
		BView*		fContainerView;
};

inline char		*BTextView::ClassName() { return "BTextView"; };

//------------------------------------------------------------------------------


#endif
