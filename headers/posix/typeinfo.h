/*
 *	typeinfo
 *	
 *		Copyright © 1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __typeinfo__
#define __typeinfo__

#include <ansi_parms.h>
#include <exception.h>

#pragma options align=mac68k

__namespace(std)

class type_info
{
		const char	*tname;
		const void	*tbase;
	
	public:
		typedef char	bool_type;
		
		//virtual 									~type_info	();
									bool_type		 operator==	(const type_info&)	const;
									bool_type		 operator!=	(const type_info&)	const;
									bool_type		 before			(const type_info&)	const;
						const	char *			 name				()									const;
	
	private:
															 type_info	(const type_info&);
									type_info&	 operator=	(const type_info&);
};

class bad_cast : public exception
{
	public:
															 bad_cast		()												throw()	{}
															 bad_cast		(const bad_cast&)					throw()	{}
									bad_cast&		 operator=	(const bad_cast&)					throw()	{ return(*this); }
		//virtual										~bad_cast		()												throw()	{}
		virtual	const char * 			 what				() 									const /*throw()*/;
};

class bad_typeid : public exception
{
	public:
															 bad_typeid	()													throw()	{}
															 bad_typeid	(const bad_typeid&)					throw()	{}
									bad_typeid&	 operator=	(const bad_typeid&)					throw()	{ return(*this); }
		//virtual										~bad_typeid	()													throw()	{}
		virtual	const char * 			 what				() 									const /*throw()*/;
};

__end_namespace(std)

#pragma options align=reset

#endif
