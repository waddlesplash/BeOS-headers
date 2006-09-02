#ifndef PREFERENCES_APP_H
#define PREFERENCES_APP_H

class BView;
class BRect;

#include <app/Messenger.h>
/* 
	This is a typedef for the function pointer that the Preferences application
   	uses to get your BView pointer back from. Your declaration of this function
   	must look like:
   
		extern "C" BView* get_pref_view(const BRect& Bounds)

   in order for the Preferences app to be able to load it.
*/


typedef BView*(*PrefsViewFactory)(const BRect& Bounds);

#include <interface/Screen.h>
// The left and top location of the PrefView titles, and the size that the text is.
#define PREF_TITLE_LEFT			(BScreen().Frame().Width() < 799 ? 10 : 45)
#define PREF_TITLE_TOP			(BScreen().Frame().Width() < 799 ? 10 : 30)
#define PREF_TITLE_FONT_SCALE	1.3
#define SetTitleFont(view)		{ 	BFont _tfont_(*be_bold_font); \
									_tfont_.SetSize(_tfont_.Size() * PREF_TITLE_FONT_SCALE); \
									view->SetFont(&_tfont_); }	




// Messages that Preference Addons get/use

// Send this message to the view's Parent() each time the addon can revert the settings.
#define B_PREF_APP_ENABLE_REVERT	'zPAE'
#define B_PREF_APP_DISABLE_REVERT	'zPAS'
#define PrefEnableRevert(enable)	BMessenger(this->Parent()).SendMessage(enable ? B_PREF_APP_ENABLE_REVERT : B_PREF_APP_DISABLE_REVERT)

// Send this message to the view's Parent() if the pref has default settings any time your pref is Show()n.
#define B_PREF_APP_ENABLE_DEFAULTS	'zPED'
#define B_PREF_APP_DISABLE_DEFAULTS	'zPDD'
#define PrefEnableDefaults(enable)	BMessenger(this->Parent()).SendMessage(enable ? B_PREF_APP_ENABLE_DEFAULTS : B_PREF_APP_DISABLE_DEFAULTS)

// The addon will get theis message when the user preses the "Defaults" button.
#define	B_PREF_APP_SET_DEFAULTS		'zPAD'

// Sometimes you want the pref window to reload itself, this happens when the language or resolution changes.
#define	B_PREF_APP_WINDOW_RELOAD	'zPAW'


// The addon will get this message when the user presses the "Revert" button.
#define	B_PREF_APP_REVERT			'zPAR'

// The addon will get this message with an entry_ref 'ref' feild for the addon's ref.
// This is useful for loading resources locaed in the addon's file. Your addon
//  will get this message before it is attached to the window.
#define	B_PREF_APP_ADDON_REF		'zPAA'

// The addon will get this message containing several strings telling it to focus itself
// and optionally a specific control to lay focus on
#define B_PREF_APP_FOCUS			'zPAF'

// The addon will get this message when shown if there are arguments to be sent to it
// with a message field called B_PREF_APP_ARGS, with string fields in it also called B_PREF_APP_ARGS
#define B_PREF_APP_ARGS_RECEIVED	'zPAA'
extern const char*	B_PREF_APP_ARGS;

// The signature of the preference application.
extern const char*	B_PREF_APP_SIG;

// Your pref 'link' object should have this mime signature.
extern const char*	B_PREF_ADDON_SIG;

#endif
