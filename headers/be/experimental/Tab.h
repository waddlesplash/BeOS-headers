/*
  -----------------------------------------------------------------------------

	File:			Tab.h
	
	Description:	
	
	Copyright 2004, Yellow Tab GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/
// Guard against the beide's broken include directives.
#ifndef _ZETA_USING_EXPERIMENTAL_
#warning *** Redirecting experimental include to standard include ***
#include <interface/TabView.h>
#define _BTAB_H_
#endif

#ifndef _BTAB_H_
#define _BTAB_H_

#include <experimental/TabView.h>

// pure virtual base class to act as interface for BTabView to
// be able to call tabs and have them draw themselves as needed.

// flesh out the interface as needed for whatever
// the drawing mechanism ends up being (voidref)
// and maybe even BIconTab if time allows

namespace Z {
namespace Experimental {
namespace Interface {

enum tab_position
{
	tpFirst,
	tpMiddle,
	tpLast	
};

enum draw_state
{
	dsNormal,
	dsMouseOver
};

class BTab
{
	public:
								BTab(BView* _target = NULL);
						
		virtual 				~BTab();

				bool			HasTargetView();
				BView&			GetTargetView();
				BView*			DetachTargetView();
				void			SetTargetView(BView* _view);
				BView*			ReplaceTargetView(BView* _replacement);

				void			SetFocused(bool _focus = true);
				bool			IsFocused() const;
				
				void			SetDirty(bool _schmutz = true);
				bool			IsDirty();
				
				bool			IsSelected() const;
					
				void			SetEnabled(bool _enabled = true);
				bool			IsEnabled();
				
				const BRect&	GetContentSize(const BView& _owner);

		virtual void		 	DrawTab(BView& _owner, 
								        const BRect& _frame, 
							    	    tab_position _position, 
							        	tab_orientation _orientation,
							        	draw_state _state) = 0;

		virtual void			DrawFocusMarker(BView& _owner, 
							    	            const BRect& _frame, 
							    	            tab_position _position, 
							    	            tab_orientation _orientation,
							    	            draw_state _state) = 0;
	protected:
		virtual	void			GetContentSize(const BView& _owner, BRect& _size) = 0;
				void			InvalidateTab();

	private:
				void			SetSelected(bool _select);

	private:
		BView*	fTargetView;
		bool	fFocused;
		bool	fEnabled;
		bool	fSelected;
		bool	fDirty;
		BRect	fContentSize;
		
		friend class BTabView;
};

class BStringTab : public BTab
{
	public:
								BStringTab(const BString& _label, BView* _target);
								BStringTab(BView* _target, const BString& _label = BString());
		virtual					~BStringTab();
		
				const BString&	GetLabel() const;
				void	 		SetLabel(const BString& _label);
			
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
		
		// For derivatives that just want to reposition the default label.
		virtual	void			DrawLabel(BView& _owner,
							    	      const BRect& _frame, 
							    	      tab_position _position, 
							    	      tab_orientation _orientation,
							    	      draw_state _state);
	
	private:
		BString fTabLabel;
};



} // Interface
} // Experimental
} // Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BTab;
using Z::Experimental::Interface::BStringTab;
using Z::Experimental::Interface::tab_position;
using Z::Experimental::Interface::tpFirst;
using Z::Experimental::Interface::tpMiddle;
using Z::Experimental::Interface::tpLast;
using Z::Experimental::Interface::draw_state;
using Z::Experimental::Interface::dsNormal;
using Z::Experimental::Interface::dsMouseOver;
#endif

#endif // _TAB_H_
