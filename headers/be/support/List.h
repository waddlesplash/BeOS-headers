//******************************************************************************
//
//	File:		List.h
//
//	Description:	List class header.
//	
//	Copyright 1992-94, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_LIST_H
#define	_LIST_H

#ifndef _OBJECT_H
#include <support/Object.h>
#endif

#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif

// -----------------------------------------------------------------------
class BList : public BObject {
	DECLARE_CLASS_INFO(BObject);

public:
				BList(long itemsPerBlock = 20);
				BList(const BList&);
virtual			~BList();

		BList	&operator=(const BList &from);
		bool	AddItem(void *item);
		bool	AddItem(void *item, long atIndex);
		bool	AddList(BList *newItems);
		bool	AddList(BList *newItems, long atIndex);
		bool	RemoveItem(void *item);
		void	*RemoveItem(long index);
		void	*ItemAt(long) const;
		void	*ItemAtFast(long) const;
		long	IndexOf(void *item) const;
		void	*FirstItem() const;
		void	*LastItem() const;
		bool	HasItem(void *item) const;
		long	CountItems() const;
		void	MakeEmpty();
		bool	IsEmpty() const;
		void	DoForEach(bool (*func)(void *));
		void	DoForEach(bool (*func)(void *, void *), void *);
		void	*Items() const;
		void	SortItems(int (*cmp)(const void *, const void *));

// -----------------------------------------------------------------------

private:
		void	Resize(bool makeLarger);

		void**	fObjectList;
		long	fPhysicalSize;
		long	fItemCount;
		long	fBlockSize;
};


inline void		*BList::Items() const
			{ return(fObjectList); }

inline void		*BList::ItemAt(long index) const
			{	if (index < 0 || index >= fItemCount)
					return(NIL);
				else
					return(fObjectList[index]);
			}

inline void		*BList::ItemAtFast(long index) const
			{ return(fObjectList[index]); }

inline bool		BList::AddItem(void* item)
			{ return(AddItem(item, fItemCount)); }

inline long		BList::CountItems() const
			{ return(fItemCount); }

inline void 		*BList::FirstItem()	 const
			{
				if (fItemCount == 0)
					return(NIL);
				else
					return(fObjectList[0]);
			}

inline void 		*BList::LastItem() 	 const
			{
				if (fItemCount == 0)
					return(NIL);
				else
					return(fObjectList[fItemCount - 1]);
			}

inline bool		BList::IsEmpty() const
			{ return(fItemCount == 0); }

inline bool		BList::HasItem(void* item) const
			{ return(IndexOf(item) != -1); }

#endif
