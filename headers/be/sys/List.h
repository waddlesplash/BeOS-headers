//******************************************************************************
//
//	File:		List.h
//
//	Description:	List class header.
//	
//	Written by:	Steve Horowitz
//
//	Copyright 1992-93, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_LIST_H
#define	_LIST_H

#ifndef _OBJECT_H
#include "Object.h"
#endif

// -----------------------------------------------------------------------
class BList : public BObject {

public:
			BList(long itemsPerBlock = 20);
			BList(const BList&);
virtual			~BList();
virtual	char		*ClassName();

	bool		AddItem(void *);
	bool		AddItem(void *, long atIndex);
	bool		RemoveItem(void *);
	void		*RemoveItem(long index);
	void		*RemoveLastItem();
	void		*GetItem(long);
	long		GetIndex(void *);
	void		*FirstItem();
	void		*LastItem();
	bool		HasItem(void *);
	long		CountItems();
	void		MakeEmpty();
	bool		IsEmpty();
	void		DoForEach(void (*func)(void *));
	void		DoForEach(void (*func)(void *, void *), void *);

// -----------------------------------------------------------------------

private:
	void		Resize(bool makeLarger);

	void**		fObjectList;
	long		fPhysicalSize;
	long		fItemCount;
	long		fBlockSize;
};


inline void		*BList::GetItem(long index) 	
			{	if (index < 0 || index >= fItemCount)
					return(NIL);
				else
					return(fObjectList[index]);
			}

inline bool		BList::AddItem(void* item)
			{ return(AddItem(item, fItemCount)); }

inline long		BList::CountItems()
			{ return(fItemCount); }

inline void 		*BList::FirstItem()	
			{
				if (fItemCount == 0)
					return(NIL);
				else
					return(fObjectList[0]);
			}

inline void 		*BList::LastItem() 	
			{
				if (fItemCount == 0)
					return(NIL);
				else
					return(fObjectList[fItemCount - 1]);
			}

inline void		*BList::RemoveLastItem()
			{ return(RemoveItem(fItemCount - 1)); }

inline bool		BList::IsEmpty()	
			{ return(fItemCount == 0); }

inline char 		*BList::ClassName()
			{ return("BList"); }

#endif
