/* ++++++++++
	File:			image.h
	Description:	kernel interface for managing executable images

	Copyright (c) 1995-96 by Be Incorporated.  All Rights Reserved.
+++++ */

#ifndef _IMAGE_H
#define	_IMAGE_H

#ifndef _OS_H
#include <OS.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct BFile;
typedef struct BFile	BFile;

typedef	long image_id;

typedef enum {
	B_APP_IMAGE = 1,
	B_LIBRARY_IMAGE,
	B_ADD_ON_IMAGE
} image_type;


/* ----------
	image_info structure - everthing there is to know about an executable
	image
----- */

typedef struct {
	long		volume;						/* volume */
	long		directory;					/* directory */
	char		name [B_FILE_NAME_LENGTH];	/* file name */
	void		*text;						/* address of text */
	long		text_size;					/* size of text */
	void		*data;						/* address of data */
	long		data_size;					/* size of data */
	image_type	type;						/* type */
} image_info;

extern long			get_nth_image_info (team_id team, long n, image_info *info);

extern thread_id	load_executable(BFile *file, int argc, const char **argv,
						const char **envp);
extern image_id		load_add_on(BFile *file);
extern long			unload_add_on(image_id imid);
extern long			get_image_symbol(image_id imid, char *name,
						int sclass, void **ptr);
extern long			get_nth_image_symbol(image_id imid, int index,
							char *buf, int *bufsize, int *sclass, void **ptr);

#ifdef __cplusplus
}
#endif

#endif
