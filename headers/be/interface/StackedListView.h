/*
 * File:		StackedListView.h
 * Author:		Rene Gollent
 * Company:		yellowTAB
 * Date:		02/18/2004
 * Description:
 * Interface Control which combines a BListView and a BStackedViewManager, yielding a
 * control that allows for easy implementation of a typical BeOS style prefs window,
 * amonst other things.
 *
 */
 
#ifndef _STACKEDLISTVIEW_H_
#define _STACKEDLISTVIEW_H_

#include <Invoker.h>
#include <View.h>

class BListView;
class BListItem;
class BScrollView;

namespace Z {
	namespace Interface {

		class BStackedViewManager;

class BStackedListView : public BView, public BInvoker
{
	public:
										BStackedListView(BRect _frame, 
								                 const BString _name,
									             uint32 _resize, 
									             uint32 _flags, 
									             BMessage* _selectionMsg,
										         bool _delayed_attach = false);
		virtual 						~BStackedListView();
		
		virtual void 					AttachedToWindow();
		virtual void 					MessageReceived(BMessage* _message);
		virtual	void					FrameResized(float _width, float _height);

		// accessors/setters for the frames
		// note that if you set the rects such that the overall area is greater
		// than the size of the StackedListView, it will automatically resize itself
		// to the smallest possible rect that completely encloses both objects
		// also note that the frames should be specified in coordinates relative to the
		// origin of the StackedListView
		//
		// If you set a rect to overlap another, they will compensate assuming the list is
		// on the left and the stack is on the right.
		//
		// Setting the ListWidth lets you allow for space inside the scroll view, the Scroll
		// view will be sized to accomodate the List's width.
		//
		// Setting the ScrollRect will change the ListRect size to accomodate the scroll bars
		// and borders.
				void 					SetListWidth(float _width);
				void					SetScrollFrame(const BRect& _frame);
				void 					SetStackFrame(const BRect& _frame);

				BRect 					GetListFrame() const;
				BRect					GetScrollFrame() const;
				BRect					GetStackFrame() const;
		
		// Adds a view to the stack.
		// _label is the key given to the View in the BListView.
		// Ff _label is empty, it will be taken from the view's name.
		// You may specify a custom list item, if _item is NULL a standard BStringItem is used.
		// Returns B_OK if label/view are valid and added, B_ERROR otherwise.
				status_t				AddView(BView* _view, 
										        const BString _label = BString(), 
										        BListItem* _item = NULL);
				                                		
		// remove returns the corresponding BView (the string item for the label is
		// automatically destroyed) and removes it from the stack.
				BView*					RemoveView(const BString _label);
				BView*					RemoveView(uint32 _index);
						

		// accessors for view stack data
				uint32					CountViews() const;
		
		// convenience functions to allow in place updates of existing items
		// as in the case of add, return B_OK if all is well, B_ERROR if parameter
		// issues. Note that SetViewAt deletes the view that was previously
		// at the requested index.
				status_t				SetLabelAt(uint32 _index, const BString _label);
				status_t				SetViewAt(uint32 _index, BView* _view, BListItem* _item = NULL);
	
				BString		 			GetLabelAt(uint32 _index) const;
				const BView&			GetViewAt(uint32 _index) const;
				BView&					EditViewAt(uint32 _index);
				const BListItem&		GetItemAt(uint32 _index) const;

		// this one is signed in order to be able to return -1 to indicate
		// an empty stack.
				int32					GetSelectedIndex() const;
				status_t				SetSelectedIndex(uint32 _index);

		const BMessage&					GetSelectionMessage() const;
		void							SetSelectionMessage(BMessage *);
		virtual void					SelectionChanged(uint32 _index);

				bool					GetAutoResize() const;
				void					SetAutoResize(bool _autoResize);

	private:
		void							SetList(const BRect& _frame);
		void							ResizeIfNeeded();
		
		// reserved for future use
		virtual void 					_ReservedVirtual1();
		virtual void 					_ReservedVirtual2();
		virtual void 					_ReservedVirtual3();
		virtual void 					_ReservedVirtual4();
		virtual void 					_ReservedVirtual5();
		virtual void 					_ReservedVirtual6();
		virtual void 					_ReservedVirtual7();
		virtual void 					_ReservedVirtual8();
		virtual void 					_ReservedVirtual9();
		virtual void 					_ReservedVirtual10();
		virtual void 					_ReservedVirtual11();
		virtual void 					_ReservedVirtual12();
		virtual void 					_ReservedVirtual13();
		virtual void 					_ReservedVirtual14();
		virtual void 					_ReservedVirtual15();

	private:
		BStackedViewManager*			fViewManager;
		BListView*						fListView;
		BScrollView*					fListScroller;
		uint8							fReserved[8];
};

	} // namespace Interface
} // namespace Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Interface::BStackedListView;
#endif

#endif // _STACKEDLISTVIEW_H_
