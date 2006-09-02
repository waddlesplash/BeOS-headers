/*
  -----------------------------------------------------------------------------

	File: Attribute.h
	
	Description: 	Attribute structure used by the stream classes
	
	Copyright 2004, yellowTAB GmbH, All rights reserved.
	
	Developer: Frans van Nispen

  -----------------------------------------------------------------------------
*/

#ifndef __ATTRIBUTE_H
#define __ATTRIBUTE_H

class BString;

struct Attribute
{
	Attribute(const char *name, const char *value)
	{
		fName = name;
		fValue = value;
	}
	
	BString	fName;
	BString	fValue;
};

#endif
