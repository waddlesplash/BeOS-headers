/*
 *   string.h -- ANSI 
 *
 *   Functions, types, and macros for manipulating strings and
 *   arbitrary areas of memory.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */
#ifndef _STRING_H
#define _STRING_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#ifndef _SIZET_H
#include <sizet.h>
#endif

#ifndef _UNICHAR_DEFINED
    typedef unsigned short _UNICHAR;
    #define _unichar _UNICHAR
    #define _UNICHAR_DEFINED
#endif

#ifndef NULL
#define NULL            ((void *)0)
#endif
#define _MAXSTRING (0xffffffff)

/* Copying functions */
extern  void *      memcpy(void *__s1, const void *__s2, size_t __n);
extern  void *      memmove(void *__s1, const void *__s2, size_t __n);
extern  char *      strcpy(char *__s1, const char *__s2);
extern  char *      strncpy(char *__s1, const char *__s2, size_t __n);

/* Concatenation functions */
extern  char *      strcat(char *__s1, const char *__s2);
extern  char *      strncat(char *__s1, const char *__s2, size_t __n);

/* Comparison functions */
extern  int         memcmp(const void *__s1, const void *__s2, size_t __n);
extern  int         strcmp(const char *__s1, const char *__s2);
extern  int         strcoll(const char *__s1, const char *__s2);
extern  int         strncmp(const char *__s1, const char *__s2, size_t __n);
extern  size_t      strxfrm(char *__s1, const char *__s2, size_t __n);

/* Search functions */
extern  void *      memchr(const void *__s, int __c, size_t __n);
extern  char *      strchr(const char *__s, int __c);
extern  size_t      strcspn(const char *__s1, const char *__s2);
extern  char *      strpbrk(const char *__s1, const char *__s2);
extern  char *      strrchr(const char *__s, int __c);
extern  size_t      strspn(const char *__s1, const char *__s2);
extern  char *      strstr(const char *__s1, const char *__s2);
extern  char *      strtok(char *__s1, const char *__s2);

/* Miscellaneous functions */
extern  void *      memset(void *__s, int __c, size_t __n);
#ifndef strerror	/*strerror may be a macro on Sun and BSD systems*/
extern  char *      strerror(int __errnum);
#endif
extern  size_t      strlen(const char *__s);

/* Non-ansi additions */
extern  void *	    _rmemcpy(void *__d, const void *__s, size_t __len);
extern  char *	    _rstrcpy(char *__d, const char *__s);
extern  char *	    _rstrncpy(char *__d, const char *__s, size_t __len);
extern  char *	    _strncat(char *__s1, const char *__s2, size_t __len);
extern  char *	    _strcats(int __count, char *__s1, const char *__s2,...);
extern  char *	    _strrev(char *__s);
extern  void *	    _memccpy(void *, void *, int, unsigned int);
extern  char *	    _strnset(char *__s, int __character, size_t __kount);
extern  char *	    _strset(char *__s, int __c);
extern  char *	    _strdup(const char *s1);
extern  char *	    _strlwr(char *__s1);
extern  char *	    _strupr(char *__s1);
extern  int 	    _strcmpi(const char *__s1, const char *__s2);
extern  int 	    _stricmp(const char *__s1, const char *__s2);
extern  int 	    _strnicmp(const char *__s1, const char *__s2, size_t __n);
extern  int 	    _memicmp(const void *, const void *, unsigned int);
extern  char * 	    _strerror(char *);
#if _I386
extern _Far void *  _fmemcpy(_Far void *dest, _Far const void *src, size_t n);
#endif

/* Unicode functions */

extern  _unichar *  _ustrcat(_unichar *__s1, const _unichar *__s2);
extern  _unichar *  _ustrchr(const _unichar *__s, int __c);
extern  int         _ustrcmp(const _unichar *__s1, const _unichar *__s2);
extern  _unichar *  _ustrcpy(_unichar *__s1, const _unichar *__s2);
extern  size_t      _ustrcspn(const _unichar *__s1, const _unichar *__s2);
extern  size_t      _ustrlen(const _unichar *__s);
extern  _unichar *  _ustrncat(_unichar *__s1, const _unichar *__s2, size_t __n);
extern  int         _ustrncmp(const _unichar *__s1, const _unichar *__s2,
				size_t __n);
extern  _unichar *  _ustrncpy(_unichar *__s1, const _unichar *__s2, size_t __n);
extern  _unichar *  _ustrpbrk(const _unichar *__s1, const _unichar *__s2);
extern  _unichar *  _ustrrchr(const _unichar *__s, int __c);
extern  size_t      _ustrspn(const _unichar *__s1, const _unichar *__s2);
extern  _unichar *  _ustrstr(const _unichar *__s1, const _unichar *__s2);
extern  int 	    _ustrcmpi(const _unichar *__s1, const _unichar *__s2);
extern  int 	    _ustrnicmp(const _unichar *__s1, const _unichar *__s2,
				size_t __n);
extern  _unichar *  _ustrlwr(_unichar *__s1);
extern  _unichar *  _ustrupr(_unichar *__s1);
extern  _unichar *  _ustrnset(_unichar *__s, int __character, size_t __kount);
extern  _unichar *  _ustrdup(const _unichar *s1);
extern  int 	    _ustricmp(const _unichar *__s1, const _unichar *__s2);
extern  _unichar *  _ustrtok(_unichar *__s1, const _unichar *__s2);
extern  _unichar *  _ustrrev(_unichar *__s);
extern  _unichar *  _ustrset(_unichar *__s, int __c);
extern  _unichar *  _ustrerror(int __errnum);

