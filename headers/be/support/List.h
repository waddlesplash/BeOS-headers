//******************************************************************************
//
//	File:		List.h
//
//	Description:	List class header.
//	
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************


#ifndef	_LIST_H
#define	_LIST_H

#include <SupportDefs.h>

// -----------------------------------------------------------------------
class BList {

public:
				BList(int32 itemsPerBlock = 20);
				BList(const BList&);
virtual			~BList();

		BList	&operator=(const BList &from);
		bool	AddItem(void *item);
		bool	AddItem(void *item, int32 atIndex);
		bool	AddList(BList *newItems);
		bool	AddList(BList *newItems, int32 atIndex);
		bool	RemoveItem(void *item);
		void	*RemoveItem(int32 index);
		bool	RemoveItems(int32 index, int32 count);
		void	*ItemAt(int32) const;
		void	*ItemAtFast(int32) const;
		int32	IndexOf(void *item) const;
		void	*FirstItem() const;
		void	*LastItem() const;
		bool	HasItem(void *item) const;
		int32	CountItems() const;
		void	MakeEmpty();
		bool	IsEmpty() const;
		void	DoForEach(bool (*func)(void *));
		void	DoForEach(bool (*func)(void *, void *), void *);
		void	*Items() const;
		void	SortItems(int (*cmp)(const void *, const void *));

// -----------------------------------------------------------------------

private:

virtual	void			_ReservedList1();
virtual	void			_ReservedList2();

		void	Resize(int32 count);

		void**	fObjectList;
		size_t	fPhysicalSize;
		int32	fItemCount;
		int32	fBlockSize;
		uint32	_reserved[2];
};

#endif
