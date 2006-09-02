/*
  -----------------------------------------------------------------------------

	File: CalendarControl.h
	
	Date: Wednesday November 10, 2004

	Description: Nice friendly GUI Calendar widget.
	
	Copyright 2004, yellowTAB GmbH, All rights reserved.
	

  -----------------------------------------------------------------------------
*/

#ifndef _CALENDARCONTROL_H_
#define _CALENDARCONTROL_H_

#include <experimental/CalendarEventData.h>
#include <interface/Control.h>
#include <support/DateTime.h>
#include <support/KeyedVector.h>
#include <support/Vector.h>

class BMenu;
class BMenuField;
class BTextControl;

namespace Z {

namespace Support {
	class BTimespan;
}

namespace Experimental {
	namespace Interface {
		namespace Private {
			class YearView;
		}
	}
	
	namespace Interface {
	
	enum CalendarViewMode 
	{
		B_CALENDAR_MONTH_VIEW,
		B_CALENDAR_YEAR_VIEW
	};
	
	enum CalendarNotificationType 
	{
		B_CALENDAR_EVENT_ADDED,
		B_CALENDAR_EVENT_REMOVED,
		B_CALENDAR_EVENT_MODIFIED
	};
	
	class BCalendarEventData;
	class BCalendarEvent;
	
	/**
	 * @short A structure containing all the info needed for the painter to draw a given day.
	 * @param day The current day being drawn.
	 * @param month The current month being drawn.
	 * @param year  The current year being drawn.
	 * @param isSelected  Indicates whether or not the day being drawn is currently selected
	 * @param frame  The frame rectangle of the current calendar square..
	 * @param events  A vector of indices into the calendar's BCalendarEventData object, representing
	 *                all the events that begin, overlap, or end on the currently drawn day.
	 */
	struct DayInfo
	{
		uint8 				day;
		uint8 				month;
		int32 				year;
		bool 				isSelected;
		BRect 				frame;
		BVector<size_t> 	events;	
	};
	
	class BCalendarControl;

/**
 * @short A simple helper class that's used to draw the
 *        content of the individual squares that compose the calendar grid.
 */	
	class BCalendarGridPainter
	{
		public:
			BCalendarGridPainter();
			
			virtual void DrawContentArea(DayInfo &_info,
				BView &_drawer, const BCalendarControl &_parent);
	};

/**
 * @short A general-purpose calendar widget with event data storage and
 * display capabilities.
 * @author Rene Gollent
 */
	class BCalendarControl : public BControl
	{
		public:
			/** Standard BControl type contructor with some additional parameters:
			 *  @param _data The set of events the control is to store and display by
			 *               default. Not passing this in will simply result in a default empty dataset.
			 *  @param _painter The painter to use for the contents of the calendar. Again not passing
			 *               one in will result in the use of a default painter which displays the day
			 *               as a number in the corner of the rect as well as displaying single/multi-day
			 *               events. To override drawing of the grid simply create your own subclass
			 *               which implements the DrawContentArea virtual as documented above.
			 *  @param _time The date/time that is currently selected. By default today.
			 */
								BCalendarControl(BRect _frame, 
								                 const char* _name, 
								                 const char* _label,									
								                 BMessage* _msg, 
								                 BCalendarEventData& _data = BCalendarEventData::Default(),									
								                 BCalendarGridPainter* _painter = NULL, 
								                 uint32 _resize = B_FOLLOW_LEFT | B_FOLLOW_TOP, 									
								                 uint32 _flags = B_WILL_DRAW, 
								                 const BDateTime& _time = BDateTime());
			
		    /**
		     * Standard destructor
		     */					                 
			virtual 			~BCalendarControl();
			
