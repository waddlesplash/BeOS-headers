/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_COMPILE_H
#define MSIPL_COMPILE_H

#define  RD_LOCK     1
#define  WR_LOCK     2

#include <stddef.h>

/* to be defined if you are supplying an extended math library */
/* #  define MSIPL_USE_EXTERNAL_MATHLIB */

/* to be defined if exception handling is to be enabled */
/* #  define MSIPL_EXCEPT */

/*Metrowerks*/
#if __MWERKS__  // MW-mm 960206a
#if macintosh && !defined(__dest_os)               	//MW-mm 960927a
  #define __dest_os __mac_os                       	//MW-mm 960927a
#endif 												//MW-mm 960927a
#  define MSIPL_DEF_EXPLICIT						//vss 971010
#  define MSIPL_EXCEPT		
#  define MSIPL_HEADER_EXTN_H
#ifndef __INTEL__
//#define MSIPL_DEF_TEMPARG	// MW-RDL allow templates with default arguments  
#endif
#  define MSIPL_TEMPL_INST_ALL           			//MW-mm 960328a
#  define MSIPL_NON_TYPE_TEMPARG        			// MW-mm 960221a
//#  define MSIPL_THROW_SPECS						//970403 bkoz should be off to improve performance
//#  define __MSL_NO_INSTANTIATE__					//970404 bkoz should be on to prohibit implicit inst
#	define MSIPL_EXPINST_ALLOWED					//970408 have inst in library
/*970415 bkoz via Dennis C. De Mars*/
#	define __MSL_FIX_ITERATORS__(myType)  null_template \
                  struct iterator_trait <myType * > { \
                      typedef ptrdiff_t               distance_type; \
                      typedef myType            value_type; \
                      typedef random_access_iterator_tag iterator_category; \
                  } 
#if __option(bool)
#  define MSIPL_BOOL_BUILTIN						//960812 bkoz
#endif		
#define MSIPL_USE_EXTERNAL_MATHLIB					//970402 bkoz
#if __dest_os == __be_os                            //971107 mm
#	define MSIPL_MULTITHREAD
#endif                                              // 971107 mm
#endif //__MWERKS__  				 				// MW-mm 960509a

/*Motorola*/
#if __MOTO__
#  define MSIPL_HEADER_EXTN_H
#  define MSIPL_THROW_SPECS
#  define MSIPL_DEF_TEMPARG
#  define MSIPL_NON_TYPE_TEMPARG
#  define MSIPL_STATIC_CONST_INIT
#  define MSIPL_EXCEPT
#  define MSIPL_64LONGLONG
#if _BOOL
#  define MSIPL_BOOL_BUILTIN
#endif
#  define MSIPL_TYPENAME
#  define MSIPL_EXPINST_ALLOWED
#  define MSIPL_DEF_EXPLICIT        
#  define MSIPL_TEMPL_NEWSPEC   
#  define MSIPL_MEMBER_TEMPLATE
#  define MSIPL_EDG231
#endif //__MOTO__

/* Apogee */
#ifdef MSIPL_APG40
#  define MSIPL_APOGEE_ADDNL_FUNCTIONS
#  define MSIPL_HEADER_EXTN_H
#  define MSIPL_THROW_SPECS
#  define MSIPL_DEF_TEMPARG
#  define MSIPL_NON_TYPE_TEMPARG
#  define MSIPL_STATIC_CONST_INIT

#  define MSIPL_USING_NAMESPACE
#  define MSIPL_EXCEPT
#  define __EDG_EXCEPT_CLASSES

#  define MSIPL_BOOL_BUILTIN
#  define MSIPL_TYPENAME
#  define MSIPL_EXPINST_ALLOWED

#  define MSIPL_DEF_EXPLICIT
#  define MSIPL_TEMPL_NEWSPEC
#  define MSIPL_MEMBER_TEMPLATE
#  define MSIPL_EDG232
#endif

/* For EDG */
#if defined(MSIPL_EDG232_SOL1) || defined(MSIPL_EDG232_SOL2)
#  define MSIPL_HEADER_EXTN_H
#  define MSIPL_THROW_SPECS
#  define MSIPL_DEF_TEMPARG
// #  define MSIPL_NON_TYPE_TEMPARG
#  define MSIPL_STATIC_CONST_INIT

#  define MSIPL_USING_NAMESPACE
#  define MSIPL_EXCEPT
#  define __EDG_EXCEPT_CLASSES

#  define MSIPL_BOOL_BUILTIN
#  define MSIPL_TYPENAME
#  define MSIPL_EXPINST_ALLOWED

#  define MSIPL_DEF_EXPLICIT        
#  define MSIPL_TEMPL_NEWSPEC   
#  define MSIPL_MEMBER_TEMPLATE

#  define MSIPL_EDG232
#  define MSIPL_APOGEE_ADDNL_FUNCTIONS
#endif

