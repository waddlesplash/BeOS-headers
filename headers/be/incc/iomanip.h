/*
 *   iostream.h
 *
 *   C++ IOStreams manipulators.
 *
 *   This file will change drastically once parameterized
 *   types are implemented.
 *
 *           Copyright (c) 1991-1992, MetaWare Incorporated
 */

#ifndef __IOMANIP_H
#define __IOMANIP_H
#pragma push_align_members(64);

#c_include <generic.h>
#c_include <iostream.h>

#define SMANIP(TYPE)	name2(smanip_,TYPE)
#define SAPP(TYPE)	name2(sapply_,TYPE)
#define IMANIP(TYPE)	name2(imanip_,TYPE)
#define OMANIP(TYPE)	name2(omanip_,TYPE)
#define IOMANIP(TYPE)	name2(iomanip_,TYPE)
#define IAPP(TYPE)	name2(iapply_,TYPE)
#define OAPP(TYPE)	name2(oapply_,TYPE)
#define IOAPP(TYPE)	name2(ioapply_,TYPE)

#define _CLa(TYPE) \
	class SMANIP(TYPE){ \
		ios&(*fcn)(ios&,TYPE); \
		TYPE arg; \
	public: \
		SMANIP(TYPE)(ios&(*f)(ios&,TYPE),TYPE a) { \
			fcn=f; \
			arg=a; \
			} \
		friend istream&operator>>(istream&i,SMANIP(TYPE)&m){ \
			ios *s=&i; \
			(*m.fcn)(*s,m.arg); \
			return i; \
			}\
		friend ostream&operator<<(ostream&o,SMANIP(TYPE)&m){ \
			ios*s=&o; \
			(*m.fcn)(*s,m.arg); \
			return o; \
			} \
	};\
	\
	class SAPP(TYPE){ \
		ios&(*fcn)(ios&,TYPE); \
	public: \
		SAPP(TYPE)(ios&(*f)(ios&,TYPE)) { \
			fcn=f; \
			} \
		SMANIP(TYPE) operator()(TYPE a){ \
			return SMANIP(TYPE)(fcn,a); \
			}\
	};


#define _CLb(TYPE) \
	class IMANIP(TYPE){ \
		istream&(*fcn)(istream&,TYPE); \
		TYPE arg; \
	public: \
		IMANIP(TYPE)(istream&(*f)(istream&,TYPE),TYPE a){ \
			fcn=f; \
			arg=a; \
			} \
		friend istream& operator>>(istream&s,IMANIP(TYPE)&m){ \
			return(*m.fcn)(s,m.arg); \
			} \
	};\
	\
	class IAPP(TYPE){ \
		istream&(*fcn)(istream&,TYPE); \
	public: \
		IAPP(TYPE)(istream&(*f)(istream&,TYPE)){ \
			fcn=f; \
			} \
		IMANIP(TYPE) operator()(TYPE a){ \
			return IMANIP(TYPE)(fcn,a); \
			} \
	};


#define _CLc(TYPE) \
	class OMANIP(TYPE){ \
		ostream&(*fcn)(ostream&,TYPE); \
		TYPE arg; \
	public: \
		OMANIP(TYPE)(ostream&(*f)(ostream&,TYPE),TYPE a){ \
			fcn=f; \
			arg=a; \
			} \
		friend ostream&operator<<(ostream&s,OMANIP(TYPE)&m){ \
			return(*m.fcn)(s,m.arg); \
			} \
	};\
	\
	class OAPP(TYPE){ \
		ostream&(*fcn)(ostream&,TYPE); \
	public: \
		OAPP(TYPE)(ostream&(*f)(ostream&,TYPE)){ \
			fcn=f; \
			} \
		OMANIP(TYPE) operator()(TYPE a){ \
			return OMANIP(TYPE)(fcn,a); \
			} \
	};

#define _CLd(TYPE)\
	class IOMANIP(TYPE){ \
		iostream&(*fcn)(iostream&,TYPE); \
		TYPE arg; \
	public: \
		IOMANIP(TYPE)(iostream&(*f)(iostream&,TYPE),TYPE a){ \
			fcn=f; \
			arg=a; \
			} \
		friend istream&operator>>(iostream&s,IOMANIP(TYPE)&m){ \
			return(*m.fcn)(s,m.arg); \
			} \
		friend ostream&operator<<(iostream&s,IOMANIP(TYPE)&m){ \
			return(*m.fcn)(s,m.arg); \
			} \
	};\
	\
	class IOAPP(TYPE){ \
		iostream&(*fcn)(iostream&,TYPE); \
	public: \
		IOAPP(TYPE)(iostream&(*f)(iostream&,TYPE)){ \
			fcn=f; \
			} \
		IOMANIP(TYPE) operator()(TYPE a){ \
			return IOMANIP(TYPE)(fcn,a); \
			} \
	};

#define IOMANIPdeclare(TYPE) _CLa(TYPE) _CLb(TYPE) _CLc(TYPE) _CLd(TYPE)

#pragma on(nodebug)

IOMANIPdeclare(int) ;
IOMANIPdeclare(long) ;

SMANIP(int) 	setbase(int b) ;	// 0, 8, 10, or 16. (NOT ios::hex, etc.)
SMANIP(long)	resetiosflags(long b) ;
SMANIP(long)	setiosflags(long b) ;
SMANIP(int)	setfill(int f);
SMANIP(int)	setprecision(int p);
SMANIP(int)	setw(int w) ;

#pragma pop(nodebug)

#pragma pop_align_members();
#endif  // __IOMANIP_H


/**          Copyright (c) 1991-1992, MetaWare Incorporated             **/
