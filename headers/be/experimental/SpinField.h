/*
  -----------------------------------------------------------------------------

	File: 				SpinField.h
	
	Date: 				Monday December 20, 2004

	Description:		Control to trigger some events like increase decriese 
						values in a view, switch some Tabs in TabView...
	
	
	Copyright 2004, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _BSPIN_FIELD_H_
#define _BSPIN_FIELD_H_

#include <interface/Control.h>
#include <support/String.h>

namespace Z {
namespace Experimental {
namespace Interface {

class BSpinField : public BControl
{
	public:
								BSpinField(BRect _frame, 
											const BString& _name,
											BMessage* _message,
											orientation _orientation = B_HORIZONTAL,
											uint32 _resize_mode = B_FOLLOW_LEFT | B_FOLLOW_TOP,
									 		uint32 _flags = B_NAVIGABLE | B_WILL_DRAW |	B_FRAME_EVENTS);

								BSpinField(BMessage* _data);
	static 	BArchivable*		Instantiate(BMessage* _data);
	virtual	status_t 			Archive(BMessage* _data, bool _deep = true) const;

	virtual						~BSpinField();

	virtual	void				AttachedToWindow();
	virtual	void				DetachedFromWindow();

	virtual void				AllAttached();
	virtual void				AllDetached();

	virtual	void				Draw(BRect _update_rect);
	virtual	void				FrameMoved(BPoint _new_position);
	virtual	void				FrameResized(float _new_width, float _new_height);

	virtual	void				MouseDown(BPoint _where);
	virtual	void				MouseUp(BPoint _point);
	virtual	void				MouseMoved(BPoint _point, uint32 _code, const BMessage* _message);

	virtual	void				KeyDown(const char* _bytes, int32 _num_bytes);
	virtual void				KeyUp(const char* _bytes, int32 _num_bytes);
	virtual	status_t			Invoke(BMessage* _message = NULL);

	virtual void				MessageReceived(BMessage* _message);
	virtual void				WindowActivated(bool _state);
	virtual void				ResizeToPreferred();
	virtual void				GetPreferredSize(float* _width, float* _height);
	virtual void				MakeFocus(bool _state = true);
	virtual	void				SetValue(int32 _value);

			orientation			Orientation() const;
	virtual void				SetOrientation(orientation _orientation);

	//----- not implemented atm -----------------------------------------	
	virtual void				SetRightTopEnabled(bool _enabled);
	virtual void 				SetLeftBottomEnabled(bool _enabled);
	
	private:
			BRect				RightTopFrame() const;
			BRect				LeftBottomFrame() const;
			
	private:
			orientation			fOrientation;
			bool				fRightTopPressed;
			bool				fLeftBottomPressed;
			bool				fRightTopEnabled;
			bool				fLeftBottomEnabled;
};

}	// Interface
}	// Experimental
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BSpinField;
#endif

#endif
