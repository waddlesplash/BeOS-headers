//******************************************************************************
//
//	File:			BMidiStore.h
//
//	Description:	Midi event storage object class.
//
//	Written by:		Eric Knight
//
//	Copyright 1994-96, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_STORE_H
#define _MIDI_STORE_H

#ifndef _MIDI_H
#include "Midi.h"
#endif
#ifndef _STDIO_H
#include <stdio.h>
#endif
class BMidiEvent;
class BFile;

/*------------------------------------------------------------*/

class BMidiStore : public BMidi {
public:
				BMidiStore();
virtual			~BMidiStore();

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

virtual	void	TempoChange(long bpm, ulong time = B_NOW);

		void	Import(BFile*);
		void	Export(BFile*, long format);

		void	SortEvents(bool force=FALSE);
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
						 uchar type, 
		   	         	 uchar data1 = 0, 
						 uchar data2 = 0,
		   	         	 uchar data3 = 0, 	 
						 uchar data4 = 0);
		void	AddSystemExclusive(void* data, long dataLength);
	
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
		uchar*	Msg();
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
		bool	WriteSystemExclusiveEvent(ulong deltaTime, 
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
		bool		fNeedsSorting;
		bool		fResetTimer;
		ulong		fStartTime;
		BFile*		fFile;
		short		fDivision;
		float		fDivisionFactor;
		long		fTempo;
		long		fCurrTime;
		long		fCurrTrack;
		long		fNumTracks;
		
		long		fToBeRead;
		long		fMsgIndex;
		long		fMsgSize;
		uchar*		fMsgBuff;
	
		long		fNumBytesWritten;
};

inline	ulong		BMidiStore::CountEvents() { return fNumEvents; };
inline	ulong		BMidiStore::CurrentEvent() { return fCurrEvent; };
inline	ulong		BMidiStore::BeginTime() { return fStartTime; };

/*------------------------------------------------------------*/

#endif
