/*
  -----------------------------------------------------------------------------

	File:			StringList.h
	
	Description:	can load and save from or to file i.e settings as string
					and split them into a list of strings 
	
	Copyright 2004, Yellow Tab GmbH, All rights reserved.

  -----------------------------------------------------------------------------
*/

#ifndef _BSTRINGLIST_H_
#define _BSTRINGLIST_H_

#include <experimental/SafeArray.h>
#include <support/String.h>

namespace Z {
namespace Support {

// Make it easier to get the params of SplitString in the correct order.	
class BStringDelimiter : public BString
{
	public:
		explicit		BStringDelimiter(const BString& _data) : BString(_data) {}
};

class BStringList : public BSafeArray<BString>
{
	public:

									BStringList();
		virtual						~BStringList();

				status_t			LoadFromFile(const BString& _path);
				status_t			SaveToFile(const BString& _path);
				
				// takes _from and adds delimited results to this
				void				SplitString(const BStringDelimiter& _delimiter, const BString& _from);
				BString				AsString(const BString& _divider) const;
		
				// Conveniance / explicit covers.
				size_t				CountStrings() const;
				size_t				IndexOfString(const BString& _string) const;
				bool				HasString(const BString& _string) const;
										              
				BString				operator[](size_t _index) const;
				BString				StringAt(uint32 _index) const;
				BString&			EditStringAt(uint32 _index);
		
				size_t				ReplaceStringAt(const BString& _string, size_t _index);
		
				size_t				AddString(const BString& _string);
				size_t				InsertString(const BString& _string, size_t _index);
		
				void				DeleteString(const BString& _string);
				void				DeleteStrings(size_t _index, size_t _count = 1);
				
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
// Inlines, please do not muck about with the following.
//
// -----------------------------------------------------------------------------

//
// -----------------------------------------------------------------------------
inline size_t
BStringList::CountStrings() const
{
	return CountItems();
}

// -----------------------------------------------------------------------------
inline size_t
BStringList::IndexOfString(const BString& _string) const
{
	return IndexOf(_string);
}

// -----------------------------------------------------------------------------
inline bool
BStringList::HasString(const BString& _string) const
{
	return HasItem(_string);
}

// -----------------------------------------------------------------------------
inline BString
BStringList::operator[](uint32 _index) const
{
	return StringAt(_index);
}

// -----------------------------------------------------------------------------
inline BString
BStringList::StringAt(uint32 _index) const
{
	return ItemAt(_index);
}

// -----------------------------------------------------------------------------
inline BString&
BStringList::EditStringAt(uint32 _index) 
{
	return EditItemAt(_index);
}

// -----------------------------------------------------------------------------
inline size_t
BStringList::ReplaceStringAt(const BString& _string, size_t _index) 
{
	return ReplaceItemAt(_string, _index);
}

// -----------------------------------------------------------------------------
inline size_t
BStringList::AddString(const BString& _string) 
{
	return AddItem(_string);
}

// -----------------------------------------------------------------------------
inline size_t
BStringList::InsertString(const BString& _string, size_t _index) 
{
	return InsertItem(_string, _index);
}

// -----------------------------------------------------------------------------
inline void
BStringList::DeleteString(const BString& _string) 
{
	DeleteItem(_string);
}

// -----------------------------------------------------------------------------
inline void
BStringList::DeleteStrings(size_t _index, size_t _count) 
{
	DeleteItems(_index, _count);
}


}	// Support
}	// Z

#ifndef _ZETA_EXPLICIT_NAMESPACE_
using Z::Support::BStringList;
using Z::Support::BStringDelimiter;
#endif

#define _D(x)	Z::Support::BStringDelimiter(x)	
#endif

