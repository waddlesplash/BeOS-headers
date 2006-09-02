#ifndef _GRIDLAYOUTMANAGER_H_
#define _GRIDLAYOUTMANAGER_H_

#include <support/KeyedVector.h>

#include <experimental/LayoutManager.h>

class BPoint;

namespace Z {
namespace Experimental {
namespace Interface {

extern const uint32 B_DEFAULT_GRID_SIZE;

class GridLayoutManager : public LayoutManager
{
	public:
		GridLayoutManager(BRect frame, const char *name, uint32 resize,
			uint32 flags, uint32 hGridSize = B_DEFAULT_GRID_SIZE,
			uint32 vGridSize = B_DEFAULT_GRID_SIZE);
		virtual ~GridLayoutManager(void);
		
		// augmented versions of AddView/UpdateView for dealing with the grid
		// assignments. If no grid rect is specified, the grid layout will try
		// to auto-position it in the next available area.
		// if it cannot fit or if the user passes a set of grid constraints
		// that are not possible (i.e. already partially/wholly in use), an
		// error is returned and the add/update fails. 
		virtual status_t AddGridView(BView *view, const	LayoutConstraints &constraints,
			const BRect &gridMap = BRect(0,0,0,0));
		virtual status_t UpdateGridViewConstraints(BView *view,
			const LayoutConstraints &constraints,
			const BRect &gridMap = BRect(0,0,0,0));
		
		virtual void ReflowLayout(void);
			
	private:
		char **fGridFreeMap;
		B::Support::BKeyedVector<BView *, BRect> fGridUsageMap;
		BPoint fGridSize;
			
}; // class GridLayoutManager

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::GridLayoutManager;
#endif

#endif // _GRIDLAYOUTMANAGER_H_
