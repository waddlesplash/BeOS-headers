/*
 *   _stdarg.h -- used by stdio.h and stdarg.h
 *
 *   Macros and type for functions that require variable
 *   numbers of arguments.
 *
 *           Copyright (c) 1990, 1993 MetaWare Incorporated
 */

#ifndef __STDARG_H
#define __STDARG_H	
#pragma push_align_members(64);

#ifdef __CPLUSPLUS__
extern "C" {
#endif

/*
 * __vararg_char is used as a pseudonym for "char". The compiler would
 * ordinarily warn about "misbehaviour" if an arbitrary pointer is cast 
 * to or from (char *) at high optimization levels.
 * To avoid this problem we use "__vararg_char" inplace of "char".
 * The compiler special-cases the type (__vararg_char *) and doesn't put
 * out the warning.
 */
typedef char __vararg_char;

#if _SPARC
/************************************************************************
 *                           SPARC varargs                              *
 ************************************************************************/
       /* Sun's convention: */
#   define __va_start(ap,parmN) (ap=(__va_list) &__builtin_va_alist)
#   define __va_arg(ap,type) ((type*)__builtin_va_arg_incr((type*)ap))[0]

#elif _UPA
/************************************************************************
 *                          HPUX/PARISC  varargs                        *
 ************************************************************************/
    #define __WORD_MASK		0xFFFFFFFC
    #define __DWORD_MASK	0xFFFFFFF8

    typedef double *__va_list;
    #define _VA_LIST_DEFINED

    /*
     > 8 bytes -- passed by reference.
     > 4 && <= 8 -- right-justified in 8 bytes.
     <= 4 -- right-justified in 4 bytes.
     ap -- 4-byte aligned address of previous argument.
     type > 8 -- address of argument is at ap -4.
     type <= 8 -- address of argument in ap - sizeof type.
    */

    #define __va_start(ap,__parmN) __builtin_va_start (ap, &__parmN)
    #define __va_arg(ap,type)					\
	(sizeof(type) > 8 ?					\
	    ((ap = (__va_list) ((char *)ap - sizeof (int))),	\
	    (*((type *) (*((int *) (ap))))))			\
	    : ((ap = (__va_list) ((long)((char *)ap - 		\
	    sizeof (type)) & (sizeof(type) > 4 ?		\
		__DWORD_MASK : __WORD_MASK))),			\
		(*((type *) ((char *)ap +			\
		((8 - sizeof(type)) % 4))))))
    #define _STDARG_INCLUDED
#elif _I860 && _860_ABI
/************************************************************************
 *                           i860 ABI varargs                            *
 ************************************************************************/
    /* Here, memoflo means the value of r28 at procedure entry. */
    /* end_of_iregs is sp at procedure entry. */
#if _NEW_ABI
#define __TO_WORDS >> 2
#define __ADJUST -(12+8)	/* 12 FP + 8 INT regs. */
#else
#define __TO_WORDS
#define __ADJUST
#endif
#   define __va_start(ap,parm) 				\
	  {extern char _ADDRESS_OF_MEMOFLO_AREA[]; 	\
	   extern long _ADDRESS_OF_INT_END_AREA[];      \
	   extern int  _PARMBYTES_USEDI##parm[], 	\
		       _PARMBYTES_USEDF##parm[], 	\
		       _PARMBYTES_USEDM##parm[]; 	\
	  (ap).ireg_bytes = (int)_PARMBYTES_USEDI##parm __TO_WORDS,\
	  (ap).freg_bytes = (int)_PARMBYTES_USEDF##parm __TO_WORDS,\
	  (ap).mem_base = (void *)&parm,	        \
	  (ap).mem_base = _ADDRESS_OF_MEMOFLO_AREA+	\
			(int)_PARMBYTES_USEDM##parm; 	\
	  (ap).end_of_iregs = _ADDRESS_OF_INT_END_AREA __ADJUST;	\
	  }
#   ifndef _VA_LIST_DEFINED
#   define _VA_LIST_DEFINED
    typedef struct {
	unsigned int ireg_bytes;/* How many int regs consumed 'til now? */
	unsigned int freg_bytes;/* How many flt regs consumed 'til now? */
#ifndef _NEW_ABI	
	char *mem_base;	     /* Address of overflow area. */
	long *end_of_iregs;  /* End of where we stored int regs. */
#else	
	long *end_of_iregs;  /* End of where we stored int regs. */
	char *mem_base;	     /* Address of overflow area. */
#endif  
        } __va_list;
#   endif
#   define __va_arg(ap,type) \
	(*(type*) _va_arg(&ap,sizeof(type),_INFO(type,0),_INFO(type,2)))
    extern void *_va_arg(__va_list *__V, unsigned __len, unsigned __align, int __type);
#ifdef __OLD_VARARGS
#define va_start(ap) {__va_start(ap,_va_alist); ap.ireg_bytes -= sizeof(int) __TO_WORDS;}
#define va_alist _va_alist, ...
#define va_dcl int _va_alist;
#endif
#elif _I860 || _SGL    /* But NOT ABI */
/************************************************************************
 *                         i860 non-abi varargs                         *
 *			   Seagull chip as well				*
 ************************************************************************/
    /* Here, memoflo means the value of sp at procedure entry, */
    /* since memoflo values are stored just above sp. */
#   define __va_start(ap,parm) 			\
	  {extern long _ADDRESS_OF_MEMOFLO_AREA[]; 	\
	   extern int  _PARMBYTES_USEDI##parm[], 	\
		       _PARMBYTES_USEDF##parm[], 	\
		       _PARMBYTES_USEDM##parm[]; 	\
	  (ap).ireg_bytes = (int)_PARMBYTES_USEDI##parm,\
	  (ap).freg_bytes = (int)_PARMBYTES_USEDF##parm,\
	  (ap).oflo_bytes = (int)_PARMBYTES_USEDM##parm,\
	  (ap).mem_base = (void *)&parm,		\
	  (ap).mem_base = _ADDRESS_OF_MEMOFLO_AREA; 	\
	  }
#   ifndef _VA_LIST_DEFINED
#   define _VA_LIST_DEFINED
    typedef struct {
	unsigned int ireg_bytes;/* How many int regs consumed 'til now? */
	unsigned int freg_bytes;/* How many flt regs consumed 'til now? */
	long oflo_bytes;     /* How many bytes have been placed in memory 
							'til now? */
	long *mem_base;      /* Address of memory oflo area. */
        } __va_list;
#   endif
#   define __va_arg(ap,type) \
	(*(type*) _va_arg(&ap,sizeof(type),_INFO(type,0),_INFO(type,1)))
    extern void *_va_arg(__va_list *__V, unsigned __len, unsigned __align, int __type);
#ifdef __OLD_VARARGS
#define va_start(ap) {__va_start(ap,_va_alist); \
		ap.ireg_bytes -= sizeof(int); ap.freg_bytes -= sizeof(double);}
