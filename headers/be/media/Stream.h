/******************************************************************************

	File:	Stream.h

	Copyright 1995-96, Be Incorporated

******************************************************************************/

#ifndef _STREAM_H
#define _STREAM_H

#ifndef _STDLIB
#include <stdlib.h>
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



/* ================
   Per-subscriber information.
   ================ */

struct _sbuf_info;

typedef struct _sub_info {
  struct _sub_info	*fNext;		/* next subscriber in the stream*/
  struct _sub_info	*fPrev;		/* previous subscriber in the stream */
  struct _sbuf_info	*fRel;		/* next buf to be released */
  struct _sbuf_info	*fAcq;		/* next buf to be acquired */
  sem_id			fSem;		/* semaphore used for blocking */
  long				fTotalTime;	/* accumulated time between acq/rel */
  long				fHeld;		/* # of buffers acq'd but not yet rel'd */
  bool				fIsBlocked;	/* TRUE if sub is sitting in acquire_sem */
} *subscriber_id;


/* ================
   Per-buffer information
   ================ */

typedef struct _sbuf_info {
  struct _sbuf_info	*fNext;		/* next "newer" buffer in the chain */
  subscriber_id		fAvailTo;	/* next subscriber to acquire this buffer */
  subscriber_id		fHeldBy;	/* subscriber that's acquired this buffer */
  long				fAcqTime;	/* time at which this buffer was acquired */
  area_id			fAreaID;	/* for system memory allocation calls */
  char				*fAddress;
  long				fSize;
  bool				fIsFinal;	/* TRUE => stream is stopping */
} *buffer_id;


/* ================
   Interface definition for BStream class
   ================ */

/* We've chosen B_MAX_SUBSCRIBER_COUNT and B_MAX_BUFFER_COUNT to be just
 * small enough so that a BStream structure fits in one 4096 byte page.
 */
#define	B_MAX_SUBSCRIBER_COUNT	62
#define	B_MAX_BUFFER_COUNT		62

#define B_BUFFER_STREAM_BASE_ADDRESS	((const char*) 0x26000000)



class BStream : public BObject {

	B_DECLARE_CLASS_INFO(BObject);

public:

						BStream();
		virtual			~BStream();
				
/* BStreams are allocated on shared memory pages */
		void			*operator new(size_t size);
		void			operator delete(void *stream, size_t size);

/* Create or delete a subscriber id for subsequent operations */
		long			Subscribe(char *name, 
								  subscriber_id clique,
								  subscriber_id *subID,
								  thread_id threadID=NULL);
		long			Unsubscribe(subscriber_id subID, 
									thread_id threadID=NULL);

/* Enter into or quit the stream */
		long			EnterStream(subscriber_id subID, 
									subscriber_id neighbor,
									bool before, 
									thread_id threadID=NULL);
		long			ExitStream(subscriber_id subID, 
								   thread_id threadID=NULL);

/* queries about a subscriber */
		bool			IsSubscribed(subscriber_id subID, 
									 thread_id threadID=NULL);
		bool			IsEntered(subscriber_id subID,
								  thread_id threadID=NULL);
		long			SubscriberName(subscriber_id subID, char *name);

/* Force an error return of a subscriber if it's blocked */
		long			UnblockSubscriber(subscriber_id subID,
										  thread_id threadID=NULL);

/* Acquire and release a buffer */
		long			AcquireBuffer(subscriber_id subID, 
									  buffer_id *bufID,
									  long timeout, 
									  thread_id threadID=NULL);
		long			ReleaseBuffer(subscriber_id subID, 
									  thread_id threadID=NULL);

/* Get the attributes of a particular buffer */
		char			*BufferData(buffer_id bufID);
		long			BufferSize(buffer_id bufID);
		bool			IsFinalBuffer(buffer_id bufID);

/* Get attributes of a particular subscriber */
		long			CountBuffersHeld(subscriber_id subID, 
										 thread_id threadID=NULL);

/* Queries for the BStream */
		long			CountSubscribers();
		long			CountEnteredSubscribers();
		subscriber_id	Clique();

