#ifndef _LAYOUTDEFS_H_
#define _LAYOUTDEFS_H_

#include <Point.h>

namespace Z {
namespace Experimental {
namespace Interface {	

// these constants specify how the view is aligned within its set of layout bounds.
// if a set of constraints is specified that would require the child to be stretched
// (i.e. E_LAYOUT_NORTH_SOUTH), then its min/max size constraints are in effect
// ignored. Otherwise the child is resized as closely as possible to its preferred
// size and aligned within any extra space in accordance to the layout constants
enum layout_alignments 
{
	B_LAYOUT_NORTH 		= 0,
	B_LAYOUT_SOUTH 		= 1, 
	B_LAYOUT_EAST		= 2,
	B_LAYOUT_WEST		= 4,
	B_LAYOUT_HCENTER	= 8,
	B_LAYOUT_VCENTER	= 16,
	B_LAYOUT_CENTER = B_LAYOUT_HCENTER | B_LAYOUT_VCENTER,
	B_LAYOUT_NS = B_LAYOUT_NORTH | B_LAYOUT_SOUTH,
	B_LAYOUT_EW = B_LAYOUT_EAST | B_LAYOUT_WEST,
	B_LAYOUT_NW = B_LAYOUT_NORTH | B_LAYOUT_WEST,
	B_LAYOUT_NE = B_LAYOUT_NORTH | B_LAYOUT_EAST,
	B_LAYOUT_SW = B_LAYOUT_SOUTH | B_LAYOUT_WEST,
	B_LAYOUT_SE = B_LAYOUT_SOUTH | B_LAYOUT_EAST
}; // enum layout_alignments

extern const BPoint B_LAYOUT_PREFERRED_SIZE;

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::layout_alignments;
using Z::Experimental::Interface::B_LAYOUT_NORTH;
using Z::Experimental::Interface::B_LAYOUT_SOUTH;
using Z::Experimental::Interface::B_LAYOUT_EAST;
using Z::Experimental::Interface::B_LAYOUT_WEST;
using Z::Experimental::Interface::B_LAYOUT_HCENTER;
using Z::Experimental::Interface::B_LAYOUT_VCENTER;
using Z::Experimental::Interface::B_LAYOUT_CENTER;
using Z::Experimental::Interface::B_LAYOUT_NS;
using Z::Experimental::Interface::B_LAYOUT_EW;
using Z::Experimental::Interface::B_LAYOUT_NW;
using Z::Experimental::Interface::B_LAYOUT_NE;
using Z::Experimental::Interface::B_LAYOUT_SW;
using Z::Experimental::Interface::B_LAYOUT_SE;
using Z::Experimental::Interface::B_LAYOUT_PREFERRED_SIZE;
#endif

#endif // _LAYOUTDEFS_H_
