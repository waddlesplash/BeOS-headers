/* ++++++++++
	audio.h
	Copyright (C) 1992 Be Inc.  All Rights Reserved.
	Definitions for using driver for the first Be Audio Card.

	Modification History (most recent first):
	24 nov 92	rwh	new today
+++++ */

#ifndef _audioh_
#define _audioh_

/* the dsp id where the audio card lives is hardcoded for now... */

#define AUDIO_DSP_ID		3

/* offsets to field in the param section for controlling the driver */

#define audioparam_command	0	/* command to the driver */
#define audioparam_status	4	/* current driver status */
#define audioparam_control	8	/* in AT&T's daa.s, but not used */
#define audioparam_frcontrol	12

/* layout of the param section, for C */

#ifdef __LINE__
struct audio_param {
	long	command;		/* command to the driver */
	long	status;			/* current driver status */
	long	control;		/* control value to/from driver */
	long	frame_control;		/* data mode control word */
	long	lspeaker_buf;		/* -> left speaker AIAO buffer */
	long	rspeaker_buf;		/* -> right speaker AIAO buffer */
	long	lmic_buf;		/* -> left mic AIAO buffer */
	long	rmic_buf;		/* -> right mic AIAO buffer */
};
#endif

/* commands to the driver */

#define audiocmd_reset		1	/* restart the driver */
#define audiocmd_terminate	2	/* shut down the driver */

#define max_audiocmd		2	/* last command */


/* status word bit definitions */

#define NODRIVER        0x4     /* 1 indicates driver is terminated */


/* ---
   Sample rates.  Set w/the init command, in the 'control' paramater.
--- */

#define audio_8_kHz		0
#define audio_16_kHz		1
#define audio_27x42857_kHz	2
#define audio_32_kHz		3
#define audio_48_kHz		6
#define audio_9x6_kHz		7
#define audio_5x5125_kHz	8
#define audio_11x025_kHz	9
#define audio_18x9_kHz		10
#define audio_22x05_kHz		11
#define audio_37x8_kHz		12
#define audio_44x1_kHz		13
#define audio_33x075_kHz	14
#define audio_6x615_kHz		15

#define audio_sample_rate_mask	0x0000000F
#define audio_sample_rate_shift	0


/* ---
   Audio data formats.  Set w/the init command, in the 'control' paramater.
--- */

#define audio_pcm_16		0
#define audio_ulaw_8		1
#define audio_alaw_8		2

#define audio_data_format_mask	0x00000030
#define audio_data_format_shift	4

/* ---
   Stereo/mono control.  Set w/the init command, in the 'control' parameter.
--- */

#define audio_stereo		0
#define audio_mono		1

#define audio_stereo_mask	0x00000040
#define audio_stereo_shift	6


/* ----------
	The second 32 bits of the AD1489's 64 bit data frame is all control
	information.  The definitions that follow enable the creation
	and manipulation of these control words.

	We restrict changes in these control values to once every VCOS
	frame (every 10 ms), so that we can pass the control word in
	the parameter buffer.  If we allowed them to change for every
	data point (which the AD1849 could do), we would have to
	pass in an AIAO buffer of control words, or mix them in with the
	data.
---------- */

/* ---
   output channel attenuation values
--- */

#define audio_left_out_attn_min		0
#define audio_left_out_attn_max		63
#define audio_left_out_attn_mask	0x3F000000
#define audio_left_out_attn_shift	24

#define audio_right_out_attn_min	0
#define audio_right_out_attn_max	63
#define audio_right_out_attn_mask	0x003F0000
#define audio_right_out_attn_shift	16

/* ---
   input channel gain values
--- */

#define audio_left_in_gain_min		0
#define audio_left_in_gain_max		15
#define audio_left_in_gain_mask		0x00000F00
#define audio_left_in_gain_shift	8

#define audio_right_in_gain_min		0
#define audio_right_in_gain_max		15
#define audio_right_in_gain_mask	0x0000000F
#define audio_right_in_gain_shift	0

/* ---
   monitor mix attenuation
--- */

#define audio_monitor_attn_min		0
#define audio_monitor_attn_max		15
#define audio_monitor_attn_mask		0x000000F0
#define audio_monitor_attn_shift	4

/* ---
   value for various other controls, hopefully self explanatory.
--- */

#define audio_line0_on			1
#define audio_line0_off			0
#define audio_line0_mask		0x40000000
#define audio_line0_shift		30

#define audio_line1_on			1
#define audio_line1_off			0
#define audio_line1_mask		0x80000000
#define audio_line1_shift		31

#define audio_mono_spkr_on		1
#define audio_mono_spkr_off		0
#define audio_mono_spkr_mask		0x00400000
#define audio_mono_spkr_shift		22

#define audio_input_line		0
#define audio_input_mic			1
#define audio_input_mask		0x00001000
#define audio_input_shift		12

#endif

