#ifndef PARAMABLE_H
#define PARAMABLE_H

#include <support/String.h>


namespace Z {
namespace Locale {

class BReplacer;

class BParamable
{
	public:
							BParamable(const char* StringWithParams);
		
		// What to use for replacing params.
		BParamable&			operator <<(const BReplacer& Replacer);
		BParamable&			operator <<(const char* String);
		BParamable&			Replace(const char* This, const char* WithThis);
			
		// How to get the string out.
							operator const char*() const;
		const BString&		AsString() const;
		const char*			String() const;

	private:
		BString		fString;
};

inline
BParamable::operator const char*() const
{
	 return String();
}


// -----------------------------------------------------------------------------
inline
const BString&
BParamable::AsString() const
{
	return fString;
}


inline const char *
BParamable::String() const
{
	 return fString.String();
}

}	//  Locale
}	//	Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Locale::BParamable;
#endif



#endif

