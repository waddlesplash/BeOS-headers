//******************************************************************************
//
//	File:		Message.h
//
//	Copyright 1994-97, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_MESSAGE_H
#define	_MESSAGE_H

#pragma once

#include <stddef.h>
#include <AppDefs.h>
#include <Rect.h>
#include <OS.h>
#include <Locker.h>
#include <Messenger.h>
#include <DataIO.h>
#include <ClassInfo.h>
#include <Entry.h>
#include <Flattenable.h>

/* ----------------------------------------------------------- */

class	BBlockCache;
class	BMessenger;
class	BHandler;

extern "C" void		_msg_cache_cleanup_();
extern "C" int		_init_message_();
extern "C" int		_delete_message_();

#define B_FIELD_NAME_LENGTH			255
#define B_PROPERTY_NAME_LENGTH		255

enum {
	B_NO_SPECIFIER = 0,
	B_DIRECT_SPECIFIER = 1,
	B_INDEX_SPECIFIER,
	B_REVERSE_INDEX_SPECIFIER,
	B_RANGE_SPECIFIER,
	B_REVERSE_RANGE_SPECIFIER,
	B_NAME_SPECIFIER,

	B_SPECIFIERS_END = 128
	// application specific forms should start here
};

/* ----------------------------------------------------------- */

class BMessage {

public:
		uint32		what;

					BMessage();
					BMessage(uint32 what);
					BMessage(const BMessage &a_message);
					BMessage(BMessage *a_message);
virtual				~BMessage();

		BMessage	&operator=(const BMessage &msg);

		status_t	AddSpecifier(const char *property);
		status_t	AddSpecifier(const char *property, int32 index);
		status_t	AddSpecifier(const char *property,
								int32 index,
								int32 range);
		status_t	AddSpecifier(const char *property, const char *name);
		status_t	AddSpecifier(const BMessage *specifier);

		status_t	GetCurrentSpecifier(int32 *index,
										BMessage *specifier = NULL,
										int32 *form = NULL,
										const char **property = NULL) const;
		bool		HasSpecifiers() const;
		status_t	PopSpecifier();

		status_t	AddRect(const char *name, BRect a_rect);
		status_t	AddPoint(const char *name, BPoint a_point);
		status_t	AddString(const char *name, const char *a_string);
		status_t	AddInt8(const char *name, int8 val);
		status_t	AddInt16(const char *name, int16 val);
		status_t	AddInt32(const char *name, int32 val);
		status_t	AddInt64(const char *name, int64 val);
		status_t	AddBool(const char *name, bool a_boolean);
		status_t	AddFloat(const char *name, float a_float);
		status_t	AddDouble(const char *name, double a_double);
		status_t	AddPointer(const char *name, const void *ptr);
		status_t	AddMessenger(const char *name, BMessenger messenger);
		status_t	AddRef(const char *name, const entry_ref *ref);
		status_t	AddMessage(const char *name, const BMessage *msg);
		status_t	AddFlat(const char *name,
							BFlattenable *obj,
							int32 num_adds = 1);
		status_t	AddData(const char *name,
							type_code type,
							const void *data,
							ssize_t numBytes,
							bool is_fixed_size = TRUE,
							int32 num_adds = 1);

