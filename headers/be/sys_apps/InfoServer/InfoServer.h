/*
  -----------------------------------------------------------------------------

	File:				InfoServer.h
	
	Description:		API to create and send information to the info_server

	Implementation:		Karsten Heimrich
	
	Copyright 2005, 2006 yellowTab GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/

#ifndef _INFO_SERVER_H_
#define _INFO_SERVER_H_

#include <app/Message.h>
#include <app/Messenger.h>
#include <experimental/StringList.h>
#include <interface/Rect.h>
#include <storage/Entry.h>
#include <support/String.h>
#include <sys/time.h>

class BBitmap;

namespace Z {
	namespace SysApps {	

enum info_type
{
	itInformation,
	itImportant,
	itError
};

enum icon_source
{
	isAttribute,
	isFile
};

// class BInfoServer -----------------------------------------------------------------------------
class BInfoServer 
{
	public:
							BInfoServer(const BString _name);
							~BInfoServer();

		status_t			InitCheck();
		
		status_t			SetInfoType(info_type _type);
		info_type			GetInfoType() const;
		
		status_t			SetAppName(BString _name);
		BString				GetAppName() const;
		
		status_t			SetInfoTitle(BString _title);
		BString				GetInfoTitle() const;

		time_t				GetDisplayTime() const;

		// Info view decoration
		status_t			SetImage(BBitmap* _image);
		status_t			SetImage(const BBitmap& _image);
		status_t			SetImage(const entry_ref& _ref, icon_source _source);
		void				RemoveImage();
				
		status_t			SetOverlayImage(BBitmap* _image);
		status_t			SetOverlayImage(const BBitmap& _image);
		status_t			SetOverlayImage(const entry_ref& _ref, icon_source _source);
		void				RemoveOverlayImage();
		
		BRect				GetMaxImageSize() const;

		// Info view on-click commands
		status_t			SetClickAppAction(const BString _app_signature, 
											  const BStringList _argv_list, 
											  const BString _label = BString());
											  
		status_t			SetClickAppAction(const BString _app_signature, 
											  const entry_ref& _ref,
											  const BString _label = BString());
											  
		status_t			SetClickAppAction(const BString _app_signature, 
											  const BMessage& _message,
											  const BString _label = BString());
		
		status_t			SetClickFileToOpen(const entry_ref& _ref, const BString _label = BString());
		status_t			SetClickCommand(const BString _command, const BString _label = BString());

		void				RemoveClickLabel();		
		void				RemoveClickAction();

		// 'Popping' info for the user.
		void				ShowInfo(const BString _text);
		void				ShowInfo(const BString _text, 
							         const BString _title, 
							         info_type _type = itInformation);

	private:
		BBitmap*			RescaleImage(const BBitmap* _image, int32 _width, int32 _height = -1);

		void				AddInfoText(const BString _text);
		status_t			AddAppSignature(const BString _app_signature);
		status_t			AddLinkLabel(const BString _label);
						
	private:
		BMessage			fInfoMessage;
		BMessenger			fMessenger;
};

	}	// namespace SysApp
}	// namespace Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_

using Z::SysApps::BInfoServer;

using Z::SysApps::info_type;
using Z::SysApps::itInformation;
using Z::SysApps::itImportant;
using Z::SysApps::itError;
using Z::SysApps::icon_source;
using Z::SysApps::isAttribute;
using Z::SysApps::isFile;

#endif

#endif
