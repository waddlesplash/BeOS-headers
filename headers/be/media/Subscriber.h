
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

typedef bool	(*enter_stream_hook)(void *userData, char *buffer, long count);
typedef long	(*exit_stream_hook)(void *userData, long error);

/* ================
   Class definition for BSubscriber
   ================ */

class BSubscriber : public BObject {


public:
					BSubscriber(const char *name=NULL);
	virtual			~BSubscriber();

	/* return most recent error (including initialization time) */
	long			Error();


/* ================
   Gaining access to the Buffer Stream
   ================ */

	virtual long	Subscribe(long resource,
							  subscriber_id clique, 
							  bool willWait);
	virtual long	Unsubscribe(void);


	subscriber_id	Clique(void);
    subscriber_id	ID(void);
	const char 		*Name(void);

	void			SetTimeout(double microseconds);
	double			Timeout(void);

/* ================
   Streaming functions.
   ================ */

	virtual long	EnterStream(subscriber_id neighbor,
								bool before,
								void *userData,
								enter_stream_hook entryFunction,
								exit_stream_hook exitFunction,
								bool background);

	virtual long	ExitStream(bool synch=FALSE);

	bool			IsInStream(void);
/* Stream info */

	long			GetStreamParameters(long *bufferSize,
										long *bufferCount,
										bool *isRunning,
										long *subscriberCount,
										subscriber_id *clique);
	long			SetStreamBuffers(long bufferSize, long bufferCount);
	long			StartStreaming();
	long			StopStreaming();



/* ================
   Protected members (may be used by inherited classes)
   ================ */
protected:

	/* Get/Set the server */
	BMessenger		*Server();
	void			SetServer(BMessenger *server);

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

	/****************************************************************
	 * Private member variables
	 */
	char			*fName;			/* name given to constructor */
	BMessenger		*fServer; 		/* message pipe to server */
	BStream			*fStream;		/* buffer stream */

	long			fError;			/* for Error() member fn */
	subscriber_id	fID;		 	/* our subscriber_id */
	subscriber_id	fClique;
	sem_id			fSem;			/* stream semaphore */

	void			*fUserData;		/* arg to fStreamFn and fCompletionFn */
	enter_stream_hook	fStreamFn;		/* per-buffer user function */
	exit_stream_hook	fCompletionFn;	/* called after streaming stops */
	bool			fCallStreamFn;	/* true while we should call fStreamFn */
	double			fTimeout;		/* time out while awaiting buffers */
	sem_id			fSynchLock;
	thread_id		fBackThread;

  };

#endif	// #ifdef _SUBSCRIBER_H
