#ifndef REPLACER_H
#define REPLACER_H

namespace Z {
namespace Locale {

class BReplacer
{
	public:
		const	char*	key;
		const	char*	value;

							BReplacer(const char* Key, const char* Value);
				
				void		SetTo(const char* Key, const char* Value);
	private:
							BReplacer() {}
	
};

}	//  Locale
}	//	Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Locale::BReplacer;
#endif

#endif

