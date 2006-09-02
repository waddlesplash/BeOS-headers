/*
  -----------------------------------------------------------------------------

	File: ToolBar.h
	
	Description: A tool bar.
	
	
	Copyright 2006, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _TOOLBAR_H_
#define _TOOLBAR_H_

#include "experimental/Tool.h"

#include <interface/View.h>
#include <support/List.h>

class BMenuItem;

namespace Z {
namespace Experimental {
namespace Interface {
	
enum 
{
	B_TOOLBAR_EXPANDED,
	B_TOOLBAR_COLLAPSED
};

enum nu_border_style
{
	BS_NO_BORDER,
	BS_PLAIN_BORDER
};

class BToolBar : public BView
{
	public :
									BToolBar(
										BRect _frame,
										const BString _name,
										orientation _orientation = B_HORIZONTAL,
										nu_border_style = BS_PLAIN_BORDER,
										uint32 _resizing_mode = B_FOLLOW_LEFT | B_FOLLOW_TOP,
										uint32 _flags = B_WILL_DRAW | B_NAVIGABLE_JUMP );
									
		virtual						~BToolBar();

				void				AddTool(
										BTool* _tool);
				
				void				AddTool(
										BTool* _tool,
										int32 _at_index );
										
				void				RemoveTool(
										BTool* _tool );
										
				void				RemoveTool(
										int32 _index );
				
		virtual void				AttachedToWindow();
				
				int32				CountTools() const;
				
		virtual void				Draw(
										BRect _update_rect );
										
		virtual void				MessageReceived(
										BMessage* _message );
										
		virtual	void				FrameResized(
										float new_width, 
										float new_height );
		
		virtual void				GetPreferredSize(
										float* _width,
										float* _height );
												
		virtual void				ResizeToPreferred();
		
				void				SetTargetForItems(
										BHandler* _handler );
				
				void				SetTargetForItems(
										BMessenger _messenger );
				
				BTool*				ToolAt(
										int32 _index ) const;
										
				int32				IndexOf(
										BTool* _tool) const;
										
		nu_border_style				BorderStyle() const;
		
			orientation				Orientation() const;
			
				void				SetStyleForTools(nu_button_style);
				
				void				SetCollapsed(bool);
				
				bool				IsCollapsed() const;
					
	private :
				void				PlaceTool(
										BTool* _tool );
				void				PlaceTool(
										BTool* _tool,
										int32 _at_index );
		  BMenuItem*				NewMenuItem(
		  								BTool* _tool );
		
		virtual void				_ReservedMethod1();
		virtual void				_ReservedMethod2();
		virtual void				_ReservedMethod3();
		virtual void				_ReservedMethod4();
		virtual void				_ReservedMethod5();
		virtual void				_ReservedMethod6();
		virtual void				_ReservedMethod7();
		virtual void				_ReservedMethod8();
		virtual void				_ReservedMethod9();
		virtual void				_ReservedMethod10();

	private :
				BTool*				fArrowTool;
				BTool*				fDoubleArrowTool;
				BList				fTools;
				orientation			fOrientation;
				nu_border_style		fBorderStyle;
				bool				enabled;
				bool				collapsed;
								
				uint32				_ReservedData[ 10 ];
};

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BToolBar;
using Z::Experimental::Interface::nu_border_style;
using Z::Experimental::Interface::BS_NO_BORDER;
using Z::Experimental::Interface::BS_PLAIN_BORDER;
using Z::Experimental::Interface::B_TOOLBAR_EXPANDED;
using Z::Experimental::Interface::B_TOOLBAR_COLLAPSED;
#endif

#endif /* _TOOLBAR_H_ */
