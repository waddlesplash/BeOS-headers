//******************************************************************************
//
//	File:		Message.h
//
//	Copyright 1994, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_MESSAGE_H
#define	_MESSAGE_H

#ifndef _APP_DEFS_H
#include <app/AppDefs.h>
#endif
#ifndef	_OBJECT_H
#include <support/Object.h>
#endif
#ifndef	_RECT_H
#include <interface/Rect.h>
#endif
#ifndef _OS_H
#include <os/OS.h>
#endif
#ifndef _CLASS_INFO_H
#include <support/ClassInfo.h>
#endif


//--------------------------------------------------------------------

class	_data_;
class	_entry_;
class	_shared_;

//--------------------------------------------------------------------

class BMessage {
	DECLARE_ROOT_CLASS_INFO();

public:
		ulong	what;

				BMessage();
				BMessage(ulong what);
//				BMessage(ulong pwhat, long ptarget);
				BMessage(BMessage *a_message);
virtual			~BMessage();

		long	Error();
		void	AddData(const char *name,
						ulong type,
						const void *data,
						long numBytes);
		void	AddRect(const char *name, BRect a_rect);
		void	AddPoint(const char *name, BPoint a_point);
		void	AddString(const char *name, const char *a_string);
		void	AddLong(const char *name, long a_long);
		void	AddBool(const char *name, bool a_boolean);
		void	AddFloat(const char *name, float a_float);

		BPoint	FindPoint(const char *name, long index = 0);
		BRect	FindRect(const char *name, long index = 0);
		long	FindLong(const char *name, long index = 0);
		float	FindFloat(const char *name, long index = 0);
		char	*FindString(const char *string_name, long index = 0);
		bool	FindBool(const char *name, long index = 0);
		
		void	*FindData(	const char *name,
							ulong type,
							long *numBytes);
		void	*FindData(	const char *name,
							ulong type,
							long index,
							long *numBytes);

		void	ReplaceLong(const char *name, long a_long);
		void	ReplaceLong(const char *name, long index, long a_long);
		void	ReplacePoint(const char *name, BPoint a_point);
		void	ReplacePoint(const char *name, long index, BPoint a_point);
		void	ReplaceRect(const char *name, BRect a_rect);
		void	ReplaceRect(const char *name, long index, BRect a_rect);
		void	ReplaceFloat(const char *name, float a_float);
		void	ReplaceFloat(const char *name, long index, float a_float);
		void	ReplaceString(const char *name, const char *a_string);
		void	ReplaceString(const char *name, long index, const char *a_string);
		void	ReplaceBool(const char *name, bool a_bool);
		void	ReplaceBool(const char *name, long index, bool a_bool);
		
		void	ReplaceData(const char *name,
							ulong type,
							void *data,
							long data_size);
		void	ReplaceData(const char *name,
							ulong type,
							long index,
							void *data,
							long data_size);

		bool	GetInfo(ulong typeRequested,
						long which,
						char **name,
						ulong *typeReturned,
						long *count = NIL);

		bool	GetInfo(const char *name, ulong *type, long *count = 0);

		void	SendReply(BMessage *the_reply);

		bool	HasData(const char *name, ulong type, long index = 0);
		bool	HasRect(const char *name, long index = 0);
		bool	HasPoint(const char *name, long index = 0);
		bool	HasString(const char *name, long index = 0);
		bool	HasLong(const char *name, long index = 0);
		bool	HasBool(const char *name, long index = 0);
		bool	HasFloat(const char *name, long index = 0);
		
		long	CountNames(ulong type);
		void	Unflatten(char *flat_buffer);
		void	Flatten(char **result, long *size);
		bool	IsEvent();
		void	PrintToStream() const;

//------------------------------------------------------------------------------
private:

friend class	BMessageQueue;
friend class	BMessenger;
friend class	BRecord;

// defined these few functions so that BApplication, BWindow, etc
// wouldn't have to be granted friendship. Those classes simply use
// these internal functions.
friend BMessage *_retrieve_message_(long *);
friend BMessage *_reconstruct_drag_msg_(BMessage *);
friend void		_set_message_target_(BMessage *, long);
friend long		_get_message_target_(BMessage *);

					BMessage(ulong what, _entry_ *entries, _shared_ *shared);
		void		init_shared_data();
		void		delete_data();
		long		calc_size();
		long		find_data(	const char *name,
								char **data,
								ulong type,
								long index=0,
								ulong *found_type = NULL);
		int			forward_message(long pid);
		int			send_message(long pid,
								BMessage **reply);
		int			send_message(long pid);
		int			send_reply(long pid);
		int			_send_(thread_id dest_pid, long code);
		BMessage	*shallow_clone();
		void		shallow_clone(BMessage *new_msg);
		BMessage	*make_ref();
		long		get_ref();
		void		change_ref(long v);

		BMessage	*link;
		_entry_		*entries;
		_shared_	*shared;
		long		target;		// token of the target
		thread_id	sender_pid;
		long		error;
		bool		posted;
};

#endif

