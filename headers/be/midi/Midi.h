//******************************************************************************
//
//	File:			Midi.h
//
//	Description:	Abstract Midi object class.
//
//	Written by:		Eric Knight
//
//	Copyright 1994-96, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_H
#define _MIDI_H

#ifndef _MIDI_DEFS_H
#include <MidiDefs.h>
#endif

#ifndef _OBJECT_H
#include <Object.h>
#endif

#ifndef _LIST_H
#include <List.h>
#endif

#ifndef _OS_H
#include <OS.h>
#endif

class BMidiEvent;

class BMidi : public BObject {
B_DECLARE_CLASS_INFO(BObject);

public:
				BMidi();
virtual			~BMidi();

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

virtual	void	Start();
virtual	void	Stop();
		bool	IsRunning();
	
		void	Connect(BMidi* toObject);
		void	Disconnect(BMidi* fromObject);
		bool	IsConnected(BMidi* toObject);
		BList*	Connections();

		void	SnoozeUntil(ulong time);

protected:
		void	SprayNoteOff(uchar channel, 
							 uchar note, 
							 uchar velocity, 
							 ulong time);
		void	SprayNoteOn(uchar channel, 
							uchar note, 
							uchar velocity, 
							ulong time);
		void	SprayKeyPressure(uchar channel, 
								 uchar note, 
								 uchar pressure, 
								 ulong time);
		void	SprayControlChange(uchar channel, 
								   uchar controlNumber,
							 	   uchar controlValue, 
								   ulong time);
		void	SprayProgramChange(uchar channel, 
								   uchar programNumber,
								   ulong time);
		void	SprayChannelPressure(uchar channel, uchar pressure, ulong time);
		void	SprayPitchBend(uchar channel, 
							   uchar lsb, 
							   uchar msb, 
							   ulong time);
		void	SpraySystemExclusive(void* data, long dataLength, 
									 ulong time = B_NOW);
		void	SpraySystemCommon(uchar statusByte, 
							 uchar data1, 
							 uchar data2,
							 ulong time);
		void	SpraySystemRealTime(uchar statusByte, ulong time);

		void	SprayTempoChange(long bpm, ulong time);

		bool	KeepRunning();

private:
friend	long	_run_thread_(void *arg);
friend	long	_inflow_task_(void *arg);
		void	SprayMidiEvent(BMidiEvent* event);
		long	ID();
virtual	void	Run();

		void	StartInflow();
		void	StopInflow();
		bool	IsInflowing();
		void	InflowTask();
		bool	InflowIsAlive();

		BList*		fConnectionList;
		thread_id	fRunTask;
		bool		fIsRunning;
		thread_id	fInflowTask;
		bool		fInflowAlive;
		port_id		fInflowPort;
};

inline	long		BMidi::ID() { return fInflowPort; };
inline	bool		BMidi::IsConnected(BMidi* o) { return fConnectionList->
						       					   HasItem(o); };
inline	BList*		BMidi::Connections() { return fConnectionList; };


#endif
