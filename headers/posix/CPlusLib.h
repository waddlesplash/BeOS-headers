/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	CPlusLib.h												*/
/*	Purpose...:	C++ specific runtime functions							*/
/*  Copyright.: ©Copyright 1993-95 by metrowerks inc					*/
/************************************************************************/

#ifndef __CPLUSLIB__
#define __CPLUSLIB__

#include <stddef.h>

#ifdef __MC68K__

	#define THIS_IN_A0		0		//	1: pass this pointer in A0; 0: pass this pointer on stack

	#if	THIS_IN_A0
		//	constructor/destructor function pointer definition
		//	only constructors of classes with virtual base classes take an additional
		//	short argument but passing a dummy short doesn't screw up the 68K calling
		//	sequence.
		typedef void (*ConstructorDestructor)(void *:__A0,short);
	#else
		typedef void (*ConstructorDestructor)(void *,short);
	#endif

#else

	typedef void (*ConstructorDestructor)(void *,short);

#endif

typedef struct PTMF {
	long	this_delta;				//	delta to this pointer
	long	vtbl_offset;			//	offset in vtable (-1: not a virtual function)
	union {
		void	*func_addr;			//	nonvirtual function address
		long	ventry_offset;		//	offset of virtual function entry in vtable
	}	func_data;
}	PTMF;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __MC68K__
extern long		__ptmf_test(const PTMF *ptmf);
extern long		__ptmf_cmpr(const PTMF *ptmf1,const PTMF *ptmf2);
extern void		__ptmf_call(...);
extern void		__ptmf_scall(...);
#endif

extern PTMF		*__ptmf_cast(long offset,const PTMF *ptmfrom,PTMF *ptmto);

extern void		*__copy(char *to,char *from,size_t size);
extern void		*__new_hdl(size_t size);
extern void		__del_hdl(void *hdl);
extern void		*__init_arr(void *memptr,ConstructorDestructor constructor,size_t object_size,size_t nobjects);
extern void		*__new_arr(ConstructorDestructor constructor,size_t object_size,size_t objects);
extern void		__del_arr(void *memptr,ConstructorDestructor destructor);
extern void		__dc_arr(void *mem,ConstructorDestructor con_des,short object_size,short objects);

extern void		__construct_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n);
extern void		__destroy_arr(void *block,ConstructorDestructor dtor,size_t size,size_t n);
extern void		*__construct_new_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n);
extern void		__destroy_new_array(void *block,ConstructorDestructor dtor);

#ifdef __cplusplus
}
#endif

#endif
