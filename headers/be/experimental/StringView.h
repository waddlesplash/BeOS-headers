/*
  -----------------------------------------------------------------------------

	File:				StringView.h
	
	Description:		Draws a non-editable automatic wrapping multiline String
	                    which can have text which will send a message when clicked.
	
	Copyright 2004-2006, Yellow Tab GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/
// Guard against the beide's broken include directives.
#ifndef _ZETA_USING_EXPERIMENTAL_
#include <interface/StringView.h>
#warning *** Redirecting experimental include to standard include ***
#endif

#ifndef _STRING_VIEW_H
#define _STRING_VIEW_H

#include <support/StringList.h>
#include <support/String.h>
#include <interface/Control.h>

class BMessage;

namespace Z {
namespace Experimental {
namespace Interface {

class BStringView : public BControl
{
	public:
											BStringView(BRect _frame, 
											            const BString _name,
											            const BString _text,
											            BMessage* _message = NULL,
											            uint32 _resize = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
											            uint32 _flags = B_WILL_DRAW);
											BStringView(BMessage* _data);
		static	BArchivable*				Instantiate(BMessage* _data);
				status_t					Archive(BMessage* _data, bool _deep = true) const;
		virtual								~BStringView();
		
				void						SetText(const BString _text);
		  		const BString				GetText() const;
		virtual	void						AttachedToWindow();
		virtual	void 						MessageReceived(BMessage* _messag);
		virtual void						ResizeToPreferred();
		virtual void						GetPreferredSize(float* _width, 
															 float* _height);
		virtual	void						Draw(BRect updateRect);
				void						SetAlignment(alignment _flag);
				alignment					Alignment() const;
		virtual	void 						MouseDown(BPoint _pt);
		virtual	void 						MouseUp(BPoint _pt);
		virtual	void 						MouseMoved(BPoint _pt, 
													   uint32 _code, 
													   const BMessage* _msg);
		virtual	void 						DetachedFromWindow();
		virtual	void 						FrameMoved(BPoint _newPosition);
		virtual	void 						FrameResized(float _newWidth, 
														 float _newHeight);
		virtual	void 						MakeFocus(bool _state);
		virtual	void 						AllAttached();
		virtual	void 						AllDetached();
		virtual void						SetFont(const BFont* _font, uint32 _mask = B_FONT_ALL);
		virtual status_t					SetTarget(const BHandler* _handler, const BLooper* _looper = NULL);
		virtual status_t					SetTarget(BMessenger _messenger);
		
				status_t					SetClickText(const BString _text,
											             const BMessage& _message = BMessage());
											             
				status_t					SetClickText(const BString _text,
											             const BHandler& _target,
											             const BMessage& _message = BMessage());

	private:
				void						PopulateLines();
				void						SplitString(const BString _string, 
				                                        float _size);
				void 						RemoveWhitespace(BString& _line);
				void						CalculateClickItems();
				void						CalculateClickItem(uint32 _index);
				void						SetInvalidCITargets();
				
				
	private:
		class ClickItem
		{
			public:
				ClickItem(const BString _text,
				          const BMessage& _message,
				          const BMessenger& _target)
					: data(_text)
					, message(_message)
					, target(_target)
					{;}

				ClickItem()
					{;}

				bool	Contains(const BPoint& _where) const;
				void	Invalidate(BView& _owner) const;
				void	Invoke();
				
				class UIData
				{
					public:
						UIData()
							:next(NULL)
							{;}
								
						UIData(const BString _text)
							:text(_text)
							,next(NULL)
							{;}
					
						UIData(const UIData& _other);
						
						~UIData()
							{ delete next; }

						BRect 		frame;
						BString		text;
						UIData*		next;
				};

				UIData		data;				
				BMessage	message;
				BMessenger	target;
		};

		alignment					fAlign;
		BString						fText;
		Z::Support::
		BStringList					fLines;
		BSafeArray<ClickItem>		fClickItems;
		uint32						fCurrentClickIndex;
};

}	// Interface
}	// Experimental
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BStringView;
#endif

#endif	//	_STRING_VIEW_H_

