//******************************************************************************
//
//	File:		Message.h
//
//	Copyright 1994-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_MESSAGE_H
#define	_MESSAGE_H

#ifndef _STDDEF_H
#include <stddef.h>
#endif

#ifndef _APP_DEFS_H
#include <AppDefs.h>
#endif
#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif
#ifndef	_OBJECT_H
#include <Object.h>
#endif
#ifndef	_RECT_H
#include <Rect.h>
#endif
#ifndef _OS_H
#include <OS.h>
#endif
#ifndef _LOCKER_H
#include <Locker.h>
#endif
#ifndef _MESSENGER_H
#include <Messenger.h>
#endif
#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif


//--------------------------------------------------------------------

struct	_data_;
struct	_entry_;
struct	_shared_msg_data_;
class	BBlockCache;
class	BMessenger;
class	BHandler;

//--------------------------------------------------------------------

extern "C" void		_msg_cache_cleanup_();

//--------------------------------------------------------------------

class BMessage : public BObject {

public:
		ulong		what;

					BMessage();
					BMessage(ulong what);
					BMessage(BMessage *a_message);
virtual				~BMessage();

		long		Error();

		long		AddRect(const char *name, BRect a_rect);
		long		AddPoint(const char *name, BPoint a_point);
		long		AddString(const char *name, const char *a_string);
		long		AddLong(const char *name, long a_long);
		long		AddBool(const char *name, bool a_boolean);
		long		AddFloat(const char *name, float a_float);
		long		AddDouble(const char *name, double a_double);
		long		AddRef(const char *name, record_ref a_ref);
		long		AddObject(const char *name, BObject *obj);
		long		AddMessenger(const char *name, BMessenger messenger);
		long		AddData(const char *name,
							ulong type,
							const void *data,
							long numBytes);

		BRect		FindRect(const char *name, long index = 0);
		BPoint		FindPoint(const char *name, long index = 0);
		const char	*FindString(const char *string_name, long index = 0);
		long		FindLong(const char *name, long index = 0);
		bool		FindBool(const char *name, long index = 0);
		float		FindFloat(const char *name, long index = 0);
		double		FindDouble(const char *name, long index = 0);
		record_ref	FindRef(const char *name, long index = 0);
		BObject		*FindObject(const char *name, long index = 0);
		BMessenger	FindMessenger(const char *name, long index = 0);
		void		*FindData(	const char *name,
								ulong type,
								long *numBytes);
		void		*FindData(	const char *name,
								ulong type,
								long index,
								long *numBytes);

		long		ReplaceRect(const char *name, BRect a_rect);
		long		ReplaceRect(const char *name, long index, BRect a_rect);
		long		ReplacePoint(const char *name, BPoint a_point);
		long		ReplacePoint(const char *name, long index, BPoint a_point);
		long		ReplaceString(const char *name, const char *a_string);
		long		ReplaceString(	const char *name,
									long index, 
									const char *a_string);
		long		ReplaceLong(const char *name, long a_long);
		long		ReplaceLong(const char *name, long index, long a_long);
		long		ReplaceBool(const char *name, bool a_bool);
		long		ReplaceBool(const char *name, long index, bool a_bool);
		long		ReplaceFloat(const char *name, float a_float);
		long		ReplaceFloat(const char *name, long index, float a_float);
		long		ReplaceDouble(const char *name, double a_double);
		long		ReplaceDouble(	const char *name,
									long index,
									double a_double);
		long		ReplaceRef(const char *name, record_ref a_ref);
		long		ReplaceRef(const char *name, long index, record_ref a_ref);
		long		ReplaceObject(const char *name, BObject *obj);
		long		ReplaceObject(const char *name, long index, BObject *obj);
		long		ReplaceMessenger(const char *name, BMessenger messenger);
		long		ReplaceMessenger(	const char *name,
										long index,
										BMessenger messenger);
		long		ReplaceData(const char *name,
								ulong type,
								void *data,
								long data_size);
		long		ReplaceData(const char *name,
								ulong type,
								long index,
								void *data,
								long data_size);

		bool		GetInfo(ulong typeRequested,
							long which,
							char **name,
							ulong *typeReturned,
							long *count = NIL);

		bool		GetInfo(const char *name, ulong *type, long *count = 0);

		bool		RemoveName(const char *name);
		long		MakeEmpty();
		bool		IsEmpty();

		bool		WasSent();
		bool		IsSourceWaiting();
		bool		IsSourceRemote();
		BMessenger	ReturnAddress();
		bool		IsReply();
		BMessage	*Previous();

		bool		WasDropped();
		BPoint		DropPoint(BPoint *offset = NULL);

		long		SendReply(BMessage *the_reply, BHandler *reply_to = NULL);
		long		SendReply(ulong command, BHandler *reply_to = NULL);
	
		long		SendReply(BMessage *the_reply, BMessage **reply_to_reply);
		long		SendReply(ulong command, BMessage **reply_to_reply);
	
		bool		HasRect(const char *name, long index = 0);
		bool		HasPoint(const char *name, long index = 0);
		bool		HasString(const char *name, long index = 0);
		bool		HasLong(const char *name, long index = 0);
		bool		HasBool(const char *name, long index = 0);
		bool		HasFloat(const char *name, long index = 0);
		bool		HasDouble(const char *name, long index = 0);
		bool		HasRef(const char *name, long index = 0);
		bool		HasObject(const char *name, long index = 0);
		bool		HasMessenger(const char *name, long index = 0);
		bool		HasData(const char *name, ulong type, long index = 0);
		
		long		CountNames(ulong type);
		void		Unflatten(const char *flat_buffer);
		void		Flatten(char **result, long *size);
		bool		IsSystem();
		void		PrintToStream() const;

		void		*operator new(size_t size);
		void		operator delete(void *ptr, size_t size);

//------------------------------------------------------------------------------
private:

friend class	BMessageQueue;
friend class	BMessenger;
friend class	BRecord;
friend void		_msg_cache_cleanup_();

// defined these few functions so that BApplication, BWindow, etc
// wouldn't have to be granted friendship. Those classes simply use
// these internal functions.

friend BMessage *_get_msg_from_port_(port_id, long *);
friend BMessage *_msg_from_data_(void *);
friend BMessage *_reconstruct_msg_(BMessage *);
friend inline void		_set_message_target_(BMessage *, long);
friend inline void		_set_message_reply_(BMessage *, BMessenger);
friend inline long		_get_message_target_(BMessage *);

					BMessage(ulong what, _shared_msg_data_ *shared);
		void		init_shared_data();
		void		delete_data();
		long		calc_size();
		long		find_data(	const char *name,
								char **data,
								ulong type,
								long index=0,
								ulong *found_type = NULL);
		long		_send_(port_id port, long token, long code);
		long		send_message(port_id port, long token, BMessage **reply);
		BMessage	*shallow_clone();
		BMessage	*make_ref();
		long		get_ref();
		void		change_ref(long v);
		void		delete_data_array(_data_ *p);

static	BBlockCache	*sMsgCache;
static	BBlockCache	*sSharedCache;

		BMessage			*link;
		_shared_msg_data_	*shared;
		long				target;		// token of the target
		long				error;
		bool				posted;
		BMessage			*original;
};


#endif

