/*
   This header file defines the C interface to file system
   query API on the BeOS.  The API is a simple derivative
   form of the Posix opendir()/readdir()/closedir() functions
   (and in fact we return dirent structures just like readdir).

   Copyright 1997 Be Inc.
*/


#ifndef _FS_QUERY_H
#define _FS_QUERY_H

#include <SupportDefs.h>
#include <dirent.h>


/* flags for fs_open_query() */

#define		B_LIVE_QUERY		0x00000001


#ifdef  __cplusplus
extern "C" {
#endif


DIR           *fs_open_query(dev_t device, const char *query, uint32 flags);
DIR           *fs_open_live_query(dev_t device, const char *query,
								  uint32 flags, port_id port, int32 token);
int            fs_close_query(DIR *d);
struct dirent *fs_read_query(DIR *d);


#ifdef  __cplusplus
}
#endif


#endif /* _FS_QUERY_H */
