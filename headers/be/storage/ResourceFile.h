#ifndef RESOURCE_FILE_H
#define RESOURCE_FILE_H

#include	<File.h>

struct	map;
struct	rsrc_desc;
class	RTDF;


class	BResourceFile : public BFile {

public:
					BResourceFile();
					BResourceFile(record_ref ref);
virtual				~BResourceFile();

virtual	long		Open(long open_mode);
virtual long		Close();
virtual	long		FileCreated();

		long		AddResource(ulong type, long id, void* data, long data_size, const char *name=0);
		long		WriteResource(ulong type, long id, void *data, long offset, long data_size);
		long		ReadResource(ulong type, long id, void *data, long offset, long data_size);
		void		*FindResource(ulong type, long id, long *data_size);
		void		*FindResource(ulong type, const char *name, long *data_size);
		bool		HasResource(long id, ulong type);
		bool		HasResource(const char *name, ulong type);
		bool		GetResourceInfo(long resIndex,
									ulong* typeFound,
									long* idFound,
									char** nameFound,
									long* size);
		bool		GetResourceInfo(ulong type,
									long resIndex,
									long* idFound,
									char** nameFound,
									long* size);
		bool		GetResourceInfo(long type,
									long id,
									char** nameFound,
									long* size);
		bool		GetResourceInfo(ulong type,
									const char *name,
									long* idFound,
									long* size);
		int			RemoveResource( ulong type,
								    long id);

		void		dump_map();

private:
		RTDF		*the_datafile;
		char		dirty;
		map			*the_map;
		bool		fReadOnly;
		int			fOpenCount;

		map			*find_type(ulong type);
		rsrc_desc 	*find_id(map *a_map, long id);
		rsrc_desc 	*find_entry(ulong type, long id);
		void		add_type(ulong type);
		void		add_desc(map *a_map, long id, long df_id, const char *name);
		void		load_map();
		long		calc_size();
		void		free_map();
		void		save_map();
		rsrc_desc 	*find_name(map *a_map, const char *name);
		rsrc_desc 	*find_entry(ulong type, const char *name);
};

#endif
