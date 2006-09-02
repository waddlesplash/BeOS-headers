/*
  -----------------------------------------------------------------------------

	File: Timespan.h
	
	Date: Thursday October 28, 2004

	Description: Support class for time manipulation.
	
	Copyright 2004, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _BTIMESPAN_H_
#define _BTIMESPAN_H_

#include <be_prim.h>

namespace Z {
namespace Support {

	class BTimespan
	{
		public:
			BTimespan();
			BTimespan(int32 _seconds);
			BTimespan(const BTimespan &_copy);

			int32 		Duration() const;
			void		SetDuration(int32 _seconds);
			
			BTimespan&	Add(const BTimespan &_duration);
			BTimespan&	Subtract(const BTimespan &_duration);
		
			BTimespan&	AddDays(int32 _days);
			BTimespan& 	AddWeeks(int32 _weeks);
			BTimespan&	AddYears(int32 _years);
			
			BTimespan&	SubtractDays(int32 _days);
			BTimespan&	SubtractWeeks(int32 _weeks);
			BTimespan&	SubtractYears(int32 _years);
		
			BTimespan& 	operator+(BTimespan &_duration);
			BTimespan&	operator-(BTimespan &_duration);
			BTimespan&	operator=(BTimespan &_copy);
		
		private:
			int32 fSeconds;
	};

} // ns Support
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Support::BTimespan;
#endif

#endif // _BTIMESPAN_H_
