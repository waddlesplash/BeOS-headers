/******************************************************************************

	File:	AudioSubscriber.h

	Copyright 1995-96, Be Incorporated

******************************************************************************/

#ifndef _AUDIO_SUBSCRIBER_H
#define _AUDIO_SUBSCRIBER_H

#ifndef _SUBSCRIBER_H
#include <Subscriber.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif


/* ================
   Class definition for BAudioSubscriber
   ================ */


class BAudioSubscriber : public BSubscriber {

	B_DECLARE_CLASS_INFO(BSubscriber);

public:

					BAudioSubscriber(const char *name=NULL);
	virtual			~BAudioSubscriber();

	long			ADCInput(void);
	long			SetADCInput(long device);

	long			GetDACSampleInfo(long *sampleSize,
									 long *channelCount,
									 long *byteOrder,
									 long *sampleFormat);

	long			SetDACSampleInfo(long sampleSize,
									 long channelCount,
									 long byteOrder,
									 long sampleFormat);

	long			GetADCSampleInfo(long *sampleSize,
									 long *channelCount,
									 long *byteOrder,
									 long *sampleFormat);

	long			SetADCSampleInfo(long sampleSize,
									 long channelCount,
									 long byteOrder,
									 long sampleFormat);

	long			SamplingRate(void);
	long			SetSamplingRate(long sRate);

	long			SetVolume(long device, 
							  float l_volume, 
							  float r_volume);

	long			GetVolume(long device, 
							  float *l_volume, 
							  float *r_volume,
							  bool *enabled);
	
	long			EnableDevice(long device, bool enable);
	bool			IsDeviceEnabled(long device);

	long			BoostMic(bool tf);
	bool			IsMicBoosted();

/* ================
   Private member functions
   ================ */

private:

long GetSampleParameters(long resource,
						 long *sampleSize,
						 long *channelCount,
						 long *byteOrder,
						 long *sampleFormat);

long SetSampleParameters(long resource,
						 long sampleSize,
						 long channelCount,
						 long byteOrder,
						 long sampleFormat);


};

#endif			// #ifdef _AUDIO_SUBSCRIBER_H
