/*
 * NetDevice.h
 * Copyright (c) 1997 Be, Inc.	All Rights Reserved 
 *
 */
#pragma once
#ifndef _NET_DEVICE_H
#define _NET_DEVICE_H

#include <NetPacket.h>
#include <net_settings.h>
#include <stdio.h>

/*
 * Standard SNMP types here
 */
typedef enum {
	B_NULL_NET_DEVICE = 0x00,   /* not a real device */
	B_ETHER_NET_DEVICE = 0x06,
	B_PPP_NET_DEVICE = 0x17,
	B_LOOP_NET_DEVICE = 0x18
} net_device_type;

enum {
	B_FLAGS_POINT_TO_POINT = 0x01
};


class BCallbackHandler {
public:
	virtual void Done(status_t status) = 0;
};

class BNetConfig {
public:
	virtual bool IsIpDevice(void) = 0;

	/*
	 * Configure the device
	 */
	virtual status_t Config(const char *ifname,
							net_settings *ncw,
							BCallbackHandler *callback,
							bool autoconfig = FALSE) = 0;

	/*
	 * Get a pretty name for this device
	 */
	virtual int GetPrettyName(char *name, int len) = 0;

	virtual ~BNetConfig(void);
};


class BIpDevice;

/*
 * A dumb network device that just sends and receives
 * packets.  The caller of this device must know the type
 * of the media to use it (Ethernet, PPP, etc).
 */
class BNetDevice {
public:
	virtual BNetPacket *ReceivePacket(void) = 0;
	virtual BNetPacket *AllocPacket(void) = 0;
	virtual void SendPacket(BNetPacket *packet) = 0;
	virtual void Address(char *address) = 0;
	
	virtual status_t AddMulticastAddress(const char *address) = 0;
	virtual status_t RemoveMulticastAddress(const char *address) = 0;
	virtual status_t SetPromiscuous(bool yes) = 0;
	virtual unsigned MaxPacketSize(void) = 0;
	virtual net_device_type Type(void) = 0;

	/*
	 * Closes all resources
	 */
	virtual void Close(void) = 0;

	/*
	 * Open the IP device associated with this dev.
	 * Ethernet devices should return NULL to use the built-in IP device.
	 * All others should return something if they want IP to work on them.
	 */
	virtual BIpDevice *OpenIP(void) = 0;
	virtual void Statistics(FILE *f) = 0;

	virtual ~BNetDevice(void);
};


void deliver_packet(
					BNetPacket *buf,
					BNetDevice *dev
					);

#endif /* _NET_DEVICE_H */


