
/******************************************************************************

	File:			Subscriber.h

	Description:	Support for communication with a buffer stream server

	Copyright 1995-96, Be Incorporated

******************************************************************************/


#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H

#ifndef _MEDIA_DEFS_H
#include <MediaDefs.h>
#endif

#ifndef _OBJECT_H
#include <Object.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

#ifndef _MESSENGER_H
#include <Messenger.h>
#endif

#ifndef _STREAM_H
#include <Stream.h>
#endif

/* ================
   declarations
   ================ */

typedef bool	(*StreamFn)(void *userData, char *buffer, long count);
typedef long	(*CompletionFn)(void *userData, long error);

/* ================
   Class definition for BSubscriber
   ================ */

class BSubscriber : public BObject {

	B_DECLARE_CLASS_INFO(BObject);

public:

					BSubscriber(char *name);
	virtual			~BSubscriber();

	/* return most recent error (including initialization time) */
	long			Error();

	/* Get/Set the server */
	BMessenger		*Server();
	void			SetServer(BMessenger *server);

/* ================
   Gaining access to the Buffer Stream
   ================ */

    subscriber_id	ID();

	long			Name(subscriber_id id, char *name);

	virtual long	Subscribe(long resource,
							  subscriber_id clique, 
							  bool willWait);

	virtual long	Unsubscribe(void);
							

	virtual long	CountSubscribers(void);
	subscriber_id	Clique(void);

	double			Timeout(void);
	void			SetTimeout(double microseconds);

	long			GetStreamParameters(long *bufferSize,
										long *bufferCount,
										bool *isRunning,
										long *subscriberCount,
										subscriber_id *clique);

	long			SetStreamBuffers(long bufferSize, long bufferCount);

	long			StartStreaming();
	long			StopStreaming();

/* ================
   Streaming functions.
   ================ */

	virtual long	EnterStream(subscriber_id neighbor,
								bool before,
								void *userData,
								StreamFn streamFunction,
								CompletionFn completionFunction,
								bool background);


	virtual long	ExitStream();


/* ================
   Protected members (may be used by inherited classes)
   ================ */
protected:

	/* send standard reply to server */
	long			SendRPC(BMessage *msg);

	/* set fError and return it */
	long			SetError(long error);

/* ================
   Private member functions.
   ================ */
private:

	static long		_ProcessLoop(void *arg);
	long			ProcessLoop();

	long			RequestEnter(subscriber_id neighbor, bool before);
	long			RequestExit();

	/* return a handle to the buffer stream associated with the server */
	long			FindStream(BStream **stream);

	/****************************************************************
	 * Private member variables
	 */
	char			*fName;			/* name given to constructor */
	BMessenger		*fServer; 		/* message pipe to server */
	BStream			*fStream;		/* buffer stream */
	long			fError;			/* for Error() member fn */
	subscriber_id	fID;		 	/* our subscriber_id */
	subscriber_id	fClique;

	void			*fUserData;		/* arg to fStreamFn and fCompletionFn */
	StreamFn		fStreamFn;		/* per-buffer user function */
	CompletionFn	fCompletionFn;	/* called after streaming stops */
	bool			fCallStreamFn;	/* true while we should call fStreamFn */
	long			fTimeout;		/* time out while awaiting buffers */
  };

#endif	// #ifdef _SUBSCRIBER_H
