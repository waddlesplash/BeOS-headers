/*
  -----------------------------------------------------------------------------

	File:			TabView.h
	
	Description: 
	
	Copyright 2004, Yellow Tab GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/

// Guard against the beide's broken include directives.
#ifndef _ZETA_USING_EXPERIMENTAL_
#warning *** Redirecting experimental include to standard include ***
#include <interface/TabView.h>
#endif

#ifndef _TAB_VIEW_H
#define _TAB_VIEW_H


#include <interface/Control.h>
#include <interface/StackedViewManager.h>
#include <support/Vector.h>

// this might be better located in InterfaceDefs.h or whatnot, TBD
// TODO: perhaps it'd be prudent to have some constants to determine tab states
// i.e. maybe we want to be able to disable tabs or otherwise force them to change
// their look?

namespace Z {
namespace Experimental {
namespace Interface {
namespace Private {
		class BTabHeader;
}

namespace ZEIP = Z::Experimental::Interface::Private;

enum tab_orientation 
{
	toLeft,
	toTop,
	toRight,	// Do not use, not currently implemented.
	toBottom
};

class BTab;

class BTabView : public BControl
{
	public:
								BTabView(BRect _frame, 
								         const BString& _name, 
								         uint32 _resize = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
								         uint32 _flags = B_WILL_DRAW, 
								         BMessage* _message = NULL,
								         tab_orientation _orient = toTop);
		virtual					~BTabView();

				tab_orientation	TabOrientation() const;
				void			SetTabOrientation(tab_orientation _orient);

				size_t			CountTabs() const;
				size_t			GetSelectedIndex() const;
				BTab&			GetSelectedTab();	
				BTab&			TabAt(size_t _index);
				size_t			TabIndex(const BTab& _tab);
				const BRect&	GetTabFrame(size_t _index) const;
				
				size_t 			AddTab(BTab* _tab);
				BTab*			RemoveTab(size_t _index);
				BTab*			RemoveTab(BTab& _tab);

				void			SelectTab(size_t _index);
				void			SetFocusedTab(size_t _index);
				size_t			GetFocusedTab();
				
		virtual void			Draw(BRect _update);
		virtual void			SelectionChanged(size_t _index);
		virtual	void			AttachedToWindow();
		virtual void			KeyDown(const char* _bytes, int32 _num_bytes);
		virtual void			MakeFocus(bool _focus_state);
		virtual	void			FrameResized(float _width, float _height);
		virtual	void			GetPreferredSize(float* _width, float* _height);
		
				BRect			GetContentArea() const;
				void			ResizeToTabSize(const BPoint& _size);
				void			ResizeToTabSize(float _width, float _height);
				
				
				// returns header width or height depending on orientation.
				float 			HeaderSize() const;
				
				BStackedViewManager&	
								GetViewManager(); 
		
	private:

				float			CalcHeaderSize();
				void			AdjustRects();
				void			CheckBounds(size_t _index) const;
				status_t		IndexOf(const BTab& _tab, size_t& index) const;
				
		// reserved for future use
		virtual void _ReservedVirtual1();
		virtual void _ReservedVirtual2();
		virtual void _ReservedVirtual3();
		virtual void _ReservedVirtual4();
		virtual void _ReservedVirtual5();
		virtual void _ReservedVirtual6();
		virtual void _ReservedVirtual7();
		virtual void _ReservedVirtual8();
		virtual void _ReservedVirtual9();
		virtual void _ReservedVirtual10();
		virtual void _ReservedVirtual11();
		virtual void _ReservedVirtual12();
		virtual void _ReservedVirtual13();
		virtual void _ReservedVirtual14();
		virtual void _ReservedVirtual15();

	private:
		friend class ZEIP::BTabHeader;
		
		ZEIP::BTabHeader*		fTabHeader;
		
		BStackedViewManager*	fStackedViewManager;
		BVector<BTab*>			fTabs;
		tab_orientation			fTabOrientation;
		size_t					fSelectedTab;
		BRect					fTabBarRect;
		size_t					fFocusedTab;
		
		uint32					fTabbyPaddies[8];
};


} // ns Experimental
} // ns Interface
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BTabView;
using Z::Experimental::Interface::tab_orientation;
using Z::Experimental::Interface::toLeft;
using Z::Experimental::Interface::toTop;
using Z::Experimental::Interface::toRight;
using Z::Experimental::Interface::toBottom;
#endif

#endif // _TABVIEW_H_
