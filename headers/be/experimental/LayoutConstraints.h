#ifndef _LAYOUTCONSTRAINTS_H_
#define _LAYOUTCONSTRAINTS_H_

#include <ctype.h>

#include <interface/Point.h>

namespace Z {
namespace Experimental {
namespace Interface {
	
class LayoutConstraints
{
	public:
		LayoutConstraints(void);
		
		LayoutConstraints(const uint32 alignment, const BPoint &minSize,
			const BPoint &maxSize, const float minGutter, const float maxGutter);
		
		virtual ~LayoutConstraints(void);

		inline uint32 GetAlignment(void) const;
		void SetAlignment(const uint32 alignment);
				
		inline const BPoint &GetMinSize(void) const;
		void SetMinSize(const BPoint &minimum);
		
		inline const BPoint &GetMaxSize(void) const;
		void SetMaxSize(const BPoint &maximum);
		
		inline float GetMinGutter(void) const;
		void SetMinGutter(const float gutter);
		
		inline float GetMaxGutter(void) const;
		void SetMaxGutter(const float gutter);

		void PrintToStream(void) const;

	private:
		uint32 fAlignment;
		BPoint fMinSize;
		BPoint fMaxSize;
		float fMinGutterSize;
		float fMaxGutterSize;
}; // class LayoutConstraints

uint32
LayoutConstraints::GetAlignment(void) const
{
	return fAlignment;
}

const BPoint &
LayoutConstraints::GetMinSize(void) const
{
	return fMinSize;
}

const BPoint &
LayoutConstraints::GetMaxSize(void) const
{
	return fMaxSize;
}

float
LayoutConstraints::GetMinGutter(void) const
{
	return fMinGutterSize;
}

float
LayoutConstraints::GetMaxGutter(void) const
{
	return fMaxGutterSize;
}

} // ns Interface
} // ns Experimental
} // ns Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Interface::LayoutConstraints;
#endif

#endif // _LAYOUTCONSTRAINTS_H_
