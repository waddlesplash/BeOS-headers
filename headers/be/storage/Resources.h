/***************************************************************************
//
//	File:			Resources.h
//
//	Description:	BResources class
//
//	Copyright 1992-97, Be Incorporated, All Rights Reserved.
//
//*************************************************************************/

#ifndef RESOURCES_H
#define RESOURCES_H

#include <SupportDefs.h>
#include <File.h>

struct	rsrc_map;
struct	rsrc_desc;
class	RTDF;


class	BResources {
public:
					BResources();
					BResources(const BFile *file, bool truncate = FALSE);
virtual				~BResources();

		status_t	SetTo(const BFile *file, bool truncate = FALSE);

const	BFile &		File() const;

		status_t	AddResource(type_code type, 
								int32 id, 
								const void *data,
								size_t data_size, 
								const char *name=NULL);

		status_t	WriteResource(type_code type, 
								  int32 id, 
								  const void *data,
								  off_t offset, 
								  size_t data_size);

		status_t	ReadResource(type_code type, 
								 int32 id, 
								 void *data, 
								 off_t offset, 
								 size_t data_size);

		void		*FindResource(type_code type, 
								  int32 id, 
								  size_t *data_size);

		void		*FindResource(type_code type, 
								  const char *name, 
								  size_t *data_size);

		bool		HasResource(type_code type, int32 id);

		bool		HasResource(type_code type, const char *name);

		bool		GetResourceInfo(int32 resIndex,
									type_code* typeFound,
									int32* idFound,
									const char **nameFound,
									size_t* size);

		bool		GetResourceInfo(type_code type,
									int32 resIndex,
									int32* idFound,
									const char **nameFound,
									size_t* size);

		bool		GetResourceInfo(type_code type,
									int32 id,
									const char **nameFound,
									size_t* size);

		bool		GetResourceInfo(type_code type,
									const char *name,
									int32* idFound,
									size_t* size);

		int			RemoveResource( type_code type,  int32 id);

private:
		BFile		fFile;
		RTDF		*the_datafile;
		rsrc_map	*the_map;
		bool		fReadOnly;
		bool		fDirty;

		void		dump_map();
		rsrc_map	*find_type(type_code type);
		rsrc_desc 	*find_id(rsrc_map *a_map, int32 id);
		rsrc_desc 	*find_entry(type_code type, int32 id);
		void		add_type(type_code type);
		void		add_desc(rsrc_map *a_map, int32 id, int32 df_id, 
							 size_t name_length, const char *name);
		long		load_map();
		int32		calc_size();
		void		free_map();
		void		save_map();
		rsrc_desc 	*find_name(rsrc_map *a_map, const char *name);
		rsrc_desc 	*find_entry(type_code type, const char *name);
};

#endif
