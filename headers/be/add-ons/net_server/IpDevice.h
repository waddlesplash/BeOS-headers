/*
 * IpDevice.h
 * Copyright (c) 1997 Be, Inc.	All Rights Reserved 
 *
 */
#pragma once
#ifndef _IP_DEVICE_H
#define _IP_DEVICE_H

#include <NetProtocol.h>

class BIpHandler;

class BIpDevice {
public:
	virtual status_t SendPacket(uint32 dst, BNetPacket *buf) = 0;
	virtual unsigned Flags(void) = 0;
	virtual unsigned MaxPacketSize(void) = 0;
	virtual BNetPacket *AllocPacket(void) = 0;
	virtual void Run(BIpHandler *ip) = 0;
	virtual void Close(void) = 0;
	virtual void Statistics(FILE *f) = 0;
	virtual ~BIpDevice(void);
};

class BIpHandler {
public:
	virtual void PacketReceived(BNetPacket *buf, BIpDevice *dev) = 0;
	virtual uint32 Address(void) = 0;
	virtual void SetAddress(uint32 address) = 0;
	virtual uint32 NetMask(void) = 0;
};


#endif /* _IP_DEVICE_H */


