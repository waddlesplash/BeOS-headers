#include <interface/TextViewCompleter.h>
#include <KeyedVector.h>

namespace Z {
namespace Interface {

struct Person
{
	BString email;	
};

class BEMailCompleter : public BTextViewCompleter
{
	public:
							BEMailCompleter();

				void		CollectPeople();
			
	private:
		B::
		Support::
		BKeyedVector<BString, Person>	fPeople;
};	

} // Interface
} // Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Interface::BEMailCompleter;
#endif

