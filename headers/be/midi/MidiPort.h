//****************************************************************************
//
//	File:			Midi.h
//
//	Description:	Abstract MIDI object class.
//
//	Copyright 1997, Be Incorporated
//
//****************************************************************************

#ifndef _MIDI_PORT_H
#define _MIDI_PORT_H

#include <Midi.h>

/*------------------------------------------------------------*/

class BMidiPort : public BMidi {

public:
				BMidiPort(const char *name=NULL);
				~BMidiPort();

		status_t	InitCheck() const; 
		status_t	Open(const char *name);
		void	Close();

virtual	void	NoteOff(uchar channel, 
						uchar note, 
						uchar velocity,
						uint32 time = B_NOW);

virtual	void	NoteOn(uchar channel, 
					   uchar note, 
					   uchar velocity,
			    	   uint32 time = B_NOW);

virtual	void	KeyPressure(uchar channel, 
							uchar note, 
							uchar pressure,
							uint32 time = B_NOW);

virtual	void	ControlChange(uchar channel, 
							  uchar controlNumber,
							  uchar controlValue, 
							  uint32 time = B_NOW);

virtual	void	ProgramChange(uchar channel, 
								uchar programNumber,
							  	uint32 time = B_NOW);

virtual	void	ChannelPressure(uchar channel, 
								uchar pressure, 
								uint32 time = B_NOW);

virtual	void	PitchBend(uchar channel, 
						  uchar lsb, 
						  uchar msb,
			    		  uint32 time = B_NOW);

virtual	void	SystemExclusive(void* data, 
								size_t dataLength, 
								uint32 time = B_NOW);

virtual	void	SystemCommon(uchar statusByte, 
							 uchar data1, 
							 uchar data2,
							 uint32 time = B_NOW);

virtual	void	SystemRealTime(uchar statusByte, uint32 time = B_NOW);

virtual	status_t	Start();
virtual	void	Stop();

private:

virtual	void		_ReservedMidiPort1();
virtual	void		_ReservedMidiPort2();
virtual	void		_ReservedMidiPort3();

virtual	void	Run();

		ssize_t	Read(void *buffer, size_t numBytes) const;
		ssize_t	Write(void *buffer, size_t numBytes, uint32 time) const;

		int32	fWriteDriverRef;
		int32	fReadDriverRef;

		char*	fName;
		status_t fCStatus;
		uint32		_reserved[4];
};

/*------------------------------------------------------------*/

#endif
