/*
  -----------------------------------------------------------------------------

	File: CalendarEventData.h
	
	Date: Monday November 22, 2004

	Description: Definition for calendar event data storage as used by
					BCalendarControl.
		
	Copyright 2004, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _CALENDAR_EVENT_DATA_H_
#define _CALENDAR_EVENT_DATA_H_

#include <interface/GraphicsDefs.h>
#include <support/DateTime.h>
#include <support/Vector.h>
#include <support/KeyedVector.h>

class BMessenger;

namespace Z {
namespace Experimental {
namespace Interface {

	class BCalendarEvent
	{
		public:
			BCalendarEvent();
			BCalendarEvent(uint32 _id, const BDateTime &_start, const BDateTime &_end,
				const BString &_name, const rgb_color &_color);
			BCalendarEvent(const BCalendarEvent &_other);
			
			bool	operator==(const BCalendarEvent &_other) const;
			
			uint32 id;
			BDateTime start;
			BDateTime end;
			BString name;
			rgb_color color;
	};

	/**
	 * @short A data storage class for events which is used primarily by BCalendarControl for
	 *        storing and retrieving the events which it is supposed to draw. 
	 */
	
	class BCalendarEventData
	{
		public:
			/**
			 *  Ordinary every day constructor/copy constructor pair
			 */
			BCalendarEventData();
			BCalendarEventData(const BCalendarEventData &_copy);
			
			/**
			 * This pair of calls implements the Observer design pattern. A class can
			 * subscribe to the event data object in order to be sent BMessages when
			 * the data in the object is modified in some way
			 */
			status_t			Subscribe(const BMessenger &_target, uint32 what);
			void				Unsubscribe(const BMessenger &_target);
			
			void				EventsModified(uint32 _eventType, ssize_t _index);

			/**
			 * General purpose functions for manipulating and retrieving from the event data store
			 */
			void				AddEvent(const BCalendarEvent &_event);
			status_t			RemoveEventAt(size_t _index);
			size_t				CountEvents() const;
			const BCalendarEvent& EventAt(size_t _index) const;
			status_t			ReplaceEventAt(size_t _index, const BCalendarEvent &_event);
			
			/**
			 * This function fills in a user-passed BVector with the indices of all events
			 * that begin on, overlap with, or end on _date.
			 */
			void				EventsFor(const BDateTime &_date, BVector<size_t> &_store) const;
			ssize_t				IndexOf(const BCalendarEvent &_event) const;
			
			static BCalendarEventData &Default();
			
		private:
			BKeyedVector<BMessenger, uint32> fSubscribers;
			BVector<BCalendarEvent>	fEvents;
			static BCalendarEventData fDefaultInstance;
	};

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BCalendarEvent;
using Z::Experimental::Interface::BCalendarEventData;
#endif

#endif // _CALENDAR_EVENT_DATA_H_
