//******************************************************************************
//
//	File:		E-mail.h
//
//	Description:	Mail class
//
//	Copyright 1996, Be Incorporated
//
//******************************************************************************

#ifndef _E_MAIL_H
#define _E_MAIL_H

#ifndef _OBJECT_H
#include <Object.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

#ifndef _MESSAGE_H
#include <Message.h>
#endif

#ifndef _LIST_H
#include <List.h>
#endif

#ifndef _RECORD_H
#include <Record.h>
#endif


// -----------------------------------------------------------------------
// 'E-Mail' database table definition...

/*		The 'E-Mail' table descends from 'BrowserItem'

	StringField("Status", B_INDEXED_FIELD);	"New", "Read", "Pending" or "Sent"
	LongField("Priority");		from "Priority: " field of header
	StringField("From");		from "From: " field of header
	StringField("Subject");		from "Subject: " field of header
	StringField("Reply");		from "Reply-to: " field of header
	TimeField("When");			from "Date: " field of header
	LongField("Enclosures");	number of enclosures
	RawField("header");			unmolested header of message
	RawField("content");		unmolested content of message
	RecordIDField("content_file");record id for large message content (>20K)
	RawField("enclosures");		mime enclosure list	<see below>
	LongField("mail_flags");	mail record flags	<see below>
*/

/* mime enclosures list...
	record_ref	ref;			record and database of enclosure
	char		mime_type[];	MIME type string (NULL-terminated)
	char		mime_subtype[];	MIME subtype string (NULL-terminated)
*/

/* mail record flags */
enum	B_MAIL_FLAGS		{B_MAIL_PENDING	= 1,	// waiting to be sent
							 B_MAIL_SENT	= 2,	// has been sent
							 B_MAIL_SAVE	= 4};	// save mail after sending

#define	B_MAIL_TYPE			'mail'


// -----------------------------------------------------------------------
// defines...

/* status values */
#define B_MAIL_NOT_QUEUED	0
#define B_MAIL_QUEUED		1

/* schedule days */
#define B_CHECK_NEVER		0
#define B_CHECK_WEEKDAYS	1
#define B_CHECK_DAILY		2

/* max. lengths */
#define B_MAX_USER_NAME_LENGTH	32
#define B_MAX_HOST_NAME_LENGTH	64

#define B_MAIL_TO			"To: "
#define B_MAIL_CC			"Cc: "
#define B_MAIL_BCC			"Bcc: "
#define B_MAIL_FROM			"From: "
#define B_MAIL_DATE			"Date: "
#define B_MAIL_REPLY		"Reply-To: "
#define B_MAIL_SUBJECT		"Subject: "
#define B_MAIL_PRIORITY		"Priority: "
#define B_MAIL_CONTENT		"Content"


// -----------------------------------------------------------------------
// structs...

typedef struct
	{
		char		pop_name[B_MAX_USER_NAME_LENGTH];
		char		pop_password[B_MAX_USER_NAME_LENGTH];
		char		pop_host[B_MAX_HOST_NAME_LENGTH];
		char		smtp_host[B_MAX_HOST_NAME_LENGTH];
	} mail_account;

typedef struct
	{
		long		days;			// see flags above
		long		interval;		// in seconds
		long		start_time;		// in seconds
		long		end_time;		// in seconds
	} mail_schedule;

typedef struct
	{
		bool		alert;
		bool		beep;
	} mail_notification;


// -----------------------------------------------------------------------
// global functions...

long	get_mail_account(mail_account*);
long	set_mail_account(mail_account*, bool save = TRUE);
long	get_mail_schedule(mail_schedule*);
long	set_mail_schedule(mail_schedule*, bool save = TRUE);
long	get_mail_notification(mail_notification*);
long	set_mail_notification(mail_notification*, bool save = TRUE);
long	get_mail_reader(ulong*);
long	set_mail_reader(ulong, bool save = TRUE);
long	check_for_mail(long *incoming_count = NULL);
long	forward_mail(BRecord*, char* recipients, bool reset_sender = TRUE,
												 bool queue = TRUE);


// -----------------------------------------------------------------------
// class...

class BMailMessage : public BObject {

public:
					BMailMessage();
					BMailMessage(BMailMessage*);
					BMailMessage(BRecord*);
					~BMailMessage();

		long		Send(bool queue = TRUE, bool save_message = TRUE);
		long		Error();
		long		Status();
		record_ref	Ref();


		void		SetField(char *field_name, void *data, long length,
														bool append = FALSE);
		long		CountFields(char *name = NIL);
		long		GetFieldName(char **field_name, long index);
		long		FindField(char *field_name, void **data, long *length,
														long index = 0);
		long		RemoveField(char *field_name, long index = 0);


		void		SetEnclosure(record_ref*, const char *mime_type,
											  const char *mime_subtype);
		long		CountEnclosures();
		long		GetEnclosure(record_ref**, char **mime_type,
											   char **mime_subtype,
											   long index = 0);
		long		RemoveEnclosure(record_ref*);

// -----------------------------------------------------------------------

private:
		long		fError;
		long		fStatus;
		BList*		fEnclosures;
		BList*		fFields;
		record_ref	fRef;

		void		empty_list(BList*);
		BList*		find_field(char*);
		void		init();
};


#endif /* _MAIL_H */
