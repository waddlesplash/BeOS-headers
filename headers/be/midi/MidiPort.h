//******************************************************************************
//
//	File:			BMidiPort.h
//
//	Description:	Midi physical interface port object class.
//
//	Written by:		Eric Knight
//
//	Copyright 1994-96, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_PORT_H
#define _MIDI_PORT_H

#ifndef _MIDI_H
#include "Midi.h"
#endif

/*------------------------------------------------------------*/

class BMidiPort : public BMidi {
B_DECLARE_CLASS_INFO(BMidi);
public:
				BMidiPort();
				~BMidiPort();

				Open(const char *name);
		void	Close();

virtual	void	NoteOff(uchar channel, 
						uchar note, 
						uchar velocity,
						ulong time = B_NOW);
virtual	void	NoteOn(uchar channel, 
					   uchar note, 
					   uchar velocity,
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

		void	AllNotesOff(bool justChannel = TRUE, ulong time = B_NOW);

virtual	void	Start();
virtual	void	Stop();

private:
		uchar	NextFilteredByte(bool* driverClosed = NIL);
virtual	void	Run();

		long	Read(void *buffer, ulong numBytes);
		long	Write(void *buffer, ulong numBytes, ulong time);

		long	fWriteDriverRef;
		long	fReadDriverRef;
};

/*------------------------------------------------------------*/

#endif
