/*
  -----------------------------------------------------------------------------

	File:			SafeArray.inl
	
	Description:	Sort of a baby-sitter array, if you do anything wrong, it 
					will explode with a nice detailed debugger message about 
					how you have messed up.	This includes such errors as indexs
					out of range and trying to do any sort of access of an item
					not in the list. So remember to always use HasItem() and 
					CountItems() before making any unfounded assumptions.
	
	Copyright 2004, Yellow Tab GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/

#ifndef _BSAFE_ARRAY_H_
#define _BSAFE_ARRAY_H_

#include <support/Vector.h>
#include <support/String.h>		// for inlines.

namespace Z {
namespace Experimental {
namespace Support {

template<class TYPE>
class BSafeArray
{
	public:
										BSafeArray();
										BSafeArray(const BSafeArray<TYPE>& _other);
		virtual							~BSafeArray();

				BSafeArray<TYPE>&		operator=(const BSafeArray<TYPE>& _other);
				bool					operator==(const BSafeArray<TYPE>& _other) const;
				
				size_t					CountItems() const;
				size_t					IndexOf(const TYPE& _item) const;
				bool					HasItem(const TYPE& _item) const;
										              
				const TYPE&				operator[](size_t _index) const;
				const TYPE&				ItemAt(uint32 _index) const;
				TYPE&					EditItemAt(uint32 _index);
		
				size_t					ReplaceItemAt(const TYPE& _item, size_t _index);
		
				size_t					AddItem(const TYPE& _item);
				size_t					InsertItem(const TYPE& _item, size_t _index);
		
				void					DeleteItem(const TYPE& _item);
				void					DeleteItems(size_t _index, size_t _count = 1);
				void					MakeEmpty();
			
	private:
				status_t				IndexFor(const TYPE& _item, uint32& _index) const;
				void					CheckBounds(size_t _index) const;
		
	private:
		BVector<TYPE>	fStorage;												
};

#include <experimental/SafeArray.inl>

}	// Support
}	// Experimental
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Experimental::Support::BSafeArray;
#endif

#endif
