/*
  -----------------------------------------------------------------------------

	File: BitmapMenuItem.h
	
	Description: A menu item with a bitmap on the left.
	
	Copyright 2003, 2004, yellowTAB GmbH, All rights reserved.
	
	Developer: Owen Smith and others.

  -----------------------------------------------------------------------------
*/

#ifndef BITMAPMENUITEM_H
#define BITMAPMENUITEM_H

#include <interface/MenuItem.h>

class BBitmap;
class BMessage;
class BMenu;

namespace Z {
namespace Interface {
	
class BBitmapMenuItem : public BMenuItem
{
	public:
						BBitmapMenuItem( const char* _label, BBitmap* _bitmap, BMessage* _message = NULL);
						BBitmapMenuItem( BMenu* _submenu, BBitmap* _bitmap, BMessage* _message = NULL);
		virtual 		~BBitmapMenuItem();
	
		virtual	void	GetContentSize( float* _width, float* _height );
		virtual void	DrawContent();
	
		virtual void	TruncateLabel( float _maxWidth, char* _newLabel );
	
				void	SetBitmapAutoDestruct( bool _state );
				bool	BitmapAutoDestruct() const;
			BBitmap*	Bitmap() const { return fBitmap; };
	
	protected:
		BBitmap*	fBitmap;
		float		fBitmapDeslX;
		float		fBitmapDeslY;
	
	private:
				void	Init();
	
	private:
		bool		fBitmapAutoDestruct;
		float		fTitleAscent;
		float		fTitleDescent;
};

}
}

#ifndef _ZETA_EXPLICIT_NAMESPACE_
	using Z::Interface::BBitmapMenuItem;
#endif


#endif
