/*
	
	ClassInfo.h
	
	Copyright 1994-97 Be, Inc. All Rights Reserved.

*/


#pragma once

#ifndef _CLASS_INFO_H
#define _CLASS_INFO_H

#include <typeinfo.h>

// returns pointer to class name.
#define class_name(ptr)				((typeid(*(ptr))).name())

// Must check for NIL after the cast to see if it was legal.
#define cast_as(ptr, class)			(dynamic_cast<class*>(ptr))

// Is the object pointed to by ptr an object of class "class"?
#define is_kind_of(ptr, class)		(cast_as(ptr, class) != 0)
	
// Is the object pointed to by ptr EXACTLY class "class"
#define is_instance_of(ptr, class)	(typeid(*(ptr)) == typeid(class))
	
#endif
