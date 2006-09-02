/*
  -----------------------------------------------------------------------------

	File: Separator.h
	
	Date: March 25th, 2004

	Description: A 3d separator line to group UI objects without having to use
	             a BBox. Has an optional view/label, just like BBox.
	
	
	Copyright 2004, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _SEPARATOR_H
#define _SEPARATOR_H

#include <interface/View.h>
#include <support/String.h>
#include <support/Vector.h>
#include <locale/LanguageNotifier.h>

namespace Z {
namespace Interface {

// Left = top and Right = bottom for B_VERTICAL orientation.
enum label_position
{
	lpFarLeft,
	lpLeft,
	lpCenter,
	lpRight,
	lpFarRight	
};


class BSeparator : public BView
{
	public:
								BSeparator(const BRect& _frame,
								           const char* _name, 
								           const BString& _label = BString(),
								           orientation _orientation = B_HORIZONTAL,
								           uint32 _resize = B_FOLLOW_LEFT | B_FOLLOW_TOP);
	
								BSeparator(const BRect& _frame,
								           const char* _name, 
								           BView* _label,
								           orientation _orientation = B_HORIZONTAL,
								           uint32 _resize = B_FOLLOW_LEFT | B_FOLLOW_TOP);

								BSeparator(BMessage* _data);
		static	BArchivable		*Instantiate(BMessage* _data);
		virtual	status_t		Archive(BMessage* _data, bool _deep = true) const;



				orientation		GetOrientation() const;
				void			SetOrientation(orientation _orient);

				label_position	GetLabelPos() const;
				void			SetLabelPos(label_position _pos);

		const	BString&		GetLabel() const;
				void			SetLabel(const BString& _label);

				bool			HasViewLabel() const;				
				BView&			GetViewLabel();
				void			SetViewLabel(BView* _view);
				BView*			RemoveViewLabel();		
				
		virtual	void			Draw(BRect _update);
		virtual	void			GetPreferredSize(float* _width, float* _height);
		virtual	void			AttachedToWindow();
		virtual	void			MessageReceived(BMessage* _message);
		virtual	void			FrameResized(float _width, float _height);
	
// ----------------  Private or reserved -------------------------------------------------		


	private:
				void			SetupLayout();
				void			CalcLabelPos();
				void			SetupLines();			
				void			SwapPoint(BPoint& _pt);
		
		virtual	void			Reservoir1();		
		virtual	void			Reservoir2();		
		virtual	void			Reservoir3();		
		virtual	void			Reservoir4();		
		virtual	void			Reservoir5();		
		virtual	void			Reservoir6();		
		virtual	void			Reservoir7();		
		virtual	void			Reservoir8();		
				
	private:
	
		struct line
		{
			line() {}
			line(const BPoint& _start, 
			     const BPoint& _end,
			     const rgb_color& _color)
			     :start(_start)
			     ,end(_end)
			     ,color(_color) {}
			     
			BPoint		start;
			BPoint		end;
			rgb_color	color;
		};
			
		BString				fLabel;
		const char*			fLabelTranslation;
		orientation			fOrientation;
		label_position		fLabelPos;
		B::Support::
		BVector<line>		fLines;
		BPoint				fLabelPoint;
		BLanguageNotifier	fNotifier;
		
		uint32				fDam[8];
		
		
};


}	// ns Interface
}	// ns Z


#ifndef _ZETA_EXPLICIT_NAMESPACE
using Z::Interface::BSeparator;
using Z::Interface::label_position;
#endif


#endif	// _SEPARATOR_H
