//******************************************************************************
//
//	File:		Dragger.h
//
//	Description:
//
//	Copyright 1997, Be Incorporated
//
//******************************************************************************


#ifndef _DRAGGER_H
#define _DRAGGER_H

#include <Locker.h>
#include <List.h>
#include <View.h>
#include <Message.h>

class _TShelfFilter_;
class BShelf;
class BBitmap;

class BDragger : public BView {
public:
					BDragger(BRect bounds,
								BView *target,
								uint32 rmask = B_FOLLOW_NONE,
								uint32 flags = B_WILL_DRAW);
					BDragger(BMessage *data);

virtual				~BDragger();
static	BDragger	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;

virtual void		AttachedToWindow();
virtual void		DetachedFromWindow();
virtual void		Draw(BRect update);
virtual void		MouseDown(BPoint where);
virtual	void		MouseUp(BPoint pt);
virtual	void		MouseMoved(BPoint pt, uint32 code, const BMessage *msg);
virtual void		MessageReceived(BMessage *msg);
virtual	void		FrameMoved(BPoint new_position);
virtual	void		FrameResized(float new_width, float new_height);

static	status_t	ShowAllDraggers();			// system wide!
static	status_t	HideAllDraggers();			// system wide!
static	bool		AreDraggersDrawn();

virtual BHandler	*ResolveSpecifier(BMessage *msg,
									int32 index,
									BMessage *specifier,
									int32 form,
									const char *property);
virtual status_t	GetSupportedSuites(BMessage *data);
virtual status_t	Perform(uint32 d, void *arg);

protected:
		bool		IsVisibilityChanging() const;

private:

friend class _TShelfFilter_;
friend class BShelf;
friend void _toggle_handles_(bool);

virtual	void		_ReservedDragger1();
virtual	void		_ReservedDragger2();
virtual	void		_ReservedDragger3();
virtual	void		_ReservedDragger4();

		BDragger	&operator=(const BDragger &);

		void		ListManage(bool);
		status_t	determine_relationship();
		status_t	SetViewToDrag(BView *target);
		void		SetShelf(BShelf *);
		void		ShowPopUp(BView *target, BPoint where);
static	bool		sVisible;
static	bool		sInited;
static	BLocker		sLock;
static	BList		sList;

		enum relation {
			TARGET_UNKNOWN,
			TARGET_IS_CHILD,
			TARGET_IS_PARENT,
			TARGET_IS_SIBLING
		};

		BView		*fTarget;
		relation	fRelation;
		BShelf		*fShelf;
		bool		fTransition;
		BBitmap		*fBitmap;
		uint32		_reserved[4];
};

#endif
