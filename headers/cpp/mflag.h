//mflag.h
//960502 bkoz to put in flag for modena library
//used to be in stdexcept but this is a mess as not included in runtime

#ifndef _USINGMODENA_
#define _USINGMODENA_
	#if 1		//	0: old CPlusLib 1: modena C++ lib
		#define	__MODENALIB__
	#else		//	CPlusLib only
		#undef	__MODENALIB__
	#endif
#endif