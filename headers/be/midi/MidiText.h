//******************************************************************************
//
//	File:			BMidiText.h
//
//	Description:	Midi text input/output object class.
//
//	Written by:		Eric Knight
//
//	Copyright 1994-96, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_TEXT_H
#define _MIDI_TEXT_H

#ifndef _MIDI_H
#include "Midi.h"
#endif
#ifndef _STDIO_H
#include <stdio.h>
#endif

/*------------------------------------------------------------*/

class BMidiText : public BMidi {
public:
				BMidiText();
virtual			~BMidiText();

virtual	void	NoteOff(uchar channel, 
						uchar note, 
						uchar velocity,
						ulong time = B_NOW);
virtual	void	NoteOn(uchar channel, 
					   uchar note, 
					   uchar velocity,
					   ulong time = B_NOW);
virtual	void	KeyPressure(uchar channel, 
							uchar note, 
							uchar pressure,
							ulong time = B_NOW);
virtual	void	ControlChange(uchar channel, 
							  uchar controlNumber, 
							  uchar controlValue, 
							  ulong time = B_NOW);
virtual	void	ProgramChange(uchar channel, 
							  uchar programNumber,
							  ulong time = B_NOW);
virtual	void	ChannelPressure(uchar channel, uchar pressure, ulong time = B_NOW);
virtual	void	PitchBend(uchar channel, 
						  uchar lsb, 
						  uchar msb,
						  ulong time = B_NOW);
virtual	void	SystemExclusive(void* data, long dataLength, ulong time = B_NOW);
virtual	void	SystemCommon(uchar statusByte, 
							 uchar data1, 
							 uchar data2,
							 ulong time = B_NOW);
virtual	void	SystemRealTime(uchar statusByte, ulong time = B_NOW);

	void	ResetTimer(bool start=FALSE);
private:
virtual	void	Run();
	long	fStartTime;
};

/*------------------------------------------------------------*/

#endif