#ifdef MSIPL_BC50
#  define MSIPL_EXCEPT
#  define MSIPL_THROW_SPECS
#  define MSIPL_NONDEF
#  define MSIPL_TYPENAME
#  define __MINMAX_DEFINED 
#  define MSIPL_BOOL_BUILTIN
#  pragma warn -inl
#endif

#ifdef MSIPL_MULTITHREAD
#  define DEC_MUTEX(obj)                mutex_rec <mutex>       obj;
#  define DEC_STATIC_MUTEX(obj)  static mutex_rec <mutex>       obj;
#  define LOCK(mut_block, mut) \
       mutex_block<mutex_rec<mutex> >    mut_block(mut)
#  define UNLOCK(mut_block)   mut_block.release ()
#  define REMOVE(mutex)       mutex.remove ()

#  ifdef MSIPL_OBJECT_LOCK

#    ifdef MSIPL_MULTIPLE_RW_LOCK
#      define DEC_OBJ_LOCK(obj)   mutex_rec <rw_mutex>    obj;
#      define READ_LOCK(mut)  \
           mutex_block<mutex_rec<rw_mutex> > loc_mut(mut, RD_LOCK)
#      define WRITE_LOCK(mut)    \
           mutex_block<mutex_rec<rw_mutex> > loc_mut(mut, WR_LOCK)

#    else                 /* !MSIPL_MULTIPLE_RW_LOCK */

#      define DEC_OBJ_LOCK(obj)   mutex_rec <mutex>       obj;
#      define READ_LOCK(mut)  \
           mutex_block<mutex_rec<mutex> >    loc_mut(mut, RD_LOCK)
#      define WRITE_LOCK(mut)     \
           mutex_block<mutex_rec<mutex> >    loc_mut(mut, WR_LOCK)

#    endif               /* MSIPL_MULTIPLE_RW_LOCK */ 

#  else

#    define DEC_OBJ_LOCK(obj)   null_mutex       obj;
#    define READ_LOCK(mut)       
#    define WRITE_LOCK(mut)

#  endif                 /* MSIPL_OBJECT_LOCK */

#else                    /* !MSIPL_MULTITHREAD */

#  define DEC_OBJ_LOCK(obj)           //null_mutex       obj;
#  define DEC_MUTEX(obj)              //null_mutex       obj;
#  define DEC_STATIC_MUTEX(obj)       //null_mutex       obj;
#  define READ_LOCK(mut)              //mut.acquire ()
#  define WRITE_LOCK(mut)             //mut.acquire ()
#  define REMOVE(mut)                 //mut.remove ()
#  define LOCK(bl_mut, mut)           
#  define UNLOCK(mut_block)           

#endif                   /* MSIPL_MULTITHREAD */

#ifndef MSIPL_BOOL_BUILTIN
#  if __dest_os == __be_os		/* Be-mani 980107 */
#    include <SupportDefs.h>	/* Be-mani 980107 */
#  else							/* Be-mani 980107 */
//#  define bool int                  //MW-mm 961111
#    define bool unsigned char          //MW-mm 961111
#  endif						/* Be-mani 980107 */
#ifndef true
	#define true			1
#endif
#ifndef false
	#define false			0
#endif
#endif

/* does your compiler support 'explicit' keyword ?? */
#ifndef MSIPL_DEF_EXPLICIT
#  define explicit
#endif

/* does your compiler support 'typename' ?? */
#ifndef MSIPL_TYPENAME
#  define typename
#endif

/* does your compiler support 'template<>' ?? */
#ifdef MSIPL_TEMPL_NEWSPEC
#  define null_template template<>
#else
#  define null_template
#endif

/* does your compiler instantiate const ARG as a
   template parameter properly */
#ifdef MSIPL_NO_CONST_TEMPARG_INST
#define M_CONST
#else
#define M_CONST const
#endif

#if defined (MSIPL_EXCEPT) && defined (MSIPL_THROW_SPECS)
#  define MSIPL_THROW throw()  
#  define MSIPL_THROW_STR(strList) throw(strList)
#else
#  define MSIPL_THROW 
#  define MSIPL_THROW_STR(strList)
#endif

#ifdef MSIPL_HEADER_EXTN_H
#     define MOD_INCLUDE(str) <str##.h>
#else
#     define MOD_INCLUDE(str) <str>
#endif

#ifdef MSIPL_ANSI_HEADER
#     define MOD_C_INCLUDE(str) MOD_INCLUDE(c##str)
#else
#     define MOD_C_INCLUDE(str) MOD_INCLUDE(str)
#endif

#endif /* MSIPL_COMPILE_H */

/* Change record
MW-mm 960730  	Inserted Metrowerks compile parameters
MW-mm 961111 	line 140 changed bool to be unsigned char
961221 bkoz line 38, added moto switches (via matthew moss)
970403 bkoz undefine MSIPL_THROW_SPECS to work around codegen bug
971010 vss  explicit keyword now implemented in compiler
971107 mm   Change from Be
980107 Be-mani Get bool from SupportDefs.h for BeOS
*/
