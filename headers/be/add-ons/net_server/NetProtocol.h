/*
 * NetProtocol.h
 * Copyright (c) 1997 Be, Inc.	All Rights Reserved 
 *
 */
#ifndef _NET_PROTOCOL_H
#define _NET_PROTOCOL_H

#include <NetDevice.h>

class BPacketHandler {
public:
	virtual bool PacketReceived(BNetPacket *buf, BNetDevice *dev) = 0;
};

class BNetProtocol {
public:
	virtual void AddDevice(BNetDevice *dev, const char *name) = 0;
	virtual ~BNetProtocol(void);
};

void register_packet_handler(
							 BPacketHandler *handler,
							 BNetDevice *dev,
							 int priority = 0);

void unregister_packet_handler(
							   BPacketHandler *handler,
							   BNetDevice *dev
							   );
#endif /* _NET_PROTOCOL_H */


