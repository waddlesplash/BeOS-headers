/*
 * Copyright (c) 1993 MetaWare, Incorporated
 *
 * This file is internal to malloc().  It is not intended for general use.
 *
 */


#ifndef _MALLOC_I_H
#define _MALLOC_I_H

#pragma push_align_members(64);

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#if !defined(_MAL_ALIGN)

#if defined _AM29K || defined _IBM370 || defined _SPARC || defined _IPENTIUM
#    define _MAL_ALIGN 8
#elif defined MSDOS_16
#    define _MAL_ALIGN 2
#elif defined _I860
#    define _MAL_ALIGN 16
#else
#    define _MAL_ALIGN 4
#endif

#endif

#if _MAL_ALIGN == 2
#    define ALIGN_MASK 1
#elif _MAL_ALIGN == 4
#    define ALIGN_MASK 3
#elif _MAL_ALIGN == 8
#    define ALIGN_MASK 7
#elif _MAL_ALIGN == 16
#    define ALIGN_MASK 15
#else
#    error Alignment factor is other than 2, 4, 8, or 16!
#    define _MAL_ALIGN 4 
#    define ALIGN_MASK 3 
#endif


/*
 * items are basic units of memory
 * "size" is the number of bytes of this item including the header.
 * It will always be aligned to MAL_ALIGN. If free, the size will have
 * the least-significant bit set.
 * "prev_size" is only used if debug level is > 1. It is the size of the
 * previous item. This gives the integrity checker more to work with.
 * "link" is used to chain free items together.
 */
typedef struct _item_header {
    unsigned size;		/*Size of this item*/
    unsigned prev_size;		/*Size of previous item (if debug level > 1)*/
    struct _item_header *fwd_link;   /*Free chain link (only if free)*/
    struct _item_header *prev_link;
    } _ITEM_HEADER;

/*
 * Segments contain a chain of allocated or unallocated items.
 */
typedef struct _segment_header {
    struct _segment_header *prev;
    struct _segment_header *next;
    unsigned size;
    _ITEM_HEADER *last_item_ptr;
    _ITEM_HEADER first_item;
    } _SEGMENT_HEADER;

#define _BUCKET_COUNT 13
#define _BLEN0   8		/*Largest item in bucket 0*/
#define _BLEN1   16		/*Largest item in bucket 1*/
#define _BLEN2   32		/*Largest item in bucket 2*/
#define _BLEN3   64		/*Largest item in bucket 3*/
#define _BLEN4   128		/*Largest item in bucket 4*/
#define _BLEN5   256		/*Largest item in bucket 5*/
#define _BLEN6   512		/*Largest item in bucket 6*/
#define _BLEN7   1024		/*Largest item in bucket 7*/
#define _BLEN8   2048		/*Largest item in bucket 8*/
#define _BLEN9   4096		/*Largest item in bucket 9*/
#define _BLEN10  8192		/*Largest item in bucket 10*/
#define _BLEN11  32000		/*Largest item in bucket 11*/
#define _BLEN12  0xFFFFFFFFUL	/*Largest item in bucket 12*/

#define _ITEM_SIZE(ip) ((ip)->size&_SIZE_MASK)
#define _NEXT_ITEM(ip) ((_ITEM_HEADER*)((char *)(ip)+_ITEM_SIZE(ip)))
#define _PREV_ITEM(ip) ((_ITEM_HEADER*)((char *)(ip)-ip->prev_size))
#define _SET_FREE_FLAG(ip)  ((ip)->size |= 1)
#define _CLEAR_FREE_FLAG(ip)  ((ip)->size &= ~1)
#define _IS_FREE(ip)   (((ip)->size & 1)!=0)
#define _NEXT_FREE(ip) ((ip)->fwd_link)
#define _PREV_FREE(ip) ((ip)->prev_link)
#define _SIZE_MASK (~1)
#define _USING_DOUBLE_LINKS (_malloc_level > 0)

#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();

#endif /* _MALLOC_I_H */