#define va_alist _va_alist, ...
#define va_dcl int _va_alist;
#endif
#elif _NAM
/************************************************************************
 *                           _NAM varargs                               *
 ************************************************************************/
#   define __va_start(ap,parmN)\
	(ap=(char *)&parmN + (sizeof(parmN)))
#   ifndef _VA_LIST_DEFINED
#   define _VA_LIST_DEFINED
    typedef void *__va_list;
#   endif
#   define __va_arg(ap, type)\
        ( *(type *) (\
			(char *)(\
				  ap = (char *)ap + sizeof(type)\
				) - sizeof(type)\
		    )\
	)

#elif _RS6000
/************************************************************************
 *                           _RS6000 varargs                            *
 ************************************************************************/
#   ifndef _VA_LIST_DEFINED
#   define _VA_LIST_DEFINED
    typedef __vararg_char *__va_list;
#   endif

#    define __va_start(ap,parmN) (ap=(__vararg_char *)	\
     ((unsigned int)&parmN + (sizeof(parmN))))

#   define __va_arg(ap, mode) ((mode *)((((ap)+=(((sizeof(mode)+3)/4)*4))-sizeof(mode))))[0]


#elif _I386 || _VAX || _I286 || _I8086 || _HOBBIT_L
/************************************************************************
 *            Generic little-endian version 
 ************************************************************************/
#    define __va_start(ap,parmN) (ap=(__vararg_char *)&parmN + \
	(sizeof(parmN)>sizeof(int)?sizeof(parmN):sizeof(int)))
#else
/************************************************************************
 *            Generic big-endian version 
 *            (short arguments are assumed right-aligned in a word)
 ************************************************************************/
#    define __va_start(ap,parmN) (ap=(__vararg_char *)&parmN + sizeof(parmN))
#endif

#ifndef _VA_LIST_DEFINED
#    define _VA_LIST_DEFINED
     typedef void *__va_list;
#endif

#if _I386 || _VAX || _I286 || _I8086
#   define __va_arg(ap, type)\
      ( *(type *) (\
	  (__vararg_char *)(\
	    ap = (__vararg_char *)ap + \
		((sizeof(type)+(sizeof(int)-1)) & ~(sizeof(int)-1))\
		  ) - ((sizeof(type)+sizeof(int)-1) & ~(sizeof(int)-1))\
	 )\
      )
#elif _HOBBIT
#   if _HOBBIT_L
#       define _NNVAARG (-1)  /* Never right align in little-endian */
#   else
#       define _NNVAARG 2 /* Right-align half-words in bit-endian */
#   endif

   /* Alignment: doubles on 8-byte boundary, long-doubles on 16-byte boundary*/
   /* Everything else on 4 byte boundary */
#   define _WA_(type) (sizeof(type)==8?8:sizeof(type)==16?16:4)
  /* Size of type as word-multiple*/
#   define _WS_(type) (  (sizeof(type) + 3) & ~3  )
#   define _ALIGN_(x,type) \
	(_WA_(type) <= 4?\
	    (long)(x):\
	    ((long)(x) + _WA_(type)-1) & ~(_WA_(type)-1))
#   define __va_arg(ap, type)\
      ( *(type *) (\
		      (__vararg_char *)(\
			 ap = (__vararg_char *)_ALIGN_(ap,type) + _WS_(type) \
				      ) - _WS_(type)\
			+ (sizeof(type)<=_NNVAARG?4-sizeof(type):0)\
		     )\
      )

#elif _R3000
/************************************************************************
 *                          MIPS R3000 varargs                          *
 ************************************************************************/
#   define __va_arg(ap, type)\
      ( (type *) (\
		      (__vararg_char *)(\
			    ap = (__vararg_char *) ((((int)ap +\
			   (_INFO(type,0)<=4?3:7))&(_INFO(type,0)<=4?-4:-8))+\
			   sizeof(type) ) )\
		     )\
      )[-1]

#elif !defined __va_arg
#   if _IBM370 || _ENGINE
#       define _NNVAARG 3   /* Largest small struct that is right aligned. */
#   else
#       define _NNVAARG 2
#   endif
#   define __va_arg(ap, type)\
      ( *(type *) (\
		      (__vararg_char *)(\
			    ap = (__vararg_char *)ap + ((sizeof(type) +3) &~3)\
			      ) - ((sizeof(type) +3) &~3)\
			+ (sizeof(type)<=_NNVAARG?4-sizeof(type):0)\
		     )\
      )
#endif

#define __va_end(ap)

#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();
#endif /*__STDARG_H*/
