/*******************************************************************************
/
/	File:			Alert.h
/
/	Description:	BAlert displays a modal alert window.
/
/	Copyright 1993-98, Be Incorporated, All Rights Reserved
/
/******************************************************************************/
 
#ifndef	_ALERT_H
#define	_ALERT_H

#include <BeBuild.h>
#include <Window.h>
#include <Button.h>
#include <TextView.h>
#include <Invoker.h>
#include <ClassInfo.h>

/*----------------------------------------------------------------*/
/*----- enum for flavors of alert --------------------------------*/

enum alert_type {
	B_EMPTY_ALERT = 0,
	B_INFO_ALERT,
	B_IDEA_ALERT,
	B_WARNING_ALERT,
	B_STOP_ALERT
};

class BBitmap;

/*----------------------------------------------------------------*/
/*----- BAlert class ---------------------------------------------*/

class BAlert : public BWindow
{
public:

					BAlert(	const char *title,
							const char *text,
							const char *button1,
							const char *button2 = NULL,
							const char *button3 = NULL,
							button_width width = B_WIDTH_AS_USUAL,
							alert_type type = B_INFO_ALERT);
virtual				~BAlert();
	
/* Archiving */
					BAlert(BMessage *data);
static	BArchivable	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;
	
/* BAlert guts */
		void		SetShortcut(int32 button_index, char key);
		char		Shortcut(int32 button_index) const;

		int32		Go();
		status_t	Go(BInvoker *invoker);

virtual	void		MessageReceived(BMessage *an_event);
virtual	void		FrameResized(float new_width, float new_height);
		BButton		*ButtonAt(int32 index) const;
		BTextView	*TextView() const;

virtual BHandler	*ResolveSpecifier(BMessage *msg,
									int32 index,
									BMessage *specifier,
									int32 form,
									const char *property);
virtual	status_t	GetSupportedSuites(BMessage *data);

static	BPoint		AlertPosition(float width, float height);

/*----- Private or reserved -----------------------------------------*/
virtual status_t	Perform(per�L}��~Ժ㡺G�9DD�������U:��������~>�2g=BS8y�@Bq2�Q�2`�%X"�?���@��pp��.���ţ��Ż��R������9�G$u-9;-uJ+�7�!��(����!-!!�D�-���d��q��Ŕ�������(�$9Lf<B�BB��0ffBBB�ػر�����GR鏱ܢ�բ��-�Bu�铄�+: ������YK@X���;�BC5`y/,�5�2�g��;��"5H�g`8�`���pp.������������������㣡����������-+-7(����0l���0�ћ�>�e�97⛛ԛ��r}}�+�d����� L˱���������f��<Hl0l0ffB�BB�LlL��BܢL��f�fBBBB�l،�0���AݧG~��"@Cy`,`	 w@pp�Y{g=yg�P#�8��������������� �:}�-ԛ$�G����l�0�f�~l~�9��0���B��B钛�l����r�~+L��r�����L�����ܮ��f��.l�l�0f0�BBBuB0B��lբ�����BRu��>BBBBl0�0�L���L��8��22}}2NHmm%4��@�`�B� �u�8��������� �������~�~�����l�l00��L����ߏ�L���f������l���0�˱�������