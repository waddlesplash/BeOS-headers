
#ifndef _XMLEXPRESSIBLE_H_
#define _XMLEXPRESSIBLE_H_

#include <Atom.h>
#include <XMLParser.h>
#include <XMLWriter.h>

namespace BXmlKit {

class BExpressible : virtual public BAtom
{
	public:
	
										BExpressible();
		virtual							~BExpressible();

		virtual status_t				Code(BCodifier *stream);
		virtual status_t				Parse(BParser **stream);
};

};

#endif
