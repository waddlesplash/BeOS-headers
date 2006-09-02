#ifndef LOCALE_H
#define LOCALE_H

#include <app/Messenger.h>
#include <interface/Rect.h>
#include <support/DateTime.h>
#include <support/KeyedVector.h>
#include <support/ReadWriteLocker.h>
#include <support/String.h>

#include <locale/Paramable.h>

class BApplication;
class BHandler;
class BBitmap;
struct entry_ref;


namespace Z {
namespace Locale {

class BLanguageNotifier;

class BLocale
{
	public:

	typedef BKeyedVector<BString, BString>		BDictionary;
	typedef BOrderedVector<BString>		 		BStringList;
	typedef BOrderedVector<const BHandler*>		BHandlerPtrList;

							BLocale();
							~BLocale();
								
		const	char*		GetString(const char* Key);
		const	BString&	GetBString(const char* Key);
				BParamable	GetParamStr(const char* Key);	
		
				BString		GetLanguageName(const char* LongName = NULL);
				BString		GetLanguageShortName(const char* ShortName = NULL);
				
				BBitmap*	GetFlagBitmap(const char* Language = NULL);
				BBitmap*	GetFlagBitmap(const BRect& Rect, const char* Language = NULL);
				entry_ref	GetFlagFile(const char* Language = NULL);

				void		GetAvailableLanguages(BStringList& List);						
				void		SetLanguage(const char* LanguageName);
				void		RefreshDictionaries();
				
				void		SetSynchronizeKeymap(bool Synchronize);
				bool		IsKeymapSynchronized();
	
				void		SetSynchronizeFont(bool Synchronize);
				bool		IsFontSynchronized();
	
				void		InvalidateCache();

				status_t	LoadLanguageFile(const char* FileBasePath);

		const	char*		GetDateFormatString();
		const	char*		GetDateString();
		const	BString&	GetDateBString();
		const	BString&	GetDateFormatBString();

		const	char*		GetTimeFormatString();
		const	char*		GetTimeString();
		const	BString&	GetTimeBString();
		const	BString&	GetTimeFormatBString();
						
				Z::Support::
				week_mode	GetWeekStart();
		
		const	char*		GetMoneySymbol();
		const	char*		GetDecimalSymbol();
		const	char*		GetThousandsSeparator();
		
	private:
				void		SendMessage(BMessage& Message);
				void		LoadLocal();				
				void		ExtractTranslationPairs(const BMessage& Message);
				void		SubscribeLanguageChanges(const BHandler* Handler);
				void		UnsubscribeLanguageChanges(const BHandler* Handler);
				void		LanguageChanged(BMessage* Message);
		const	BString&	GetSpecialSymbol(const char* SymId, const char* DefaultResult);	

	public:
				// not recommended to use this.
				void		SetLocaleServerMessenger(const BMessenger& _server);	
						
	private:

		BMessenger			fServer;
		BDictionary			fDictionary;
		BReadWriteLocker	fLock;
		BHandlerPtrList		fNotificationHandlers;
		BReadWriteLocker	fNotificationLock;
		bool				fDumpKeyRequests;
		uint32				fStateFlags;		
		uint32				fPaddington[4];	
			
		friend class BLanguageNotifier;
		friend class ::BApplication;
};

extern BLocale be_locale;

// Conveniant Macros
#define _T(str)				be_locale.GetString(str)
#define _TBS(str)			BString(_T(str))
#define _TCBS(str)			be_locale.GetBString(str)
#define _TPS(str)			be_locale.GetParamStr(str)

// Old style
#define GETSTRING(str)		_T(str)

}	//  Locale
}	//	Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Locale::BLocale;
using Z::Locale::be_locale;
#endif


#endif

