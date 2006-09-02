// TCPMessenger
// This isn't really a BMessenger, but it looks a lot like one.  Its target is a TCPLooper
// at the given TCP address

#ifndef TCPMessenger_H
#define TCPMessenger_H 1

#include <netinet/in.h>

#include <remotemessage/RemoteMessenger.h>
#include <String.h>

class BMessage;

class TCPMessenger : public BRemoteMessenger
{
public:
					TCPMessenger(const char* hostname, uint16 port);
					TCPMessenger(const struct sockaddr_in& targetAddress);
					~TCPMessenger();

					TCPMessenger(const TCPMessenger& other);
					TCPMessenger& operator=(const TCPMessenger& rhs);

					bool IsValid() const;

					status_t SendMessage(uint32 command) const;
					status_t SendMessage(const BMessage& msg) const;
	
	virtual	const	BString	Target() const;

private:
	struct		sockaddr_in fTargetSock;		// target address
	bool					fIsValid;
	BString					fTarget;
};

// TCPM protocol header
	// header:
	//		- transaction number, identical for all packets in this transmission, selected by originator
	//		- total number of packets in message
	//		- sequence number of this packet [0 based]
	//		- total payload size of message
	//		- payload size of this packet
	//		- padding to 32 byte header size
	// data:
	//		- payload bytes, not more than TCPM_MAX_PAYLOAD bytes

struct TCPMessageHeader
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
