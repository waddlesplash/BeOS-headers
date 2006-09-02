/*
  -----------------------------------------------------------------------------

	File:			TextField.h
	
	Description:	Encapsulates a label/ value pair of strings much like a MenuField
	
	Copyright 2004, Yellow Tab GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/

#ifndef _BTEXT_FIELD_H_
#define _BTEXT_FIELD_H_

#include <experimental/StringView.h>
#include <interface/View.h>

namespace Z {
namespace Experimental {
namespace Interface {
		
class BTextField : public BView
{
	public:
									BTextField(BRect _frame,
						           			   const BString _name,
						           			   const BString _label,
						           			   const BString _value,
						  					   uint32 resizeFlags = B_FOLLOW_LEFT | B_FOLLOW_TOP,
						            		   uint32 flags = B_WILL_DRAW);
									BTextField(BMessage* _data);
		static	BArchivable*		Instantiate(BMessage* _data);
				status_t			Archive(BMessage* _data, bool _deep = true) const;
		virtual						~BTextField();
		
		virtual	void				SetLabel(const BString _label);		
		const 	BString				GetLabel() const;
		virtual	void				SetValue(const BString _value);
		const 	BString				GetValue() const;
		virtual	void				SetDivider(float _divider);
				float				GetDivider() const;
		virtual	void				SetAlignment(alignment _align);
				alignment			Alignment() const;

		virtual	void				AttachedToWindow();
		virtual	void				Draw(BRect _updateRect);
		
		virtual	void 				MessageReceived(BMessage* _messag);
		virtual	void				MouseDown(BPoint _pt);
		virtual	void 				MouseUp(BPoint _pt);
		virtual	void 				MouseMoved(BPoint _pt, uint32 _code, const BMessage* _msg);
		virtual	void				DetachedFromWindow();
		virtual	void				FrameMoved(BPoint _newPosition);
		virtual	void				FrameResized(float _newWidth, float _newHeight);
		virtual void				SetFont(const BFont* _font, uint32 _mask = B_FONT_ALL);

		virtual	void				ResizeToPreferred();
		virtual void				GetPreferredSize(float* _width, float* _height);
		virtual	void				MakeFocus(bool _state);
		virtual	void				AllAttached();
		virtual	void				AllDetached();

				BStringView&		Value();
						
	private:
				float				fDivider;
				BString				fLabel;
				BStringView*		fValue;
				alignment			fAlign;
};

}	// Interface
}	// Experimental
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BTextField;
#endif

#endif
