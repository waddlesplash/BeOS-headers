#ifndef SPYDATA_H
#define SPYDATA_H

#include <Locker.h>
#include <Message.h>


#define B_SPY_DATA_MESSAGE	'_SDM'
#define B_SPY_LOCAL			"be:Spy-O-Matic:LocalSpy"

namespace Spy {

class SpyData
{
	public:
		SpyData();
		~SpyData();
		
		BMessage& Data();
	
	private:
	
		static BLocker sLock;
		static BMessage sDataMessage;

};	// DataAccess


}	// Spy

#endif

