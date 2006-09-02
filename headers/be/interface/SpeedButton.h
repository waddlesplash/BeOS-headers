#ifndef SPEEDBUTTON_H
#define SPEEDBUTTON_H

//-------------------------------------------------------------------------------
//
// SpeedButton
//
// Deco SpeedButton class, a nifty X-style button with a graphic and a label.
// It tries to be as lightweight as possible (but is failing miserably ;).
//
// Author: Alan Westbrook
// Copyright 1999 - 2004, the Deco team. CGSoftware International
//
// Used with permission for the Vision project. (http://vision.sourceforge.net/)
//
// Used with permission for the Zeta project.
//-------------------------------------------------------------------------------


class BLooper;
class BBitmap;

#include <interface/Control.h>
#include <interface/Rect.h>

namespace Z {
namespace Interface {
		
enum BSBStyle
{
	sbFlat,
	sbUp
};

/**
 * @short A nifty X-style button with a graphic..
 * This class is a BButton derivative with some cool features.
 * @author Alan Ellis
 */
class BSpeedButton : public BControl
{
	public:
	    /**
	     * Standard stuff for BButtons with some additions.
	     * @param Label Set this to NULL if you do not wish to have a label drawn on your button.
	     * @param EnabledBitmap The bitmap which shows the button in an enabled state.
	     *                      Copies are made of the b itmaps that you pass in. You still own them.
	     * @param Style Optional style. Avaliable styles are sbFlat (pops up as the mouse goes over it)
	     *              and sbUp, normal looking button.
	     * @param DisabledBitmap Optional look for a disabled bitmap.
	     *                       If this is not supplied, a disabled button will be created from the
	     *                       Enabled bitmap
	     */
	    						BSpeedButton(BRect _frame, 
	    						             const char* _name, 
	    						             const char* _label,
	                 			             BMessage* _message, 
	                 			             BBitmap* _enabledBitmap = NULL,
	                 			             BSBStyle _style = sbFlat,
	                 			             BBitmap* _disabledBitmap = NULL,
	                 			             uint32 _resizingMask = B_FOLLOW_LEFT | B_FOLLOW_TOP,
	                 			             uint32 _flags = B_WILL_DRAW);
	
	    /**
	     * Standard unarchiving constructor.  
	     */					
	    						BSpeedButton(BMessage* _archive);
	
	    /**
	     * Goes with above constructor.  
	     */					
	    static BSpeedButton*	Instantiate(BMessage* _archive);
	
	    /**
	     * Standard destructor.  
	     */					
	    virtual 				~BSpeedButton();
	
	    /**
	     * More archiving stuff.  
	     */					
	    virtual status_t		Archive(BMessage* _archive, bool _deep = true) const;
	
	    virtual void 			AttachedToWindow();
	    virtual void 			DetachedFromWindow();
	    virtual void 			Draw(BRect Frame);
	
	    virtual void 			MouseDown(BPoint _where);
	    virtual void 			MouseUp(BPoint _where);
	    virtual void			MouseMoved(BPoint _where,
								           uint32 _code,
								           const BMessage* _message);
	
	    virtual void			FrameResized(float _width, float _height);
	
	    /**
	     * What style is the button? You need but ask.
	     */					
	    virtual BSBStyle	   Style();
	
	    /**
	     * Set the style.
	     * @param Style Set to one of 'sbFlat' or 'sbUp'. See the constructor for explanation of the vaules.
	     */
	    virtual void			Style(BSBStyle _style);
	
	    /**
	     * Used to 'group' buttons owned by the same view for 'radio' functionality.
	     * @param Index All buttons belonging to the same index will be in the same group. A group index of
	     * -1 indicates a button is not part of any group.
	     */
	    virtual void			GroupIndex(int32 _index);
	
	    /**
	     * Oh great oracle, to which group does my button belong? 
	     */
	    virtual int32			GroupIndex();
	
	    /**
	     * Primarily useful to buttons in Groups or latching, a button is seleced when it is in the 'down' state.
	     */
	    virtual void			Selected(bool _selected);
	    virtual bool			Selected();
	
	    /**
	     * A button that 'latches' will stick down when pressed. If the button is part of a group the other buttons in the
	     * group will become un-latched.
	     */
	    virtual void			Latching(bool _latching);
	    virtual bool			Latching();
	
	    /**
	     *	You may want to show that a button is in a special state, Highlighting can do this for you by drawing an outline
	     *  inside the edge of the button.
	     */
	    virtual void			Highlighted(bool _highlighted);
	    virtual bool			Highlighted();
	    virtual void			HighlightColor(rgb_color _highlightColor);
	    virtual rgb_color		HighlightColor();
	
	protected:

	private:
		virtual	void			_ReservedSB1();
		virtual	void			_ReservedSB2();
		virtual	void			_ReservedSB3();
		virtual	void			_ReservedSB4();
	
	
	private:
				void			SetupBitmaps(const BBitmap& _source);
				void			SetupLabel();
	    
	private:
	    enum BSBDrawState { sbdsDown, sbdsFlat, sbdsUp };
	
		BBitmap*	fDisabledBitmap;
		BBitmap*	fEnabledBitmap;
		BRect		fBitmapSourceRect;
		BRect		fBitmapDestinationRect;
		BRect		fBorder;
		BSBStyle	fStyle;
	    int32		fGroupIndex;
	    rgb_color	fHighlightColor;
	    rgb_color	fEnabledViewColor;
	    BPoint		fLabelPos;
	
	    bool		fActive;
	    bool		fMouseDown;
	    bool		fOutside;
	    bool		fAttachedToWindow;
	    bool		fSelected;
	    bool		fLatching;
	    bool		fHighlighted;	
	    uint32		_paddington[8];
};

}	// Interface
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
	using Z::Interface::BSpeedButton;
#endif

#endif

