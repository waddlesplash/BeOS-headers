//******************************************************************************
//
//	File:		Phone.h
//
//	Description:	BPhone class interface
//
//	Written by:	Eric Knight
//
//	Copyright 1992-93, Be Incorporated
//
//	Change History:
//
//	11/25/92	ehk	new today (see .cpp for mods)
//
//******************************************************************************


#ifndef _PHONE_H
#define	_PHONE_H

#ifndef _OBJECT_H
#include <sys/Object.h>
#endif
#ifndef _STDIO_H
#include <stdio.h>
#endif

//------------------------------------------------------------------------------

#define	kOn		TRUE
#define	kOff		FALSE
#define	kNoTerminator	0
#define kNumberLength	32

//------------------------------------------------------------------------------

enum volType { kSilent, kLowVolume, kMidVolume, kHighVolume };

//------------------------------------------------------------------------------

typedef struct {
	long idle_count;
	long idle_min;
	long frame_count;
	long debug_val;
	long sample_rate;
	char *mailbox;
	char off_hook;
	char volume;
	char fill;
	char state;
} phoneParam;

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------

class	BPhone : BObject {
	
public:
		void		BPhone();
				~BPhone();
		
		void		SetHook(char state);
		char		HookIsOff();
		void		Flash(long miliseconds = 1000);
		void		SetVolume(volType volume);
		volType		GetVolume();
		void		SetDial9(char state);
		void		SetLocalAreaCode(char* threeDigits);
		
		long		Dial(char* digits);
		short		GetTones(char* digits, short max, char terminator = kNoTerminator);
		void		AutoAnswer(char state);
virtual		void		OnAnswer();
		long		Record(char* toFile, long maxSeconds);
		long		Play(char* fromFile);
		
		void		AnswerTask();
private:
		long		InitPhoneDriver();
		void		ClosePhoneDriver();
		long		FifoToDisk(long hf, FILE* fd);
		long		FifoToBuffer(long hf, long* buffer, long maxLength);
		long		DiskToFifo(long hf, FILE* fd);
		long		BufferToFifo(long hf, long* buffer, long length);
		
		long		ftidPhone;
		phoneParam*	fParamPtr;
		char		fAutoAnswer;
		long		fAnswerTask;
		char		fInOnAnswer;
		char		fDial9;
		char		fLocalAreaCode[4];  
};

//------------------------------------------------------------------------------

#endif
