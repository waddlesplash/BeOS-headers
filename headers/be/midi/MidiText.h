//******************************************************************************
//
//	File:			BMidiText.h
//
//	Description:	Midi text input/output object class.
//
//	Written by:		Eric Knight
//
//	Copyright 1994, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_TEXT_H
#define _MIDI_TEXT_H

#ifndef _MIDI_H
#include "Midi.h"
#endif
#ifndef _STDIO_H
#include <inc/stdio.h>
#endif

/*------------------------------------------------------------*/

class BMidiText : public BMidi {
DECLARE_CLASS_INFO(BMidi);
public:
				BMidiText();
virtual			~BMidiText();

virtual	void	NoteOff(char channel, 
						char note, 
						char velocity,
						ulong time = NOW);
virtual	void	NoteOn(char channel, 
					   char note, 
					   char velocity,
					   ulong time = NOW);
virtual	void	KeyPressure(char channel, 
							char note, 
							char pressure,
							ulong time = NOW);
virtual	void	ControlChange(char channel, 
							  char controlNumber, 
							  char controlValue, 
							  ulong time = NOW);
virtual	void	ProgramChange(char channel, 
							  char programNumber,
							  ulong time = NOW);
virtual	void	ChannelPressure(char channel, char pressure, ulong time = NOW);
virtual	void	PitchBend(char channel, 
						  char lsb, 
						  char msb,
						  ulong time = NOW);
virtual	void	SystemExclusive(void* data, long dataLength, ulong time = NOW);
virtual	void	SystemCommon(char statusByte, 
							 char data1, 
							 char data2,
							 ulong time = NOW);
virtual	void	SystemRealTime(char statusByte, ulong time = NOW);

	void	ResetTimer(bool start=FALSE);
private:
virtual	void	Run();
	long	fStartTime;
};

/*------------------------------------------------------------*/

#endif
