/******************************************************************************
/
/	File:			AtomList.h
/
/	Description:	Looks and feels like a BList, but holds atoms.
/
/	Copyright 2000, Be Incorporated
/
******************************************************************************/

#ifndef	_SUPPORT_ATOM_LIST_H
#define	_SUPPORT_ATOM_LIST_H

#include <support/BAtom.h>
#include <support/List.h>

namespace B {
namespace Support {

/*-----------------------------------------------------------------*/
/*----- BAtomList class -------------------------------------------*/

class BAtomList {

public:
						BAtomList(int32 initialAllocSize = 0);
						BAtomList(const BAtomList&);
virtual					~BAtomList();

		BAtomList&		operator=(const BAtomList &from);

/* Adding and removing items. */
		bool			AddItem(BAtom* item);
		bool			AddItem(BAtom* item, int32 atIndex);
		bool			AddList(BAtomList* newItems);
		bool			AddList(BAtomList* newItems, int32 atIndex);
		bool			RemoveItem(BAtom* item);
		atom_ptr<BAtom>	RemoveItem(int32 index);
		bool			RemoveItems(int32 index, int32 count);
		atom_ptr<BAtom>	ReplaceItem(int32 index, BAtom* newItem);
		void			MakeEmpty();

/* Reordering items. */
		void			SortItems(int (*cmp)(const BAtom *, const BAtom *));
		bool			SwapItems(int32 indexA, int32 indexB);
		bool			MoveItem(int32 fromIndex, int32 toIndex);

/* Retrieving items. */
		atom_ptr<BAtom>	ItemAt(int32) const;
		atom_ptr<BAtom>	FirstItem() const;
		atom_ptr<BAtom>	LastItem() const;

/* Querying the list. */
		bool			HasItem(BAtom* item) const;
		int32			IndexOf(BAtom* item) const;
		int32			CountItems() const;
		bool			IsEmpty() const;

/* Iterating over the list. */
		void			DoForEach(bool (*func)(BAtom *));
		void			DoForEach(bool (*func)(BAtom *, void *), void *);

/*----- Private or reserved ---------------*/
private:

virtual	void			_ReservedAtomList1();
virtual	void			_ReservedAtomList2();
virtual	void			_ReservedAtomList3();
virtual	void			_ReservedAtomList4();
virtual	void			_ReservedAtomList5();
virtual	void			_ReservedAtomList6();
virtual	void			_ReservedAtomList7();
virtual	void			_ReservedAtomList8();
virtual	void			_ReservedAtomList9();
virtual	void			_ReservedAtomList10();

		void			AcquireAll(void* id);
		void			ReleaseAll(void* id);
		
		BList			fList;
		uint32			_reserved[2];
};

} }	// namespace B::Support

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

#endif /* _ATOM_LIST_H */
