//******************************************************************************
//
//	File:			BMidiStore.h
//
//	Description:	Midi event storage object class.
//
//	Written by:		Eric Knight
//
//	Copyright 1994, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_STORE_H
#define _MIDI_STORE_H

#ifndef _MIDI_H
#include "Midi.h"
#endif
#ifndef _STDIO_H
#include <inc/stdio.h>
#endif
class BMidiEvent;

/*------------------------------------------------------------*/

class BMidiStore : public BMidi {
DECLARE_CLASS_INFO(BMidi);
public:
				BMidiStore();
virtual			~BMidiStore();

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

virtual	void	TempoChange(long bpm, ulong time = NOW);

		void	Import(char *pathName);
		void	Export(char *pathName, long format);

		ulong	CountEvents();
		ulong	CurrentEvent();
		void	SetCurrentEvent(ulong);
		ulong	DeltaOfEvent(ulong eventNumber);
		ulong	EventAtDelta(ulong time);
		ulong	BeginTime();
	
		void	SetTempo(long bpm);
		long	Tempo();

private:
virtual	void	Run();

		void	AddEvent(ulong time, 
						 bool inMS, 
						 char type, 
		   	         	 char data1 = 0, 
						 char data2 = 0,
		   	         	 char data3 = 0, 	 
						 char data4 = 0);
		void	AddSysEx(void* data, long dataLength);
		void	SortMidiEvents();
	
		void	Error(char*);
	
		void	ReadHeader();
		long	ReadMT(char*);
		long	GetC();
		long	Read32Bit();
		long	EGetC();
		long	To32Bit(long, long, long, long);
		long	Read16Bit();
		long	To16Bit(long, long);
		bool	ReadTrack();
		long	ReadVariNum();
		void	ChannelMessage(long, long, long);
		void	MsgInit();
		void	MsgAdd(long);
		void	BiggerMsg();
		void	MetaEvent(long);
		long	MsgLength();
		char*	Msg();
		void	BadByte(long);
	
		long	PutC(long c);
		bool	WriteTrack(long track);
		void	WriteTempoTrack();
		bool	WriteTrackChunk(long whichTrack);
		void	WriteHeaderChunk(long format);
		bool	WriteMidiEvent(ulong deltaTime, 
							   ulong type, 
							   ulong channel, 
							   uchar* data, 
							   ulong size);
		bool	WriteMetaEvent(ulong deltaTime, 
							   ulong type, 
							   uchar* data, 
							   ulong size);
		bool	WriteSysExEvent(ulong deltaTime, 
							    uchar* data, 
							    ulong size);
		void	WriteTempo(ulong deltaTime, long tempo);
		void	WriteVarLen(ulong value);
		void	Write32Bit(ulong data);
		void	Write16Bit(ushort data);
		long	EPutC(uchar c);
	
		ulong	TicksToMilliseconds(ulong ticks);
		ulong	MillisecondsToTicks(ulong ms);

		BMidiEvent*	fEvents;
		ulong		fNumEvents;
		ulong		fEventsSize;
		ulong		fCurrEvent;
		bool		fResetTimer;
		ulong		fStartTime;
		FILE*		fFileRef;
		short		fDivision;
		float		fDivisionFactor;
		long		fTempo;
		long		fCurrTime;
		long		fCurrTrack;
		long		fNumTracks;
		
		long		fToBeRead;
		long		fMsgIndex;
		long		fMsgSize;
		char*		fMsgBuff;
	
		long		fNumBytesWritten;
};

inline	ulong		BMidiStore::CountEvents() { return fNumEvents; };
inline	ulong		BMidiStore::CurrentEvent() { return fCurrEvent; };
inline	ulong		BMidiStore::BeginTime() { return fStartTime; };

/*------------------------------------------------------------*/

#endif
