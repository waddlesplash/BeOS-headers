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
	B_ADD_ON_IMAGE,
	B_SYSTEM_IMAGE
} image_type;


/* ----------
	image_info structure - everthing there is to know about an executable
	image
----- */

typedef struct {
	long		volume;						/* volume */
	long		directory;					/* directory */
	char		name [B_FILE_NAME_LENGTH];	/* file name */
	image_id	id;							/* image id */
	void		*text;						/* address of text */
	long		text_size;					/* size of text */
	void		*data;						/* address of data */
	long		data_size;					/* size of data */
	image_type	type;						/* type */
} image_info;


extern thread_id	load_executable(BFile *file, long argc, const char **argv,
						const char **envp);

extern image_id		load_add_on(BFile *file);
extern long			unload_add_on(image_id imid);

extern long			get_image_info (image_id image, image_info *info);
extern long			get_nth_image_info (team_id team, long n, image_info *info);

/* Symbol type constants */
#define	B_SYMBOL_TYPE_CODE		0x0
#define	B_SYMBOL_TYPE_DATA		0x1
#define	B_SYMBOL_TYPE_TEXT		0x2
#define	B_SYMBOL_TYPE_TOC		0x3
#define	B_SYMBOL_TYPE_GLUE		0x4

extern long			get_image_symbol(image_id imid, char *name,
						long sclass, void **ptr);
extern long			get_nth_image_symbol(image_id imid, long index,
							char *buf, long *bufsize, long *sclass, void **ptr);

#ifdef __cplusplus
}
#endif

#endif
