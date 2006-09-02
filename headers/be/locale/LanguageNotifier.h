// Stack based proxy for registering you BHandler derivative
// to receive language changed notification messaged (B_LANGAUGE_CHANGED)

#ifndef LANGUAGE_NOTIFIER_H
#define LANGUAGE_NOTIFIER_H

class BHandler;

namespace Z {
namespace Locale {

class BLanguageNotifier
{
	public:
				BLanguageNotifier();
				~BLanguageNotifier();
				
				// Use this on your object after it has been
				// added to a looper, like in AttachedToWindow()
		void	SetTarget(BHandler* Handler);
	
	private:
		BHandler* fHandler;	
};

}	//  Locale
}	//	Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Locale::BLanguageNotifier;
#endif


#endif
