//******************************************************************************
//
//	File:		PhonePanel.h
//
//	Description:	BPhonePanel class interface
//
//	Written by:	Eric Knight
//
//	Copyright 1992-3, Be Incorporated
//
//	Change History:
//
//	12/16/92	ehk	new today
//	2/4/93		ehk	got rid of dir. view, related 2 buttons,
//				and name textedit view; added volume
//				radio buttons
//
//******************************************************************************

#ifndef _PHONE_PANEL_H
#define	_PHONE_PANEL_H

#ifndef _INTERFACE_KIT_H
#include <InterfaceKit.h>
#endif
#ifndef _PHONE_H
#include <Phone.h>
#endif

//------------------------------------------------------------------------------

class TCluster;

class TGroupedRadio : public BRadioButton {
public:
	TCluster*	fCluster;

	void		TGroupedRadio(char *name, BRect *r, char *label, 
				      TCluster* cluster, long code, 
				      long resizeMask = FOLLOW_LEFT_TOP, 
				      long flags = WILL_DRAW);
virtual	void		SetValue(long v);

};

//------------------------------------------------------------------------------

class	TCluster {
public:
	void		TCluster();
	void		SetButtons(TGroupedRadio* r1, TGroupedRadio* r2, 
				   TGroupedRadio* r3, TGroupedRadio* r4);

	TGroupedRadio*	fR1;
	TGroupedRadio*	fR2;
	TGroupedRadio*	fR3;
	TGroupedRadio*	fR4;
};

//------------------------------------------------------------------------------

class BCheckBox;
class BButton;
class BTextView;

class BPhonePanel : BWindow {
	
public:
			BPhonePanel(BRect *frame, char *title, 
				    window_type type, long flags, 
				    BPhone* phone = NIL);
virtual			~BPhonePanel();

virtual	void		handle_commands(long msg);
	void		CloseRequest();

	bool		CloseHit();
		
private:
	BRect*		AdjustRect(BRect* original);

	bool		fCloseHit;
	bool		fCreatedPhone;
	BPhone*		fPhone;
	BCheckBox*	fDial9Box;
	BButton*	fDialButton;
	BTextView*	fNumberText;
};

//------------------------------------------------------------------------------

#endif
