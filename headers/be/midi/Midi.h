//******************************************************************************
//
//	File:			Midi.h
//
//	Description:	Abstract Midi object class.
//
//	Written by:		Eric Knight
//
//	Copyright 1994, Be Incorporated
//
//******************************************************************************

#ifndef _MIDI_H
#define _MIDI_H

#ifndef _MIDI_DEFS_H
#include <midi/MidiDefs.h>
#endif

#ifndef _SUPPORT_KIT_H
#include <SupportKit.h>
#endif

#ifndef _OS_KIT_H
#include <OSKit.h>
#endif

class BMidiEvent;

class BMidi : public BObject {
DECLARE_CLASS_INFO(BObject);

public:
				BMidi();
virtual			~BMidi();

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

		void	Start();
		void	Stop();
		bool	IsRunning();
	
		void	Connect(BMidi* toObject);
		void	Disconnect(BMidi* fromObject);
		bool	IsConnected(BMidi* toObject);
		BList*	Connections();

		void	SnoozeUntil(ulong time);

protected:
		void	SprayNoteOff(char channel, 
							 char note, 
							 char velocity, 
							 ulong time);
		void	SprayNoteOn(char channel, 
							char note, 
							char velocity, 
							ulong time);
		void	SprayKeyPressure(char channel, 
								 char note, 
								 char pressure, 
								 ulong time);
		void	SprayControlChange(char channel, 
								   char controlNumber,
							 	   char controlValue, 
								   ulong time);
		void	SprayProgramChange(char channel, 
								   char programNumber,
								   ulong time);
		void	SprayChannelPressure(char channel, char pressure, ulong time);
		void	SprayPitchBend(char channel, 
							   char lsb, 
							   char msb, 
							   ulong time);
		void	SpraySystemExclusive(void* data, long dataLength, 
									 ulong time = NOW);
		void	SpraySystemCommon(char statusByte, 
							 char data1, 
							 char data2,
							 ulong time);
		void	SpraySystemRealTime(char statusByte, ulong time);

		void	SprayTempoChange(long bpm, ulong time);

		bool	KeepRunning();

private:
friend	void	_run_thread_();
friend	void	_inflow_task_();
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
