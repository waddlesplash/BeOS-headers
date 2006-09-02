// UDPMessenger

#ifndef UDPMessenger_H
#define UDPMessenger_H 1

class BMessage;
#include <netinet/in.h>

#include <String.h>
#include <remotemessage/RemoteMessenger.h>

// This isn't really a BMessenger, but it looks a lot like one.  Its target is a UDPLooper
// at the given UDP address

class UDPMessenger : public BRemoteMessenger
{
public:


	UDPMessenger(const char* hostname, uint16 port);
	UDPMessenger(const struct sockaddr_in& targetAddress);
	~UDPMessenger();

	UDPMessenger(const UDPMessenger& other);
	UDPMessenger& operator=(const UDPMessenger& rhs);

	virtual		 	status_t	SendMessage(const BMessage& Message) const;
	virtual			bool		IsValid() const;
	virtual	const	BString		Target() const;

	status_t SendMessage(uint32 command) const;
	status_t SendMessage(const BMessage* msg) const;

private:
	struct sockaddr_in 	fTargetSock;		// target address
	bool 				fIsValid;
	BString 			fTarget;
};

// UDPM protocol header
	// header:
	//		- transaction number, identical for all packets in this transmission, selected by originator
	//		- total number of packets in message
	//		- sequence number of this packet [0 based]
	//		- total payload size of message
	//		- payload size of this packet
	//		- padding to 32 byte header size
	// data:
	//		- payload bytes, not more than UDPM_MAX_PAYLOAD bytes

struct UDPMessageHeader
{
	uint32 transaction_number;
	uint32 total_packets;		// at least 1; 0 indicates an ACK packet
	uint32 this_packet;			// in the range [0, total_packets)
	uint32 total_payload;
	uint32 this_payload;

	// reserve more space to bring the total size to 32 bytes; should be zeros for now
	uint32 reserved0;
	uint32 reserved1;
	uint32 reserved2;
};

#endif
