/******************************************************************************

	File:	StreamController.h

	Copyright 1995-96, Be Incorporated

******************************************************************************/

#ifndef _STREAM_CONTROLLER_H
#define _STREAM_CONTROLLER_H

#ifndef _STREAM_H
#include <Stream.h>
#endif

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _OBJECT_H
#include <Object.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

#ifndef _LOCKER_H
#include <Locker.h>
#endif


/* ================
   Local Declarations
   ================ */

#define B_DEFAULT_BSTREAM_COUNT			3
#define	B_DEFAULT_BSTREAM_SIZE			B_PAGE_SIZE
#define B_DEFAULT_BSTREAM_DELAY			10000
#define	B_DEFAULT_BSTREAM_TIMEOUT		5000000


enum stream_state {
  B_IDLE = 100,		/* stream is shut down */
  B_RUNNING,		/* stream is running */
  B_STOPPING		/* waiting for final buffer to return */
  };


/* ================
   Class definition for BStreamController
   ================ */


class BStreamController : public BObject {


public:

					BStreamController();
	virtual			~BStreamController();


	BStream			*Stream();

	long			CountBuffers() const;
	void			SetBufferCount(long count);

	long			BufferSize() const;
	void			SetBufferSize(long bytes);

  /* Get or set the minimum delay between sending out successive buffers.
   * Although the StreamController automatically shuts down when there
   * are no more subscribers, setting the minumum delay can prevent
   * prevent runaway streams.  A zero or negative value means no 
   * delay.
   */
	double			BufferDelay() const;
	void			SetBufferDelay(double usecs);

  /* If no Buffers return to the StreamController within a period of time, the
   * StreamController will decide that one of the subscribers is broken and
   * will go hunting for it.  When it finds the offending subscriber,
   * it will be removed from the chain with impunity.
   *
   * The default is B_DEFAULT_TIMEOUT.  Setting the timeout to 0 or a 
   * negative number will disable this.
   */
	double			Timeout() const;
	void			SetTimeout(double usecs);

  /****************************************************************
   * Control the running of the stream.
   *
   */

  /* Set the pending state to B_RUNNING and, if required, start up
   * the processing thread.  The processing thread will start
   * emitting buffers to the stream.
   */
	stream_state	Start();

  /* Set the pending state to B_STOPPING.  The processing thread will
   * stop emitting new buffers to the stream, and when all buffers
   * are accounted for, will automatically set the desired state
   * to B_IDLE.
   */
	stream_state	Stop();

  /* Set the desired state to B_IDLE.  The processing thread will
   * stop immediately and all buffers will be "reclaimed" back 
   * to the StreamController.
   */
	stream_state	Abort();
  
  /* Return the current state of the stream (B_RUNNING, B_STOPPING, or B_IDLE).
   */
	stream_state	State() const;

  /* When NotificationPort is set, the receiver will get a message
   * whenever the state of the StreamController changes.  The msg_id of the 
   * message will be the new state of the StreamController.
   */
	port_id			NotificationPort() const;
	void			SetNotificationPort(port_id port);

  /* Lock the data structures associated with this StreamController
   */
	bool			Lock();
	void			Unlock();

  /****************************************************************
   * Controlling the suscriber list.
   */

	long			Subscribe(char *name, 
							  subscriber_id clique, 
							  subscriber_id *subID,
							  sem_id semID);
	long			Unsubscribe(subscriber_id subID);
  	bool			IsSubscribed(subscriber_id subID);

	long			EnterStream(subscriber_id subID, 
								subscriber_id neighbor,
								bool before);
	long			ExitStream(subscriber_id subID);
  	bool			IsEntered(subscriber_id subID);

	long			SubscriberName(subscriber_id subID, char *name);
	long			CountSubscribers();
	long			CountEnteredSubscribers();
  	subscriber_id	Clique();


/* ================
   Private member functions.
   ================ */

private:

	friend class BStreamer;

  /****************************************************************
   * 
   * The processing thread.  This thread waits to acquire a Buffer
   * (or for the timeout to expire) and takes appropriate action.
   */
	void			StartProcessing();
	void			StopProcessing();
	static long		_ProcessingThread(void *arg);
	void			ProcessingThread();

  /* Set the state of the stream.  If newState is the same as the
   * current state, this is a no-op.  Otherwise, this method will
   * notify anyone listening on the notification port about the
   * changed state and will send a StateChange buffer through the
   * stream.
   */
	void			SetState(stream_state newState);

  /* Snooze until the desired time arrives.  Returns the 
   * current time upon returning.
   */
	double			SnoozeUntil(double sys_time);

  /****************************************************************
   *
   * Private fields.
   *
   */

  BStream		*fStream;			/* a BStream object */
  stream_state	fState;				/* running, stopping, etc. */

  long			fCountBuffers;		/* desired # of buffers */
  long			fBufferSize;		/* desired size of each buffer */
  double		fBufferDelay;		/* minimum time between sends */
  double		fTimeout;			/* watchdog timer */

  port_id		fNotifyPort;		/* when set, send change of state msgs */
  thread_id		fProcessingThread;	/* thread to dispatch buffers */
  subscriber_id	fControllerID;		/* StreamController's subID in fStream */

  BLocker		fLock;
};

#endif			// #ifdef _STREAM_CONTROLLER_H