		subscriber_id	FirstSubscriber();
		subscriber_id	LastSubscriber();
		subscriber_id	NextSubscriber(subscriber_id subID, 
									   thread_id threadID=NULL);
		subscriber_id	PrevSubscriber(subscriber_id subID, 
									   thread_id threadID=NULL);

/* debugging aids */
		void			PrintStream(thread_id threadID=NULL);
		void			PrintBuffers(thread_id threadID=NULL);
		void			PrintSubscribers(thread_id threadID=NULL);
#if 0
		void			ConsistencyCheck(thread_id threadID=NULL);
#endif


/* ================
   Private member functions that require locking
   ================ */

private:

friend class BStreamController;

/* introduce a new buffer into the "newest" end of the chain */
		long			AddBuffer(buffer_id bufID, thread_id threadID=NULL);

/* remove a buffer from the "oldest" end of the chain */
		buffer_id		RemoveBuffer(bool force, thread_id threadID=NULL);

/* allocate a buffer from shared memory and create a bufID for it. */
		buffer_id		CreateBuffer(long size, 
									 bool isFinal,
									 thread_id threadID=NULL);

/* deallocate a buffer and returns its bufID to the freelist */
		void			DestroyBuffer(buffer_id bufID,
									  thread_id threadID=NULL);

/* remove and destroy any "newest" buffers from the head of the chain
 * that have not yet been claimed by any subscribers.  If there are
 * no subscribers, this clears the entire chain.
 */
		void			RescindBuffers(thread_id threadID=NULL);

/* ================
   Private member functions that assume locking already has been done.
   ================ */

/* gaining exclusive access to the BStream */
		void 			Lock(thread_id threadID);
		void			Unlock();

/* initialize the free list of subscribers */
		void			InitSubscribers();

/* return TRUE if subID appears valid */
		bool			IsSubscribedSafe(subscriber_id subID);

/* return TRUE if subID is entered into the stream */
		bool			IsEnteredSafe(subscriber_id subID);

/* initialize the free list of buffer IDs */
		void			InitBuffers();

/* Give subID all the buffers it can get */
		void			InheritBuffers(subscriber_id subID);

/* Relinquish any buffers held by subID */
		void			BequeathBuffers(subscriber_id subID);

/* Fast version of ReleaseBuffer() */
		long			ReleaseBufferSafe(subscriber_id subID);

/* Release a buffer to a subscriber */
		long			ReleaseBufferTo(buffer_id bufID, subscriber_id subID);

/* deallocate all buffers */
		void			FreeAllBuffers();

/* deallocate all subscribers */
		void			FreeAllSubscribers();

/* ================
   Private data members
   ================ */

		sem_id				fLock;
		long				fLockOwner;
		long				fLockOwnerCount;

		long				fAreaID;		/* area id for this BStream */

		/* ================
		   subscribers
		   ================ */

		struct _sub_info	*fFreeSubs;		/* free list of subscribers */
		struct _sub_info	*fFirstSub;		/* first entered in itinierary */
		struct _sub_info	*fLastSub;		/* last entered in itinerary */

		subscriber_id		fClique; 		/* current "owner" of the stream */
		long				fSubCount;
		long				fEnteredSubCount;

		struct _sub_info	fSubscribers[B_MAX_SUBSCRIBER_COUNT];

		/* ================
		   buffers
		   ================ */

		struct _sbuf_info	*fFreeBuffers;
		struct _sbuf_info	*fOldestBuffer;	/* first in line */
		struct _sbuf_info	*fNewestBuffer;	/* fNewest->fNext = NULL */
		long				fCountBuffers;

		struct _sbuf_info	fBuffers[B_MAX_BUFFER_COUNT];
};

#endif 	// #ifdef _STREAM_H
