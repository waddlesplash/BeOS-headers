/*
 *	exception
 *	
 *		Copyright © 1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __exception__
#define __exception__

#include <ansi_parms.h>

#pragma options align=mac68k

__namespace(std)

class exception
{
	public:
														 exception			()														throw()	{}
														 exception			(const exception&)						throw()	{}
						exception&			 operator=			(const exception&)						throw()	{ return(*this); }
		virtual									~exception			()														throw()	{}
		virtual	const char *		 what						()											const	/*throw()*/;
};

class bad_exception : public exception
{
	public:
														 bad_exception	()														throw()	{}
														 bad_exception	(const bad_exception&)				throw()	{}
						bad_exception&	 operator=			(const bad_exception&)				throw()	{ return(*this); }
		virtual									~bad_exception	()														throw()	{}
		virtual	const char * 		 what						() 											const /*throw()*/;
};

typedef void (* unexpected_handler)();
typedef void (* terminate_handler )();

unexpected_handler	set_unexpected(unexpected_handler);
terminate_handler		set_terminate (terminate_handler );

void	unexpected();
void	terminate ();

__end_namespace(std)

#pragma options align=reset

#endif
