/*
 * NetPacket.h
 * Copyright (c) 1997 Be, Inc.	All Rights Reserved 
 *
 */
#pragma once
#ifndef _NET_PACKET_H
#define _NET_PACKET_H

#include <SupportDefs.h>

class BNetPacket {
	BNetPacket(void);
public:
	virtual unsigned Size(void) = 0;
	virtual void SetSize(unsigned size) = 0;
	virtual unsigned Base(void) = 0;		/* absolute position */
	virtual void SetBase(int offset) = 0;	/* relative to current base */
	virtual char *DataBlock(unsigned offset, unsigned *size) = 0;
	virtual ~BNetPacket(void) = 0;

	virtual void Read(unsigned offset, char *data, unsigned size);
	virtual void Write(unsigned offset, const char *data, unsigned size);

	
	/* obsolescent */
	char *Data(void)
	{
		char *data;
		unsigned size;
		unsigned retsize;

		size = Size();
		retsize = size;
		data = DataBlock(0, &retsize);
		if (retsize != size) {
			return (NULL);
		}
		return (data);
	}
};


class BStandardPacket : public BNetPacket {
public:
	void *operator new(size_t size);
	void operator delete(void *ptr);

	BStandardPacket(unsigned size = 0);
	~BStandardPacket(void);
	unsigned Size(void);
	void SetSize(unsigned size);
	unsigned Base(void);
	void SetBase(int offset);
	char *DataBlock(unsigned offset, unsigned *size);
private:
	char *store;
	unsigned size;
	unsigned maxsize;
	unsigned offset;
};

void
copy_packet(
		   BNetPacket *srcpacket,
		   unsigned srcoffset,
		   BNetPacket *dstpacket,
		   unsigned dstoffset,
		   unsigned size
		   );

class BTimeoutHandler {
public:
	virtual void TimedOut(uint32 receipt) = 0;
};

bool cancel_timeout(uint32 receipt);
uint32 set_timeout(BTimeoutHandler *handler, bigtime_t howlong);

#endif /* _NET_PACKET_H */


