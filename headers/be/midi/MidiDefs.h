//******************************************************************************
//
//	File:			MidiDefs.h
//
//	Description:	Midi Kit constants and coolants
//
//	Written by:		Eric Knight
//
//	Copyright 1994, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_DEFS_H
#define _MIDI_DEFS_H

/*------------------------------------------------------------*/

#define 	NOW 			get_tick()

/*------------------------------------------------------------*/

// Useful defines
#define HIGH_NIBBLE(x)			((x) & 0xf0)
#define LOW_NIBBLE(x)			((x) & 0x0f)

/*------------------------------------------------------------*/

// Channel Message Masks
const char 	NOTE_OFF			= 0x80;
const char 	NOTE_ON				= 0x90;
const char 	KEY_PRESSURE		= 0xa0;
const char 	CONTROL_CHANGE		= 0xb0;
const char 	PROGRAM_CHANGE		= 0xc0;
const char 	CHANNEL_PRESSURE	= 0xd0;
const char 	PITCH_BEND 			= 0xe0;

/*------------------------------------------------------------*/

// System Messages
const char	SYS_EX_START	= 0xf0;
const char	MIDI_TIME_CODE	= 0xf1;
const char	SONG_POS_PTR	= 0xf2;
const char	SONG_SELECT		= 0xf3;
const char	TUNE_REQUEST	= 0xf6;
const char	SYS_EX_END		= 0xf7;
const char	TIMING_CLOCK	= 0xf8;
const char	START			= 0xfa;
const char	CONTINUE		= 0xfb;
const char	STOP			= 0xfc;
const char	ACTIVE_SENSING	= 0xfe;
const char	SYSTEM_RESET	= 0xff;

/*------------------------------------------------------------*/

// Controller Numbers
const char	MODULATION			= 0x01;
const char	BREATH_CTRL			= 0x02;
const char	FOOT_CTRL			= 0x04;
const char	PORTAMENTO_TIME		= 0x05;
const char	DATA_ENTRY			= 0x06;
const char 	MAIN_VOLUME			= 0x07;
const char	BALANCE				= 0x08;
const char 	PAN					= 0x0a;
const char	EXPRESSION_CTRL		= 0x0b;
const char	GENERAL_CTRL_1		= 0x10;
const char	GENERAL_CTRL_2		= 0x11;
const char	GENERAL_CTRL_3		= 0x12;
const char	GENERAL_CTRL_4		= 0x13;
const char	SUSTAIN_PEDAL		= 0x40;
const char	PORTAMENTO			= 0x41;
const char	SOSTENUTO			= 0x42;
const char	SOFT_PEDAL			= 0x43;
const char	HOLD_2				= 0x45;
const char	GENERAL_CTRL_5		= 0x50;
const char	GENERAL_CTRL_6		= 0x51;
const char	GENERAL_CTRL_7		= 0x52;
const char	GENERAL_CTRL_8		= 0x53;
const char	EXT_EFFECTS_DEPTH	= 0x5b;
const char	TREMOLO_DEPTH		= 0x5c;
const char	CHORUS_DEPTH		= 0x5d;
const char	CELESTE_DEPTH		= 0x5e;
const char	PHASER_DEPTH		= 0x5f;
const char	DATA_INCREMENT		= 0x60;
const char	DATA_DECREMENT		= 0x61;
const char 	RESET_ALL_CONTROLLERS	= 0x79;
const char	LOCAL_CONTROL		= 0x7a;
const char 	ALL_NOTES_OFF		= 0x7b;
const char	OMNI_MODE_OFF		= 0x7c;
const char	OMNI_MODE_ON		= 0x7d;
const char	MONO_MODE_ON		= 0x7e;
const char	POLY_MODE_ON		= 0x7f;

const char	TEMPO_CHANGE		= 0x51;

/*------------------------------------------------------------*/

#endif