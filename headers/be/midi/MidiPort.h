//******************************************************************************
//
//	File:			BMidiPort.h
//
//	Description:	Midi physical interface port object class.
//
//	Written by:		Eric Knight
//
//	Copyright 1994, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_PORT_H
#define _MIDI_PORT_H

#ifndef _MIDI_H
#include "Midi.h"
#endif

/*------------------------------------------------------------*/

class BMidiPort : public BMidi {
DECLARE_CLASS_INFO(BMidi);
public:
				BMidiPort();
				~BMidiPort();

virtual	void	NoteOff(char channel, 
						char note, 
						char velocity,
						ulong time = NOW);
virtual	void	NoteOn(char channel, 
					   char note, 
					   char velocity,
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

		void	AllNotesOff(bool justChannel = TRUE, ulong time = NOW);

private:
		char	NextFilteredByte(bool* driverClosed = NIL);
virtual	void	Run();

		long	Read(void *buffer, ulong numBytes);
		long	Write(void *buffer, ulong numBytes, ulong time);

		long	fDriverRef;
};

/*------------------------------------------------------------*/

#endif
