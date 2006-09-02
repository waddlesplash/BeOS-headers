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

// -----------------------------------------------------------------------------
template<class TYPE>
BSafeArray<TYPE>::BSafeArray() 
{
}

// -----------------------------------------------------------------------------
template<class TYPE> 
BSafeArray<TYPE>::BSafeArray(const BSafeArray<TYPE>& _other)
	:fStorage(_other.fStorage) 
{
	
}

// -----------------------------------------------------------------------------
template<class TYPE> 
BSafeArray<TYPE>::~BSafeArray() 
{
	
}

// -----------------------------------------------------------------------------
template<class TYPE> 
BSafeArray<TYPE>&
BSafeArray<TYPE>::operator=(const BSafeArray<TYPE>& _other) 
{
	fStorage = _other.fStorage;
	return *this;
}


// -----------------------------------------------------------------------------
template<class TYPE> 
bool
BSafeArray<TYPE>::operator==(const BSafeArray<TYPE>& _other) const
{
	const size_t tcount = CountItems();
	const size_t ocount = _other.CountItems();
	
	bool result = (tcount == ocount);

	if( true == result )
	{
		for(size_t i = 0; i < tcount; ++i )
		{
			if( false == (ItemAt(i) == _other.ItemAt(i)) )
			{
				result = false;
				break;
			}
		}
	}
	
	return result;
}


// -----------------------------------------------------------------------------
template<class TYPE>
size_t
BSafeArray<TYPE>::CountItems() const
{
	return fStorage.CountItems();
}

// -----------------------------------------------------------------------------
template<class TYPE> 
size_t
BSafeArray<TYPE>::IndexOf(const TYPE& _item) const
{
	size_t result = 0;
	
	if( B_ERROR == IndexFor(_item, result) )
	{
		debugger("\n\n\tItem is not present in array\n\n");
	}

	return result;
}

// -----------------------------------------------------------------------------
template<class TYPE> 
bool
BSafeArray<TYPE>::HasItem(const TYPE& _item) const
{
	uint32 idx = 0;
	
	return IndexFor(_item, idx) == B_OK;
}

// -----------------------------------------------------------------------------
template<class TYPE>
const TYPE&
BSafeArray<TYPE>::operator[](size_t _index) const
{
	return ItemAt(_index);
}

// -----------------------------------------------------------------------------
template<class TYPE> 
const TYPE&
BSafeArray<TYPE>::ItemAt(uint32 _index) const
{
	CheckBounds(_index);	
	return fStorage.ItemAt(_index);
}

// -----------------------------------------------------------------------------
template<class TYPE> 
TYPE&
BSafeArray<TYPE>::EditItemAt(uint32 _index) 
{
	CheckBounds(_index);	
	return fStorage.EditItemAt(_index);
}

// -----------------------------------------------------------------------------
template<class TYPE> 
size_t
BSafeArray<TYPE>::ReplaceItemAt(const TYPE& _item, size_t _index) 
{
	CheckBounds(_index);	
	return fStorage.ReplaceItemAt(_item, _index);
}

// -----------------------------------------------------------------------------
template<class TYPE> 
size_t
BSafeArray<TYPE>::AddItem(const TYPE& _item) 
{
	return InsertItem(_item, CountItems());
}

// -----------------------------------------------------------------------------
template<class TYPE> 
size_t
BSafeArray<TYPE>::InsertItem(const TYPE& _item, size_t _index) 
{
	if( _index > 0 )
	{
		CheckBounds(_index - 1);
	}
	
	return fStorage.AddItemAt(_item, _index);
}

// -----------------------------------------------------------------------------
template<class TYPE> 
void
BSafeArray<TYPE>::DeleteItem(const TYPE& _item) 
{
	DeleteItems(IndexOf(_item), 1);
}

// -----------------------------------------------------------------------------
template<class TYPE> 
void
BSafeArray<TYPE>::DeleteItems(size_t _index, size_t _count) 
{
	if( 0 == _count )
	{
		debugger("\n\n\tDon't you think it's a bit silly to delete 0 items?\n\n");
	}
	
	CheckBounds(_index + _count - 1);
	
	fStorage.RemoveItemsAt(_index, _count);
}

// -----------------------------------------------------------------------------
template<class TYPE> 
void
BSafeArray<TYPE>::MakeEmpty() 
{
	// If we are already empty, do we punish?
	fStorage.MakeEmpty();
}

// -----------------------------------------------------------------------------
template<class TYPE> 
status_t
BSafeArray<TYPE>::IndexFor(const TYPE& _item, uint32& _index) const
{
	status_t result = B_ERROR;

	for (size_t i = 0; i < fStorage.CountItems(); ++i)
	{
		if (fStorage.ItemAt(i) == _item)
		{
			result = B_OK;
			_index = i;
			break;
		}
	}

	return result;
}

// -----------------------------------------------------------------------------
template<class TYPE> 
void
BSafeArray<TYPE>::CheckBounds(size_t _index) const
{
	if( _index >= CountItems() )
	{
		BString notice("\n\n\tIndex out of bounds:");
		notice << _index << " \n\n";
		debugger(notice.String());
	}
}
