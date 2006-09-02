#ifndef _LAYOUTHVGROUP_H_
#define _LAYOUTHVGROUP_H_

#include <experimental/LayoutManager.h>

class BPoint;

namespace Z {
namespace Experimental {
namespace Interface {
	
enum layout_group_orientation 
{
	B_LAYOUT_HORIZONTAL = 0,
	B_LAYOUT_VERTICAL
}; // enum layout_group_orientation

class LayoutHVGroup : public LayoutManager
{
	public:
		LayoutHVGroup(BRect frame, const char *name, uint32 resize, uint32 flags,
			const uint32 orientation);
		LayoutHVGroup(BMessage *from);
		
		virtual ~LayoutHVGroup(void);
		
		void SetOrientation(const uint32 orientation);
		
		virtual status_t AddView(BView *view, const LayoutConstraints &constraints);
		virtual status_t UpdateViewConstraints(BView *view, const LayoutConstraints &constraints);
		virtual status_t RemoveView(BView *view);
		virtual BView *RemoveView(const uint32 index);
		virtual void ReflowLayout(void);
		
		// BArchivable impl
		virtual status_t Archive(BMessage *into, bool deep = true) const;
		static	BArchivable	*Instantiate(BMessage *data);
	
	private:
		void CalculateSlack(BPoint &sizeSlack, BPoint &gutterSlack);
		void RecalcCache(void);
		void ReflowVertical(const BPoint &sizeSlack, const BPoint &gutterSlack);
		void ReflowHorizontal(const BPoint &sizeSlack, const BPoint &gutterSlack);
		
		uint32 fOrientation;
		BRect fCachedMinSize;
		BRect fCachedMaxSize;
		BPoint fCachedMinGutter;
		BPoint fCachedMaxGutter;
		bool fCacheDirty;
}; // class LayoutHVGroup

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::LayoutHVGroup;
using Z::Experimental::Interface::layout_group_orientation;
using Z::Experimental::Interface::B_LAYOUT_HORIZONTAL;
using Z::Experimental::Interface::B_LAYOUT_VERTICAL;
#endif

#endif // _LAYOUTHVGROUP_H_