		status_t	FindRect(const char *name, BRect *rect) const;
		status_t	FindRect(const char *name, int32 index, BRect *rect) const;
		status_t	FindPoint(const char *name, BPoint *pt) const;
		status_t	FindPoint(const char *name, int32 index, BPoint *pt) const;
		status_t	FindString(const char *name, const char **str) const;
		status_t	FindString(const char *name, int32 index, const char **str) const;
		status_t	FindInt8(const char *name, int8 *value) const;
		status_t	FindInt8(const char *name, int32 index, int8 *val) const;
		status_t	FindInt16(const char *name, int16 *value) const;
		status_t	FindInt16(const char *name, int32 index, int16 *val) const;
		status_t	FindInt32(const char *name, int32 *value) const;
		status_t	FindInt32(const char *name, int32 index, int32 *val) const;
		status_t	FindInt64(const char *name, int64 *value) const;
		status_t	FindInt64(const char *name, int32 index, int64 *val) const;
		status_t	FindBool(const char *name, bool *value) const;
		status_t	FindBool(const char *name, int32 index, bool *value) const;
		status_t	FindFloat(const char *name, float *f) const;
		status_t	FindFloat(const char *name, int32 index, float *f) const;
		status_t	FindDouble(const char *name, double *d) const;
		status_t	FindDouble(const char *name, int32 index, double *d) const;
		status_t	FindPointer(const char *name, void **ptr) const;
		status_t	FindPointer(const char *name, int32 index,  void **ptr) const;
		status_t	FindMessenger(const char *name, BMessenger *m) const;
		status_t	FindMessenger(const char *name, int32 index, BMessenger *m) const;
		status_t	FindRef(const char *name, entry_ref *ref) const;
		status_t	FindRef(const char *name, int32 index, entry_ref *ref) const;
		status_t	FindMessage(const char *name, BMessage *msg) const;
		status_t	FindMessage(const char *name,
								int32 index,
								BMessage *msg) const;
		status_t	FindFlat(const char *name, BFlattenable *obj) const;
		status_t	FindFlat(const char *name,
							int32 index,
							BFlattenable *obj) const;
		status_t	FindData(const char *name,
							type_code type,
							const void **data,
							ssize_t *numBytes) const;
		status_t	FindData(const char *name,
							type_code type,
							int32 index,
							const void **data,
							ssize_t *numBytes) const;

		// ---------------- old style FindXXX -----------------
		BRect		FindRect(const char *name, int32 index = 0) const;
		BPoint		FindPoint(const char *name, int32 index = 0) const;
		const char	*FindString(const char *string_name, int32 index = 0) const;
		int16		FindInt16(const char *name, int32 index = 0) const;
		int32		FindInt32(const char *name, int32 index = 0) const;
		bool		FindBool(const char *name, int32 index = 0) const;
		float		FindFloat(const char *name, int32 index = 0) const;
		double		FindDouble(const char *name, int32 index = 0) const;
		// -----------------------------

		status_t	ReplaceRect(const char *name, BRect a_rect);
		status_t	ReplaceRect(const char *name, int32 index, BRect a_rect);
		status_t	ReplacePoint(const char *name, BPoint a_point);
		status_t	ReplacePoint(const char *name, int32 index, BPoint a_point);
		status_t	ReplaceString(const char *name, const char *a_string);
		status_t	ReplaceString(	const char *name,
									int32 index, 
									const char *a_string);
		status_t	ReplaceInt8(const char *name, int8 val);
		status_t	ReplaceInt8(const char *name, int32 index, int8 val);
		status_t	ReplaceInt16(const char *name, int16 val);
		status_t	ReplaceInt16(const char *name, int32 index, int16 val);
		status_t	ReplaceInt32(const char *name, int32 val);
		status_t	ReplaceInt32(const char *name, int32 index, int32 val);
		status_t	ReplaceInt64(const char *name, int64 val);
		status_t	ReplaceInt64(const char *name, int32 index, int64 val);
		status_t	ReplaceBool(const char *name, bool a_bool);
		status_t	ReplaceBool(const char *name, int32 index, bool a_bool);
		status_t	ReplaceFloat(const char *name, float a_float);
		status_t	ReplaceFloat(const char *name, int32 index, float a_float);
		status_t	ReplaceDouble(const char *name, double a_double);
		status_t	ReplaceDouble(	const char *name,
									int32 index,
									double a_double);
		status_t	ReplacePointer(const char *name, const void *ptr);
		status_t	ReplacePointer(const char *name,
									int32 index,
									const void *ptr);
		status_t	ReplaceMessenger(const char *name, BMessenger messenger);
		status_t	ReplaceMessenger(	const char *name,
										int32 index,
										BMessenger messenger);
		status_t	ReplaceRef(	const char *name,
								const entry_ref *ref);
		status_t	ReplaceRef(	const char *name,
								int32 index,
								const entry_ref *ref);
		status_t	ReplaceMessage(const char *name, const BMessage *msg);
		status_t	ReplaceMessage(const char *name,
									int32 index,
									const BMessage *msg);
		status_t	ReplaceFlat(const char *name, BFlattenable *obj);
		status_t	ReplaceFlat(const char *name,
								int32 index,
								BFlattenable *obj);
		status_t	ReplaceData(const char *name,
								type_code type,
								const void *data,
								ssize_t data_size);
		status_t	ReplaceData(const char *name,
								type_code type,
								int32 index,
								const void *data,
								ssize_t data_size);

