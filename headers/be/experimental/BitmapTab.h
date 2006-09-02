/*
  -----------------------------------------------------------------------------

	File: BitmapTab.h
	
	Date: Thursday December 08, 2005

	Description: A Tab to go on a TabView which will show a bitmap and a label.
				 The label can be an empty string to just show a bitmap.
	
	
	Copyright 2004, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _BITMAPTAB_H
#define _BITMAPTAB_H

#include <experimental/Tab.h>

namespace Z {
namespace Experimental {
namespace Interface {

class BitmapTab : public BStringTab
{
	public:
								BitmapTab(BBitmap* _bitmap, const BString& _label, BView* _target);
								BitmapTab(BView* _target, BBitmap* _bitmap, const BString& _label = BString());
								BitmapTab(const BitmapTab& _other);
								
		virtual					~BitmapTab();
					
				BBitmap*		SwapBitmap(BBitmap* _bitmap);
				void			SetBitmap(BBitmap* _bitmap);		
		const	BBitmap&		GetBitmap() const;
					
		virtual void	 		DrawTab(BView& _owner, 
							    	    const BRect& _frame, 
							    	    tab_position _position, 
							    	    tab_orientation _orientation,
							    	    draw_state _state);

		virtual void			DrawFocusMarker(BView& _owner, 
							    	            const BRect& _frame, 
							    	            tab_position _position, 
							    	            tab_orientation _orientation,
							    	            draw_state _state);

	protected:
		virtual void			GetContentSize(const BView& _owner, BRect& _size);
		virtual	void			DrawLabel(BView& _owner,
							    	      const BRect& _frame, 
							    	      tab_position _position, 
							    	      tab_orientation _orientation,
							    	      draw_state _state);
	
	private:
		BBitmap* fBitmap;

};

} // Interface
} // Experimental
} // Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BitmapTab;
#endif

typedef Z::Experimental::Interface::BitmapTab BBitmapTab;

#endif
