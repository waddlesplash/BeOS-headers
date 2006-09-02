/*
  -----------------------------------------------------------------------------

	File: DateTime.h
	
	Date: Thursday October 28, 2004

	Description: Support class for easy date/time manipulation and representation.
	
	Copyright 2004, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _BDATETIME_H_
#define _BDATETIME_H_

#include <support/String.h>

#include <be_prim.h>
#include <time.h>

namespace Z {
namespace Support {
	
	enum week_mode {
		B_WEEK_ON_SUNDAY = 0,
		B_WEEK_ON_MONDAY = 1
	};
	
	class BTimespan;
	
	class BDateTime
	{
		public:
			BDateTime();
			BDateTime(time_t _unixtime);
			BDateTime(uint8 day, uint8 month, int32 year);
			BDateTime(const BString &_humanDate);
			BDateTime(const BDateTime &_copy);

			uint8				Day() const;
			uint8				Month() const;
			int32				Year() const;
			uint8				Hour() const;
			uint8				Minute() const;
			uint8				Seconds() const;
			uint8				DaysInMonth() const;
			int8				TimeZone() const;
			bool				IsLeapYear() const;
			
			week_mode			WeekMode() const;
			void				SetWeekMode(week_mode);
			
			uint8				Week() const;
			uint8				WeekDay() const;
			
			uint16				DayInYear() const;

			status_t			SetDay(uint8 _newday);
			status_t			SetMonth(uint8 _newmonth);
			status_t			SetYear(int32 _newyear);
			status_t			SetTimeZone(int8 _tzoffset);
			status_t			SetHour(uint8 _newhour);
			status_t			SetMinute(uint8 _newminutes);
			status_t			SetSeconds(uint8 _newseconds);
			
			status_t			SetFromTimestamp(time_t _unixtime);
			time_t				AsTimestamp();
			
			status_t			SetFromString(const BString &_humanDate);
			
			BDateTime&			Add(const BTimespan &_duration);
			BDateTime&			Subtract(const BTimespan &_duration);
			BTimespan			Difference(const BDateTime &_other) const;
			
			// returns an ascii representation of the date
			// with optional strftime argument to allow user-specifiable
			// format - defaults to Locale-specific DateTimeFormatString
			BString				ToString(const BString &_format = BString()) const;
			
			// these two functions compare by ignoring some of the datetime's
			// data as specified, and return a result with semantics comparable to
			// strcmp (1 if this is >, -1 if this is <, 0 if equal)			
			int8				CompareByDate(const BDateTime &_other) const;
			int8				CompareByTime(const BDateTime &_other) const;		
		
			BDateTime&			operator=(const BString &_input);
			bool				operator==(const BDateTime &_other) const;
			bool				operator!=(const BDateTime &_other) const;
			bool				operator<(const BDateTime &_other) const;
			bool				operator<=(const BDateTime &_other) const;
			bool				operator>(const BDateTime &_other) const;
			bool				operator>=(const BDateTime &_other) const;
			
		private:
			tm					fTimeData;
			week_mode			fWeekMode;
			time_t				fCachedTime;
			
			char 				_PaddingForTheCat[28];
	};

	BString&			operator<<(BString &_lhs, const BDateTime &_rhs);

} // ns Support
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Support::BDateTime;
#endif // _ZETA_EXPLICIT_NAMESPACE_

#endif // _DATETIME_H_
