/*
   This header file defines the interface to extended 
   file system indexing on the BeOS.

   Copyright 1997 Be Inc.
*/


#ifndef _FS_INDEX_H
#define _FS_INDEX_H

#include <BeBuild.h>
#include <dirent.h>


typedef struct index_info
{
	uint32     type;
	off_t      size;
	time_t     modification_time;
	time_t     creation_time;
	uid_t      uid;
	gid_t      gid;
} index_info;



#ifdef  __cplusplus
extern "C" {
#endif


_IMPEXP_ROOT DIR           *fs_open_index_dir(dev_t device);
_IMPEXP_ROOT int            fs_close_index_dir(DIR *d);
_IMPEXP_ROOT struct dirent *fs_read_index_dir(DIR *d);
_IMPEXP_ROOT void           fs_rewind_index_dir(DIR *d);

_IMPEXP_ROOT int			fs_create_index(dev_t device, const char *name, int type, uint flags);
_IMPEXP_ROOT int			fs_remove_index(dev_t device, const char *name);

_IMPEXP_ROOT int			fs_stat_index(dev_t device, const char *name, struct index_info *buf);


#ifdef  __cplusplus
}
#endif


#endif /* _FS_INDEX_H */
