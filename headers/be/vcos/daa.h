/* ++++++++++
	daa.h
	Copyright (C) 1993 Be Inc.  All Rights Reserved.
	Definitions for using the daa driver.
+++++ */

#ifndef _daah_
#define _daah_

/* layout of the param section, for C */

#ifdef __LINE__
struct daaparam {
	long	host_cmd;		/* host command to the driver */
	long	dsp_cmd;		/* dsp command to the driver */
	long	status;			/* current driver status */
	long	cadence;		/* ring line samples */
	long	reserved1;		/* reserved */
	long	reserved2;		/* reserved */
	/* long	reserved3;		   reserved */
	long	bridge_attenuation;	/* bridging attenuation percentage */
	long	oem_reserved;		/* reserved for oem */
};
#endif

/* commands to the driver, specified by AT&T */

#define daacmd_reset		0x01	/* restart the driver */
#define daacmd_terminate	0x02	/* shut down the driver */

#define daacmd_local_onhook	0x04	/* put local phone on hook */
#define daacmd_local_offhook	0x05	/* put local phone off hook */
#define daacmd_disconnect_cid	0x06	/* disconnect caller id */
#define daacmd_connect_cid	0x07	/* connect caller id */
#define daacmd_co_onhook	0x08	/* go on hook to central office */
#define daacmd_co_offhook	0x09	/* go off hook  to central office */
#define daacmd_stop_idle	0x0a	/* stop idling (resume i/o to codec) */
#define daacmd_start_idle	0x0b	/* start idling (no i/o to codec) */
#define daacmd_speaker_off	0x0e	/* turn speaker off */
#define daacmd_speaker_on	0x0f	/* turn speaker on */

#define daacmd_speaker_vol0	0x10	/* set speaker volume to zero */
#define daacmd_speaker_vol1	0x11	/* set speaker volume to one */
#define daacmd_speaker_vol2	0x12	/* set speaker volume to two */
#define daacmd_speaker_vol3	0x13	/* set speaker volume to three */

#define max_daacmd		0x13	/* last command */

/* commands unique to the Be phone card */

#define daacmd_start_local_ring	0x40000001 /* ring local phone till offhook */
#define daacmd_bridge_on	0x40000002 /* bridge local<=>CO lines */
#define daacmd_bridge_off	0x40000003 /* stop bridging */
#define daacmd_set_bridge_attn	0x40000004 /* set bridging attenuation percentage */
#define daacmd_stop_local_ring	0x40000005 /* stop ringing local phone */


/* status word bit definitions */

#define daast_running		0x00001	/* 1/0 driver running/terminated */
#define daast_co_connected	0x00002	/* 1/0 central office line present/absent */
#define daast_cid_connected	0x00004	/* 1/0 caller id enabled/disabled */
#define daast_co_offhook	0x00008	/* 1/0 co line offhook/onhook */
#define daast_idle		0x00010	/* 1/0 idle mode enabled/disabled */
#define daast_rsvd		0x00020	/* 1/0 reserved */
#define daast_speaker_on	0x00040	/* 1/0 speaker on/off */
#define daast_speaker_vol	0x00180	/* speaker volume bits */
#define daast_co_ringing	0x00200	/* 1/0 co line ringing/not ringing */
#define daast_local_offhook	0x00400	/* 1/0 local phone offhook/onhook */
#define daast_ringing_local	0x04000	/* 1/0 currently ringing local phone */
#define daast_local_bridged	0x08000	/* 1/0 local line is/not bridged to CO */
#define daast_ring_count	0xF0000	/* ring count (0-16) */

#define daast_speaker_vol_shift	7 	/* shift amt to get volume bits */
#define daast_ring_count_shift	16	/* shift amt to get ring count */

#endif

