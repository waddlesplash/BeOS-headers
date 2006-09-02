#ifndef _LAYOUTMANAGER_H_
#define _LAYOUTMANAGER_H_

#include <interface/View.h>
#include <support/KeyedVector.h>

#include <experimental/LayoutConstraints.h>

// abstract base class for all layout managers

namespace Z {
namespace Experimental {
namespace Interface {
	 
class LayoutManager : public BView
{
	public:
		LayoutManager(BRect frame, const char *name, uint32 resize, uint32 flags);
		LayoutManager(BMessage *from);
		
		virtual ~LayoutManager(void);
		
		virtual void FrameResized(float width, float height);
		
		// view/constraint management
		virtual status_t AddView(BView *view, const LayoutConstraints &constraints);
		virtual status_t UpdateViewConstraints(BView *view, const LayoutConstraints &constraints);
		virtual status_t RemoveView(BView *view);
		virtual BView *RemoveView(const uint32 index);
		uint32 CountViews() const;
		
		const LayoutConstraints &GetConstraints(BView *view) const;

		virtual void ReflowLayout(void) = 0;
		
		// Archivable impl
		virtual status_t Archive(BMessage *into, bool deep = true) const;
		static	BArchivable	*Instantiate(BMessage *data);
					
	private:
		BKeyedVector<BView *, LayoutConstraints> fLayouts;
}; // class LayoutManager
	
} // ns Interface	
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::LayoutManager;
#endif

#endif // _LAYOUTMANAGER_H_
