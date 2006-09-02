/*
 * File:		StackedViewManager.h
 * Author:		Rene Gollent
 * Company:		yellowTAB
 * Date:		02/18/2004
 * Description:
 * Support class for interface controls which in some form or other include a "stack" of overlapping views
 * that are made visible/invisible as a result of some on-screen selection, i.e. tabs or a list view.
 *
 *
 */

#ifndef _STACKEDVIEWMANAGER_H_
#define _STACKEDVIEWMANAGER_H_

#include <app/Invoker.h>
#include <interface/View.h>
#include <support/Vector.h>

namespace Z {
namespace Interface {

class BStackedViewManager : public BView, public BInvoker
{
	public:
			// @ param _lazy_attach deferrs attachment of the view until it is shown.
									BStackedViewManager(BRect _frame, 
							    	                    const char* _name, 
							                            uint32 _resize, 
							                            uint32 _flags, 
							                            BMessage* _modificationMessage,
							                            bool _lazy_attach = false);
		virtual			 			~BStackedViewManager();

				uint32		 		CountViews() const;
				uint32				IndexOf(const BView& _view) const;
				bool				HasView(const BView& _view) const;

				BView&				EditViewAt(uint32 _index);
				const BView&		ViewAt(uint32 _index) const;

				uint32				AddView(BView* _view);
				uint32				InsertView(BView* _view, uint32 _index); 

				BView*				RemoveView(uint32 _index);
				BView*				RemoveView(BView& _view);
		
				BView*				ReplaceView(uint32 _index, BView* _view);

				void				SetSelectedIndex(uint32 _index);
				void				SetSelectedView(BView& _view);
				
				uint32				GetSelectedIndex() const;
				BView&				GetSelectedView();
				
				bool				GetAutoResize() const;
				void				SetAutoResize(bool _autoResize);
				
				bool				DoesLazyAttach() const;
				void				SetLazyAttach(bool _lazy);

		virtual void		AttachedToWindow();
		virtual void 		SelectionChanged(uint32 _index);

	private:
		// reserved for future use
		virtual void _ReservedVirtual1();
		virtual void _ReservedVirtual2();
		virtual void _ReservedVirtual3();
		virtual void _ReservedVirtual4();
		virtual void _ReservedVirtual5();
		virtual void _ReservedVirtual6();
		virtual void _ReservedVirtual7();
		virtual void _ReservedVirtual8();
		virtual void _ReservedVirtual9();
		virtual void _ReservedVirtual10();
		virtual void _ReservedVirtual11();
		virtual void _ReservedVirtual12();
		virtual void _ReservedVirtual13();
		virtual void _ReservedVirtual14();
		virtual void _ReservedVirtual15();

				status_t	IndexFor(const BView& _view, uint32& _index) const;
				void		CheckBounds(uint32 _index) const;

	private:
		B::Support::
		BVector<BView*>		fStackedViewList;
		uint32				fSelectedIdx;
		bool				fAutoResize;
		bool				fDelayedAttach;
		uint8				_FBCPadding[32];
};


// -----------------------------------------------------------------------------

} // namespace Interface
} // namespace Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Interface::BStackedViewManager;
#endif

#endif // _STACKEDVIEWMANAGER_H_
