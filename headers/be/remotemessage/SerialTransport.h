// -------------------------------------------------------------------------------
/* 
	SerialTransport
	 
	Copyright (c) 2001 Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			October 10, 2001 
 
	Allows sending and receiving messages over the Serial ports. 
*/ 
// -------------------------------------------------------------------------------

#ifndef SERIALTRANSPORT_H
#define SERIALTRANSPORT_H

#include <Locker.h>
#include <List.h>
#include <SerialPort.h>
#include <String.h>

class BMessage;
class BSerialLooper;
class BSerialMessenger;

class BSerialTransport
{
	protected:
												BSerialTransport();
												~BSerialTransport();


						status_t				SendMessage(const BMessage& Message);
			
						status_t				InitStatus() const	{ return fStatus; }
				const	BString					Port() const;

		static			BSerialTransport*		TransportForPort(const BString& Port);
		static			BSerialTransport*		AddSerialLooper(BSerialLooper* Looper, const BString& Port);
						void					RemoveSerialLooper(BSerialLooper* Looper);

						void					DetachMessage();

						void					DecrementRef();
						void					IncrementRef();

						void		MessageReceived(BMessage* Message);
						status_t	SetPort(const BString& PortName);
		
						status_t	StartListening();
						void		StopListening();
						bool		Listening() const	{ return fListening; }
		static			int32		Listener(void* Data);
	
	private:
						void		ReadMessage(uint32 size);
						void		ListenForInput();
						status_t	TransferData(const BMessage &Message);

	private:
			BSerialPort		fPort;
			BString			fPortName;
			BList			fLoopers;
			status_t		fStatus;
			bool			fListen;
			bool			fListening;
			bool			fDetachMessage;
			uint32			fRefrences;
		
	static	BList			sTransports;
	static	BLocker			sLock;	
	
	friend class BSerialMessenger;
	friend class BSerialLooper;
};

#endif

