/* ++++++++++
	File:			image.h
	Description:	kernel interface for managing executable images

	Copyright (c) 1995-97 by Be Incorporated.  All Rights Reserved.
+++++ */

#pragma once

#ifndef _IMAGE_H
#define	_IMAGE_H

#include <OS.h>
#include <sys/param.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef	int32 image_id;

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
	image_id	id;							/* image id */
	image_type	type;						/* type */
	int32		sequence;					/* sequence number */
	int32		init_order;					/* the larger the later to be inited */
	B_PFV		init_routine;				/* init routine */
	B_PFV		term_routine;				/* term routine */
	dev_t		device;						/* device and node for file */
	ino_t		node;
	char        name[MAXPATHLEN];           /* full pathname of image */
	void		*text;						/* address of text */
	void		*data;						/* address of data */
	int32		text_size;					/* size of text */
	int32		data_size;					/* size of data */
} image_info;


extern thread_id	load_image(int32 argc, const char **argv, const char **envp);
extern image_id		load_add_on(const char *path);
extern status_t		unload_add_on(image_id imid);

extern status_t		_get_image_info (image_id image, image_info *info,
									 size_t size);
extern status_t		_get_next_image_info (team_id team, int32 *cookie,
										  image_info *info, size_t size);

#define get_image_info(image, info)                        \
              _get_image_info((image), (info), sizeof(*(info)))
#define get_next_image_info(team, cookie, info)   \
	          _get_next_image_info((team), (cookie), (info), sizeof(*(info)))


/* Symbol type constants */
#define	B_SYMBOL_TYPE_CODE		0x0
#define	B_SYMBOL_TYPE_DATA		0x1
#define	B_SYMBOL_TYPE_TEXT		0x2
#define	B_SYMBOL_TYPE_TOC		0x3
#define	B_SYMBOL_TYPE_GLUE		0x4

extern status_t		get_image_symbol(image_id imid, const char *name,
						int32 sclass, void **ptr);
extern status_t		get_nth_image_symbol(image_id imid, int32 index,
							char *buf, int32 *bufsize, int32 *sclass, void **ptr);


/* the flags for clear_caches() */
#define B_FLUSH_DCACHE         0x0001   /* data cache */
#define B_INVALIDATE_DCACHE    0x0002
#define B_FLUSH_ICACHE         0x0004
#define B_INVALIDATE_ICACHE    0x0008   /* instruction cache */

void clear_caches(void *addr, size_t len, uint32 flags);


#ifdef __cplusplus
}
#endif

#endif
