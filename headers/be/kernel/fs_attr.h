/*
   This header file defines the interface to extended file
   attributes on the BeOS.

   Copyright 1997 Be Inc.
*/


#ifndef _FS_ATTR_H
#define _FS_ATTR_H

#include <SupportDefs.h>
#include <dirent.h>


typedef struct attr_info
{
	uint32     type;
	off_t      size;
} attr_info;



#ifdef  __cplusplus
extern "C" {
#endif

ssize_t fs_read_attr(int fd, const char *attribute, uint32 type, off_t pos,
					 void *buf, size_t count);
ssize_t fs_write_attr(int fd, const char *attribute, uint32 type, off_t pos,
					  const void *buf, size_t count);

int		fs_remove_attr(int fd, const char *attr);



DIR           *fs_open_attr_dir(const char *path);
DIR           *fs_fopen_attr_dir(int fd);
int            fs_close_attr_dir(DIR *dirp);
struct dirent *fs_read_attr_dir(DIR *dirp);
void           fs_rewind_attr_dir(DIR *dirp);

int fs_stat_attr(int fd, const char *name, struct attr_info *ai);


#ifdef  __cplusplus
}
#endif


#endif /* _FS_ATTR_H */
