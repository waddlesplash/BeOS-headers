//******************************************************************************
//
//	File:		BlockCache.h
//
//	Description:	A simple caching mecahnism for fixed size blocks
//
//	Copyright 1995-96, Be Incorporated
//
//******************************************************************************

#ifndef _BLOCK_CACHE_H
#define _BLOCK_CACHE_H

#ifndef _STDDEF_H
#include <stddef.h>
#endif
#ifndef _LOCKER_H
#include <Locker.h>
#endif

/*
 temporary comment:

 The BBlockCache object can be used to transparently cache a blocks of
 memory. In certain situations this can be a substantial performance
 boast. This code is limited to objects that are either managed by
 malloc/free or the C++ new/delete operator. In addition, the blocks
 must be of fixed size.

 B_OBJECT_CACHE:
	 The block of memory being cached is an object that is allocated
	 by the global 'new' operator and disposed of by the global
	 'delete' operator. 

 B_MALLOC_CACHE:
	 The block of memory being cached is allocated and deallocated
	 by the standard malloc/free methods.

*/

enum {
	B_OBJECT_CACHE = 0,
	B_MALLOC_CACHE = 1
};

class BMessage;

// ------------------------------------------------------------------- //

class BBlockCache {
	public:
				BBlockCache(int cache_size, size_t block_size, long type);
virtual			~BBlockCache();

		void	*Get(size_t block_size);
		void	Save(void *pointer, size_t block_size);

	private:
		friend BMessage;

		enum {
			/*
			 This is a private define for block allocated/deallocated
			 by sh_malloc and sh_free.
			*/
			B_SHARED_HEAP_CACHE = 100
		};

		int		fCacheSize;
		void	**fCache;
		int		fMark;
		BLocker	fLock;
		int		fBlkSize;
		void	*(*fAlloc)(size_t size);
		void	(*fFree)(void *);
};

#endif
