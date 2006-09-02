#ifndef MEM_ARRAY_H
#define MEM_ARRAY_H

#include <DataIO.h>

template <class T>
class BMemArray : public BMallocIO
{
public:
	BMemArray()
		: BMallocIO()
	{
	}

	BMemArray( const BMemArray<T> &array )
	{
		Resize( array.Size() );
		memcpy( data(), array.data(), array.BufferLength() );
	}

	void Resize( int count )
	{
		SetSize( count * sizeof(T) );
	}

	T &at( int index ) const
	{
		return ((T*)Buffer())[index];
	}

	T &operator[](int index) const
	{
		return at(index);
	}

	int Size() const
	{
		return BufferLength() / sizeof(T);
	}

	T *data() const
	{
		return (T*)Buffer();
	}
};

#endif
