//******************************************************************************
//
//	File:		StatusBar.h
//
//	Description:	status bar class.
//
//	Copyright 1996, Be Incorporated
//
//******************************************************************************

#ifndef	_STATUS_BAR_H
#define	_STATUS_BAR_H

#ifndef _VIEW_H
#include <View.h>
#endif

class BStatusBar : public BView {

public:
					BStatusBar(	BRect frame,
								const char *name,
								const char *static_label = NULL,
								const char *trailing_static_label = NULL);
virtual				~BStatusBar();

virtual	void		AttachedToWindow();
virtual	void		MessageReceived(BMessage *msg);
virtual	void		Draw(BRect updateRect);

virtual	void		SetBarColor(rgb_color color);
virtual	void		SetBarHeight(float height);
virtual	void		SetText(const char *str);
virtual	void		SetTrailingText(const char *str);
virtual	void		SetMaximum(float max);

virtual	void		Progress(	float delta,
								const char *main_text = NULL,
								const char *trailing_text = NULL);
virtual	void		Reset(	const char *static_label = NULL,
							const char *trailing_static_label = NULL);
		float		Current() const;
		float		Maximum() const;

private:
		void		SetTextData(char **pp, const char *str);
		void		FillBar(BRect r);
		void		Resize();

		char		*fLabel;
		char		*fTrailingLabel;
		char		*fText;
		char		*fTrailingText;
		float		fMax;
		float		fCurrent;
		float		fBarHeight;
		float		fTrailingWidth;
		rgb_color	fBarColor;
		float		fEraseText;
		float		fEraseTrailingText;
};

#endif