			virtual void 		AttachedToWindow();
			virtual void 		Draw(BRect _frame);
			virtual void 		MessageReceived(BMessage *_msg);
			virtual	void		MouseDown(BPoint _pt);
			virtual	void		MouseUp(BPoint _pt);
			virtual	void		MouseMoved(BPoint _pt, 
								           uint32 _transit, 
								           const BMessage* _msg);
			virtual	void		KeyDown(const char *_bytes, int32 _numBytes);
			
			/**
			 * Override used to show the events of the day as a tooltip
			 */
			virtual status_t	GetToolTipInfo(BPoint _where, 
								               BRect* _outViewRegion,									
								               BToolTipInfo* _outInfo = NULL);
			
			/**
			 * Retrieves and sets the BMessage sent when the selection changes.
			 */
			const BMessage*		SelectionMessage() const;
			void				SetSelectionMessage(BMessage* _msg);
			
			/**
			 * Retrieves and sets the BMessage sent when a day is double-clicked.
			 */
			const BMessage*		InvocationMessage() const;
			void				SetInvocationMessage(BMessage* _msg);
		
			/**
			 * Retrieves and sets the BMessage sent when the event data associated with
			 * the calendar is modified in any way.
			 */
			const BMessage*		EventModificationMessage() const;
			void				SetEventModificationMessage(BMessage* _msg);

			/**
			 * Hook function that's called when modifications are made to event data.
			 */
			virtual void		EventsModified(uint32 _eventType, ssize_t _index);
		
			/**
			 * Retrieves and sets the currently selected date.
			 */
			const BDateTime&	SelectedDate() const;
			void				SetSelectedDate(const BDateTime& _newdate, bool _scrollToSelection = true);

			virtual void		SelectionChanged();
			
			void				ScrollToSelection();		
			
			bool				IsSelectorVisible() const;
			void				SetSelectorVisible(bool _visible);

			/**
			 * Retrieves and sets the BCalendarEventData object that is currently being used as the
			 * calendar's event data store..
			 */
			const BCalendarEventData &EventData() const;
			void				SetEventData(BCalendarEventData& _data);

			// this pair of functions allows the calendar to be set into a
			// read-only mode whereby its selected date can only be altered
			bool				IsSelectable() const;
			void				SetSelectable(bool _selectable);
			
			/**
			 * Modifies the calendar's view mode -- currently supported modes
			 * are month and year view, though year view is presently buggy.
			 */
			CalendarViewMode 	ViewMode() const;
			void				SetViewMode(CalendarViewMode _mode);
			
		protected:
			uint8				GetDayForPoint(BPoint _pt) const;
		
		private:
			friend class 		Z::Experimental::Interface::Private::YearView;
			
			void				DrawHeader();
			void				DrawMonthGrid();
			void				DrawYearGrid();
			
			BRect				GetHeaderRect() const;
			BRect				GetSelectorRect() const;
			BRect				GetGridRect() const;
			
			void				CreateSelectorControls();
			
			virtual void		_ReservedVirtual1();
			virtual void		_ReservedVirtual2();
			virtual void		_ReservedVirtual3();
			virtual void		_ReservedVirtual4();
			virtual void		_ReservedVirtual5();
			virtual void		_ReservedVirtual6();
			virtual void		_ReservedVirtual7();
			virtual void		_ReservedVirtual8();
			virtual void		_ReservedVirtual9();
			virtual void		_ReservedVirtual10();
			
		private:
			BDateTime 					fCurrentTime;
			int32						fOldTime;
			BMessage*					fInvocationMessage;
			BMessage*					fEventMessage;
			BMenuField*					fMonthSelector;
			BTextControl*				fYearSelector;
			BCalendarEventData&			fEventData;
			bool						fShowSelector;
			bool						fSelectable;
			CalendarViewMode			fViewMode;
			BCalendarGridPainter*		fGridPainter;
			char 						_padding[32];
			
			bigtime_t					fLastClick;
	};

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::BCalendarControl;
using Z::Experimental::Interface::BCalendarGridPainter;
#endif

#endif // _CALENDARCONTROL_H_
