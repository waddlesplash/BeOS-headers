#ifndef DLFCN_H
#define DLFCN_H
/*
** dlfcn - a dlfcn compatiblity header for ports
** This file is a rough compatibility layer which may help
** in porting applications that do not press too much on
** the technicalities of dlopen and family.  Semantics taken
** from man pages, not experience.
**
** By Andrew Bachmann, shatty@bemail.org
**
** Copyright (c) 2002 Andrew Bachmann.  All Rights Reserved.
** This file may be used under the terms of the OpenBeOS License.
**
*/

#ifdef BUILDING_DLFCN_H
#include <BeBuild.h>
#define IMPEXP_DLFCN _EXPORT
#else
#define IMPEXP_DLFCN
#endif

#ifdef __cplusplus
extern "C"
{
#endif

// values from the obos kernel dlfcn.h
#define RTLD_LAZY 0
#define RTLD_NOW 1
#define RTLD_GLOBAL 2
#define RTLD_LOCAL 0
#define RTLD_BEOS 5038

/*
 * open a shared library
 *
 * search the LIBRARY_PATH if an absolute path is not given
 */
IMPEXP_DLFCN
void *
dlopen(const char *file, int mode);

/*
 * close a shared library
 */
IMPEXP_DLFCN
int
dlclose(void *handle);

/*
 * find a dynamic symbol
 */
IMPEXP_DLFCN
void *
dlsym(void *handle, const char *symbol);

/*
 * stores the error message from the last call
 *
 * calling the function clears the message
 *
 * note: don't free the buffer, it is reused,
 *       as usual, not threadsafe
 */
IMPEXP_DLFCN
char *
dlerror(void);

/*
 * informative structure returned by dladdr
 */
typedef struct {
  const char * dli_fname; // the pathname of this library
  void * dli_fbase;       // the base address of this library
  const char * dli_sname; // the name of the highest addressed symbol
                          // whose address precedes the given address
  void * dli_saddr;       // the address of the above symbol
} Dl_info;

/*
 * provide access to information about the shared lib
 *
 * pass an address for a variable in the lib
 * (for example: something you got back from dlsym)
 *
 * returns nonzero if the address is found, otherwise 0
 */
IMPEXP_DLFCN
int
dladdr(void * address, Dl_info * dlip);

#ifdef __cplusplus
} /* "C" */
#endif

#endif // DLFCN_H
