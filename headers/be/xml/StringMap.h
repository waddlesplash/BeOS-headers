/*******************************************************************************
/
/	File:			StringMap.h
/
/   Description:    A Simple Mapping of BString to BString.  Uses BList
/					instead of the STL to be memory efficient.  However,
/					that makes it do O(n) lookups instead of O(log n)
/
/	Copyright 2000, Be Incorporated, All Rights Reserved
/
*******************************************************************************/

#ifndef _STRINGMAP_H
#define _STRINGMAP_H

#include <String.h>
#include <List.h>
#include <SupportDefs.h>


template <class K, class T>
class BMap
{
public:
						BMap();
						BMap(const BMap & copy);
	BMap				& operator=(const BMap & copy);
	virtual				~BMap();
	
	void				Add(const K & key, const T & val);
	status_t			PairAt(int32 index, K & key, T & val) const;
	status_t			PairAt(int32 index, K ** key, T ** val);
	int32				FindIndex(const K & key) const;
	status_t			Find(const K & key, T & val) const;
	T					* Find(const K & key) const;
	int32				CountItems() const;
	
	void				MakeEmpty();
private:
	BList	_names;
	BList	_values;
};

// BStringMap is distinct from BMap, because it has the AddAdopt function
class BStringMap
{
public:
						BStringMap();
						BStringMap(const BStringMap & copy);
	BStringMap			& operator=(const BStringMap & copy);
	virtual				~BStringMap();
	
	void				AddAdopt(BString & key, BString & val);
	void				Add(const BString & key, const BString & val);
	status_t			PairAt(int32 index, BString & key, BString & val) const;
	status_t			PairAt(int32 index, BString ** key, BString ** val);
	int32				FindIndex(const BString & key) const;
	status_t			Find(const BString & key, BString & val) const;
	BString				* Find(const BString & key) const;
	int32				CountItems() const;
	
	void				MakeEmpty();
private:
	BList	_names;
	BList	_values;
};

class BStringSet
{
public:
						BStringSet();
						BStringSet(const BStringSet & copy);
	BStringSet			& operator=(const BStringSet & copy);
	virtual				~BStringSet();
	
	status_t			AddAdopt(BString & val);
	status_t			Add(const BString & val);
	status_t			Remove(const BString & val);
	bool				Exists(const BString & val) const;
	
	int32				CountItems() const;
	const BString		& ItemAt(int32 index) const;
	
	void				MakeEmpty();
	
private:
	BList	_values;
};

bool SplitStringOnWhitespace(const BString & str, BString & split, int32 * pos);
void MushString(BString & str);
void StripWhitespace(BString & str);

#endif // _STRINGMAP_H