		status_t	GetInfo(type_code typeRequested,
							int32 which,
							char **name,
							type_code *typeReturned,
							int32 *count = NULL) const;

		status_t	GetInfo(const char *name,
							type_code *type,
							int32 *c = 0) const;
		status_t	RemoveData(const char *name, int32 index = 0);
		status_t	RemoveName(const char *name);

		int32		CountNames(type_code type) const;
		status_t	MakeEmpty();
		bool		IsEmpty() const;

		bool		WasDelivered() const;
		bool		IsSourceWaiting() const;
		bool		IsSourceRemote() const;
		BMessenger	ReturnAddress() const;
		bool		IsReply() const;
		const BMessage	*Previous() const;

		bool		WasDropped() const;
		BPoint		DropPoint(BPoint *offset = NULL) const;

		status_t	SendReply(uint32 command, BHandler *reply_to = NULL);
		status_t	SendReply(	BMessage *the_reply,
								BHandler *reply_to = NULL,
								bigtime_t timeout = B_INFINITE_TIMEOUT);
	
		status_t	SendReply(uint32 command, BMessage *reply_to_reply);
		status_t	SendReply(	BMessage *the_reply,
								BMessage *reply_to_reply,
								bigtime_t send_timeout = B_INFINITE_TIMEOUT,
								bigtime_t reply_timeout = B_INFINITE_TIMEOUT);
	
		bool		HasRect(const char *name, int32 index = 0) const;
		bool		HasPoint(const char *name, int32 index = 0) const;
		bool		HasString(const char *name, int32 index = 0) const;
		bool		HasInt8(const char *name, int32 index = 0) const;
		bool		HasInt16(const char *name, int32 index = 0) const;
		bool		HasInt32(const char *name, int32 index = 0) const;
		bool		HasInt64(const char *name, int32 index = 0) const;
		bool		HasBool(const char *name, int32 index = 0) const;
		bool		HasFloat(const char *name, int32 index = 0) const;
		bool		HasDouble(const char *name, int32 index = 0) const;
		bool		HasPointer(const char *name, int32 index = 0) const;
		bool		HasMessenger(const char *name, int32 index = 0) const;
		bool		HasRef(const char *name, int32 index = 0) const;
		bool		HasMessage(const char *name, int32 index = 0) const;
		bool		HasFlat(const char *name, const BFlattenable *obj) const;
		bool		HasFlat(const char *name,
							int32 index,
							const BFlattenable *obj) const;
		bool		HasData(const char *name, type_code type, int32 index = 0) const;

		ssize_t		FlattenedSize() const;
		status_t	Flatten(char *buffer, ssize_t size) const;
		status_t	Flatten(BDataIO *stream, ssize_t *size = NULL) const;
		status_t	Unflatten(const char *flat_buffer);
		status_t	Unflatten(BDataIO *stream);

		bool		IsSystem() const;
		void		PrintToStream() const;

		void		*operator new(size_t size);
		void		operator delete(void *ptr, size_t size);

//------------------------------------------------------------------------------
private:

friend class	BMessageQueue;
friend class	BMessenger;
friend class	BApplication;

// defined these few functions so that BApplication, BWindow, etc
// wouldn't have to be granted friendship. Those classes simply use
// these internal functions.

friend			void		_msg_cache_cleanup_();
friend			BMessage 	*_reconstruct_msg_(BMessage *);
friend inline	void		_set_message_target_(BMessage *, int32, bool);
friend inline	void		_set_message_reply_(BMessage *, BMessenger);
friend inline	int32		_get_message_target_(BMessage *);
friend inline	bool		_use_preferred_target_(BMessage *);

virtual	void		_ReservedMessage1();
virtual	void		_ReservedMessage2();
virtual	void		_ReservedMessage3();

		void		init_data();
		int32		flatten_hdr(uchar *result,
								ssize_t size,
								uchar flags) const;
		status_t	real_flatten(char *result,
								ssize_t size,
								uchar flags) const;
		status_t	real_flatten(BDataIO *stream,
								ssize_t size,
								uchar flags) const;
		char		*stack_flatten(char *stack_ptr,
									ssize_t stack_size,
									bool incl_reply,
									ssize_t *size = NULL) const;
		ssize_t		calc_size(uchar flags) const;
		ssize_t		calc_hdr_size(uchar flags) const;
		ssize_t		min_hdr_size() const;
		status_t	nfind_data(	const char *name,
								type_code type,
								int32 index,
								const void **data,
								ssize_t *data_size) const;
		status_t	copy_data(	const char *name,
								type_code type,
								int32 index,
								void *data,
								ssize_t data_size) const;

