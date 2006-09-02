/*
 * File:		StackedOutlineView.h
 * Author:		Rene Gollent
 * Company:		yellowTAB
 * Date:		02/18/2004
 * Description:
 * Interface Control which combines a BOutlineListView and a BStackedViewManager,
 * yielding a control that allows for easy implementation of a typical BeOS style
 * prefs window, amongst other things.
 *
 */
 
#ifndef _STACKEDOUTLINEVIEW_H_
#define _STACKEDOUTLINEVIEW_H_

#include <Invoker.h>
#include <View.h>

class BOutlineListView;
class BScrollView;
class BStringItem;

namespace Z {
namespace Interface {

class BStackedViewManager;

class BStackedOutlineView : public BView, public BInvoker
{
	public:
										BStackedOutlineView(BRect _frame, 
										                    const char* _name,
										                    uint32 _resize, 
										                    uint32 _flags, 
										                    BMessage* _selectionMsg);
		virtual 						~BStackedOutlineView();
		
		virtual			void 			AttachedToWindow();
		virtual			void 			MessageReceived(BMessage* _message);

		// accessors/setters for the rects
		// note that if you set the rects such that the overall area is greater
		// than the size of the StackedListView, it will automatically resize itself
		// to the smallest possible rect that completely encloses both objects
		// also note that the rects should be specified in coordinates relative to the
		// origin of the StackedListView
						void 			SetListRect(const BRect& _rect);
						void 			SetStackRect(const BRect& _rect);

						BRect 			GetListRect() const;
						BRect 			GetStackRect() const;
		
		// adds a view to the stack.
		// label is the key given to it in the BListView
		// if label is NULL, it will be taken from the view's name.
		// returns B_OK if label/view are valid and added, B_ERROR otherwise.
						status_t		AddView(BStringItem* _label, 
						                        BView* _view, 
										        BStringItem* _parent = NULL); 

		
		// remove returns the corresponding BView (the string item for the label is
		// automatically destroyed) and removes it from the stack.
						BView*			RemoveView(const char* _label);
						BView*			RemoveView(uint32 _index);
						

		// accessors for view stack data
						uint32			CountViews() const;
		
		// convenience functions to allow in place updates of existing items
		// as in the case of add, return B_OK if all is well, B_ERROR if parameter
		// issues. Note that SetViewAt deletes the view that was previously
		// at the requested index.
						status_t		SetLabelAt(uint32 _index, const char* _label);
						status_t		SetViewAt(uint32 _index, BView* _view);
	
				const	char* 			GetLabelAt(uint32 _index) const;
				const	BView&			GetViewAt(uint32 _index) const;
						BView&			EditViewAt(uint32 _index);

		// this one is signed in order to be able to return -1 to indicate
		// an empty stack.
						int32			GetSelectedIndex() const;
						status_t		SetSelectedIndex(uint32 _index);

				const	BMessage&		GetSelectionMessage() const;
						void			SetSelectionMessage(BMessage* _message);
		virtual 		void			SelectionChanged(uint32 _index);

						bool			GetAutoResize() const;
						void			SetAutoResize(bool _autoResize);

	private:
				void					ResizeIfNeeded();
				void					CheckBounds(uint32 _index) const;
				BView *					RecursiveRemove(uint32 _index);
				
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
		BOutlineListView*				fListView;
		BScrollView*					fListScroller;
		char							_FBCPadding[32];
};

} // namespace Interface
} // namespace Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Interface::BStackedOutlineView;
#endif

#endif // _STACKEDOUTLINEVIEW_H_
