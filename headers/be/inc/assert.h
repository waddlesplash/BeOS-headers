/*
 *   assert.h -- ANSI 
 *
 *   Diagnostic facilities.
 *
 *           Copyright (c) 1991, MetaWare Incorporated
 */

#ifndef _ASSERT_H
#define _ASSERT_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#undef	assert

#if (defined(NDEBUG) && !defined(__PENPOINT__)) \
 || (!defined(DEBUG) &&  defined(__PENPOINT__))

    #define assert(ignore) ((void)0)
    #define _uassert(ignore) ((void)0)

#else
    void _assert(void *, void *, unsigned);
    #define assert(E) ((E)? (void)0 : _assert(#E, __FILE__, __LINE__))

    void _u_assert(void *, void *, unsigned);
    #define _uassert(E) ((E)? (void)0 : _u_assert(#E, __FILE__, __LINE__))

#endif /* NDEBUG */

#if __HIGHC__
    #ifdef __UNICODE__
	#define Uassert _uassert
    #else
	#define Uassert assert
    #endif
#endif

#ifdef __CPLUSPLUS__
}
#endif
#endif /*_ASSERT_H */
