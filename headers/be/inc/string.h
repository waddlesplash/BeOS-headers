/*
 *	string.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __string__
#define __string__

#pragma options align=mac68k

#include <ansi_parms.h>
#include <size_t.h>
#include <null.h>

#define __max_errstr	32

__extern_c

void * memcpy (void * dst, const void * src, size_t n);
void * memmove(void * dst, const void * src, size_t n);

void * memset(void * dst, int val, size_t n);

void * memchr(const void * src, int val, size_t n);

int		 memcmp(const void * src1, const void * src2, size_t n);

size_t strlen(const char * str);

char * strcpy (char * dst, const char * src);
char * strncpy(char * dst, const char * src, size_t n);

char * strcat (char * dst, const char * src);
char * strncat(char * dst, const char * src, size_t n);

int    strcmp (const char * str1, const char * str2);
int    strncmp(const char * str1, const char * str2, size_t n);

int    strcoll(const char * str1, const char * str2);
size_t strxfrm(      char * str1, const char * str2, size_t n);

char * strchr (const char * str, int chr);
char * strrchr(const char * str, int chr);
char * strpbrk(const char * str, const char * set);
size_t strspn (const char * str, const char * set);
size_t strcspn(const char * str, const char * set);
char * strtok (      char * str, const char * set);

char * strstr(const char * str, const char * pat);

char * strerror(int errnum);

char * __strerror(int errnum, char * str);

__end_extern_c

#pragma options align=reset

#endif