		status_t	_send_(port_id port,
							int32 token,
							bool preferred,
							bigtime_t timeout,
							bool reply_required,
							BMessenger &reply_to) const;
		status_t	send_message(port_id port,
								team_id port_owner,
								int32 token,
								bool preferred,
								BMessage *reply,
								bigtime_t send_timeout,
								bigtime_t reply_timeout) const;

		enum		{ sNumReplyPorts = 3 };
static	port_id		sReplyPorts[sNumReplyPorts];
static	long		sReplyPortInUse[sNumReplyPorts];
static	int32		sGetCachedReplyPort();

friend	int _init_message_();
friend	int _delete_message_();
static	BBlockCache	*sMsgCache;

		struct dyn_array {
			int32		fLogicalBytes;
			int32		fPhysicalBytes;
			int32		fChunkSize;		// In bytes. 0 for variable size entries
			int32		fCount;
			int32		fEntryHdrSize;	// size of entry_dr, incl padding
		//+	actual data follows here
		};

		struct entry_hdr  : public dyn_array {
			entry_hdr	*fNext;
			uint32		fType;
			uchar		fNameLength;	// strlen(fName)
			char		fName[1];
			// actual data follows the fName data. For entries with variable
			// size chunks, what follows will be an array of var_chunk
			// structures.
		};

		struct var_chunk {
			int32	fDataSize;				// sizeof(fData)
			char	fData[1];
		};

		void		*da_create(int32 header_size, int32 chunk_size,
								bool fixed, int32 nchunks);
		status_t	da_add_data(dyn_array **da, const void *data, int32 size);
		void		*da_find_data(dyn_array *da, int32 index,
									int32 *size = NULL) const;
		status_t	da_delete_data(dyn_array **pda, int32 index);
		status_t	da_replace_data(dyn_array **pda, int32 index,
									const void *data, int32 dsize);
		int32		da_calc_size(int32 hdr_size, int32 chunksize,
								bool is_fixed, int32 nchunks) const;
		void		*da_grow(dyn_array **pda, int32 increase);
		void		da_dump(dyn_array *da);

		int32		da_chunk_hdr_size() const
						{ return sizeof(int32); }
		int32		da_chunk_size(var_chunk *v) const
						{ return (v->fDataSize + da_chunk_hdr_size() + 7) & ~7; }
		var_chunk	*da_first_chunk(dyn_array *da) const
						{ return (var_chunk *) da_start_of_data(da); }
		var_chunk	*da_next_chunk(var_chunk *v) const
						{ return (var_chunk *) (((char*) v) + da_chunk_size(v)); }
		var_chunk	*da_chunk_ptr(void *data) const
						{ return (var_chunk*) (((char *) data) - da_chunk_hdr_size()); }

		int32		da_pad_8(int32 val) const
						{ return (val + 7) & ~7; }
		int32		da_total_size(dyn_array *da) const
						{ return sizeof(dyn_array) + da->fEntryHdrSize +
											da->fPhysicalBytes; }
		char		*da_start_of_data(dyn_array *da) const
						{ return ((char *) da) + (sizeof(dyn_array) +
											da->fEntryHdrSize); }
		bool		da_is_mini_data(dyn_array *da) const
						{ return ((da->fLogicalBytes <= UCHAR_MAX) &&
											(da->fCount <= UCHAR_MAX)); }

		BMessage			*link;
		int32				fTarget;			// token of the target
		BMessage			*fOriginal;
		uint32				fChangeCount;
		int32				fCurSpecifier;		// index (0-based)
		uint32				_reserved[4];

		BMessage::entry_hdr	*fEntries;

		struct {
			port_id				port;
			int32				target;
			team_id				team;
			bool				preferred;
		} fReplyTo;

		bool				fPreferred;
		bool				fReplyRequired;
		bool				fReplyDone;
		bool				fIsReply;
		bool				fWasDelivered;
		bool				fReadOnly;
		bool				fHasSpecifiers;	
};


#endif