extern  _unichar *  _uchrccpy(_unichar *__s1, const _unichar *__s2,
				_unichar __c, size_t __n);
extern  _unichar *  _uchrchr(const _unichar *__s, _unichar __c, size_t __n);
extern  _unichar *  _uchrcpy(_unichar *__s1, const _unichar *__s2, size_t __n);
extern  int         _uchrcmp(const _unichar *__s1, const _unichar *__s2,
				size_t __n);
extern  int         _uchricmp(const _unichar *__s1, const _unichar *__s2,
				size_t __n);
extern  _unichar *  _uchrset(_unichar *__s, _unichar __c, size_t __n);

#if __HIGHC__
  #ifdef __UNICODE__
    #define Ustrcat   _ustrcat
    #define Ustrchr   _ustrchr
    #define Ustrcmp   _ustrcmp
    #define Ustrcpy   _ustrcpy
    #define Ustrcspn  _ustrcspn
    #define Ustrlen   _ustrlen
    #define Ustrncat  _ustrncat
    #define Ustrncmp  _ustrncmp
    #define Ustrncpy  _ustrncpy
    #define Ustrpbrk  _ustrpbrk
    #define Ustrrchr  _ustrrchr
    #define Ustrspn   _ustrspn
    #define Ustrstr   _ustrstr
    #define Ustrcmpi  _ustrcmpi
    #define Ustrnicmp _ustrnicmp
    #define Ustrlwr   _ustrlwr
    #define Ustrupr   _ustrupr
    #define Ustrnset  _ustrnset
    #define Ustrdup   _ustrdup
    #define Ustricmp  _ustricmp
    #define Ustrtok   _ustrtok
    #define Ustrrev   _ustrrev
    #define Ustrset   _ustrset
    #define Ustrerror _ustrerror

    #define Uchrccpy  _uchrccpy
    #define Uchrchr   _uchrchr
    #define Uchrcpy   _uchrcpy
    #define Uchrcmp   _uchrcmp
    #define Uchricmp  _uchricmp
    #define Uchrset   _uchrset
  #else
    #define Ustrcat   strcat
    #define Ustrchr   strchr
    #define Ustrcmp   strcmp
    #define Ustrcpy   strcpy
    #define Ustrcspn  strcspn
    #define Ustrlen   strlen
    #define Ustrncat  strncat
    #define Ustrncmp  strncmp
    #define Ustrncpy  strncpy
    #define Ustrpbrk  strpbrk
    #define Ustrrchr  strrchr
    #define Ustrspn   strspn
    #define Ustrstr   strstr
    #define Ustrcmpi  _strcmpi
    #define Ustrnicmp _strnicmp
    #define Ustrlwr   _strlwr
    #define Ustrupr   _strupr
    #define Ustrnset  _strnset
    #define Ustrdup   _strdup
    #define Ustricmp  _stricmp
    #define Ustrtok   strtok
    #define Ustrrev   _strrev
    #define Ustrset   _strset
    #define Ustrerror strerror

    #define Uchrccpy  _memccpy
    #define Uchrchr   memchr
    #define Uchrcpy   memcpy
    #define Uchrcmp   memcmp
    #define Uchricmp  _memicmp
    #define Uchrset   memset
  #endif
#endif

#include <_na.h>
#if _NA_NAMES 
    _NA(memccpy)
    _NA(strnset)
    _NA(strset)
    _NA(strdup)
    _NA(strrev)
    _NA(strlwr)
    _NA(strupr)
    _NA(strcmpi)
    _NA(stricmp)
    _NA(strnicmp)
    _NA(memicmp)
#elif _MSDOS && __HIGHC__
    extern  void *  memccpy(void *, void *, int, unsigned int);
    extern  char *  strnset(char *__s, int __character, size_t __kount);
    extern  char *  strset(char *__s, int __c);
    extern  char *  strdup(const char *s1);
    extern  char *  strrev(char *__s);
    extern  char *  strlwr(char *__s1);
    extern  char *  strupr(char *__s1);
    extern  int     strcmpi(const char *__s1, const char *__s2);
    extern  int     stricmp(const char *__s1, const char *__s2);
    extern  int	    strnicmp(const char *__s1, const char *__s2, size_t __n);
    extern  int     memicmp(const void *, const void *, unsigned int);
#endif

#if _MSDOS || _MSNT || _OS2
extern void _movedata(unsigned int, unsigned int, unsigned int, unsigned int,
	unsigned int);
    #if _NA_NAMES
	_NA(movedata)
    #elif _MSDOS && __HIGHC__
	extern void movedata(unsigned int, unsigned int, unsigned int,
		unsigned int, unsigned int);
    #endif

#if __HIGHC__ 
    #ifdef __CPLUSPLUS__
    inline int _compare(const void *__s1, const void *__s2, size_t __n) {
	return memcmp(__s1,__s2,__n);
	}
    #else
    #define _compare(s1, s2, n) memcmp(s1, s2, n)
    #endif
#endif /*__HIGHC__*/

#endif /*_MSDOS || _MSNT || _OS2 */

#ifdef __CPLUSPLUS__
}
#endif
#endif /*_STRING_H*/
