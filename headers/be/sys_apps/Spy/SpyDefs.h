// --------------------------------------------------------------------------- 
/* 
	SpyDefs.h 
	 
	Copyright (c) 2000+ Be Inc. All Rights Reserved. 
	 
	Author:	Alan Ellis 
			November 8, 2001 
 
	One stop shop for Spy constants. This is a pain for dependencies, but easy
	 for finding things. Ah well, there's always a trade off, eh?
*/ 
// --------------------------------------------------------------------------- 
#ifndef SPYDEFS_H
#define SPYDEFS_H

// todo: I'm sure this will be a mess when I check it in, clean it up! - Alan -

// Default TCP listening and sending ports, the Display listens on the first one and
//  sends to the second one, and the Monitor does the opposite.
#define B_SPY_DISPLAY_LISTEN_PORT 		"4139"
#define B_SPY_MONITOR_LISTEN_PORT 		"4138" // BeIA (hrm ...)

//! Message constants that you can subscribe to. They should be pretty self eplanatory.
#define B_SPY_ALL_MODULES_LOADED		'_AML'
#define B_SPY_NO_TARGET					'_SNT'
#define B_SPY_NOTIFICATION				'_SNT'
#define B_SPY_PING_REMOTE				'_SPR'
#define B_SPY_REMOTE_TARGET_INVALID		'_RTI'
#define B_SPY_REMOTE_TARGET_GOOD		'_RTG'
#define B_SPY_SUBSCRIBE					'_SSS'

#define B_SPY_ERROR						"be:Spy-O-Matic.ErrorCode"
#define B_SPY_MESSENGER_ERROR			"be:Spy-O-Matic.MessengerErr"
#define B_SPY_MODULE_NAME				"be:Spy-O-Matic.ModuleName"
#define B_SPY_ORIGINAL_WHAT				"be:Spy-O-Matic.OriginalWhat"
#define B_SPY_REMOTE_TARGET_NAME		"be:Spy-O-Matic.RemoteTargetName"
#define B_SPY_SUBSCRIBER_MESSENGER		"be:Spy-O-Matic.SubscriberMessenger"
#define B_SPY_SUBSCRIBE_TO				"be:Spy-O-Matic.SubscribeTo"

// todo: Move into more appropriate place
#define B_SPY_TOTAL_TIME				"be:Spy-O-Matic.TotalTime"
#define B_SPY_TOTAL_VALUE				"be:Spy-O-Matic.TotalValue"

// SpyData relevant message constants.
#define B_SPY_DATA_MESSAGE				'_SDM'
//#define B_SPY_MODE_CHANGED	'_SMC'

/*! Some constants for standard SpyData. */
#define B_SPY_REMOTE_MESSAGE_ORIGIN		"be:Spy-O-Matic.RemoteMessageOrigin"
#define B_SPY_REMOTE_MESSAGE_TARGET		"be:Spy-O-Matic.RemoteMessageTarget"

// Umm, what can I say about this one?
#define LOCALHOST						"127.0.0.1"

// Which transport are we using?
#define B_SPY_TRANSPORT_CHANGED			'_STC'
#define B_SPY_TRANSPORT					"be:Spy-O-Matic.SpyTransport"
namespace Spy {
	enum SpyTransport
	{
		stNone,
		stTCP,
		stSerial
	};
}	// ns Spy

// Application signatures
#define B_SPY_O_MATIC_MONITOR	 		"application/x-vnd.Be.Spy-O-Matic.Monitor"
#define B_SPY_O_MATIC_DISPLAY	 		"application/x-vnd.Be.Spy-O-Matic.Display"

// Command line arg definitions
#define B_SPY_LOCAL_FLAG				"--local"
#define B_SPY_HELP_FLAG					"--help"
#define B_SPY_TARGET_FLAG				"-t"
#define B_SPY_SERIAL_PORT_FLAG			"-s"
#define SERIAL_DEFAULT					"serial1"

// Remote Message API specifics 
#define B_SPY_SEND_REMOTE_MESSAGE		'_SRM'
#define B_SPY_REMOTE_MESSAGE_DELIVERY	'_RMD'

#define B_SPY_TCP_SEND_PORT				"be:Spy-O-Matic.TCP/IPSeningPort"
#define B_SPY_TCP_LISTEN_PORT			"be:Spy-O-Matic.TCP/IPListeningPort"
#define B_SPY_SERIAL_LISTEN_PORT		"be:Spy-O-Matic.SerialListeningPort"

#define B_SPY_REMOTE_MESSAGE			"be:Spy-O-Matic.RemoteMessage"								
#define B_SPY_MESSAGE_TARGET			"be:Spy-O-Matic.MessageTarget"
#define B_SPY_ORIGIN_APP_SIG			"be:Spy-O-Matic.OriginAppSignature"
#define B_SPY_COMM_ORIGINAL_WHAT		"be:Spy-O-Matic.CommOriginalWhat"

// This is for the SenseListener
#define UDPM_MAX_PAYLOAD (8192)


#endif

