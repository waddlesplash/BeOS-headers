/******************************************************************************

	File:	MediaDefs.h

	Copyright 1995-96, Be Incorporated

******************************************************************************/

#ifndef _MEDIA_DEFS_H
#define _MEDIA_DEFS_H

#ifndef _OS_H
#include <OS.h>
#endif

#ifndef _ERRORS_H
#include <Errors.h>
#endif

#define		B_MEDIA_LEVEL	41

#define 	B_NO_CHANGE (-1)

/* ================
   Subscriber IDs and special values
   ================ */

#define			B_NO_SUBSCRIBER_ID		((subscriber_id)0)
#define			B_NO_SUBSCRIBER_NAME		"not subscribed"

#define			B_SHARED_SUBSCRIBER_ID	((subscriber_id)-1)
#define			B_SHARED_SUBSCRIBER_NAME	"shared subscriber"

/* The Invisible Subscriber is entitled to join ANY clique */
#define			B_INVISIBLE_SUBSCRIBER_ID			((subscriber_id)-2)
#define			B_INVISIBLE_SUBSCRIBER_NAME		"invisible subscriber"


/* ================
   Values for sound files and audio streams 
   ================ */

/* values for byte_ordering */
enum { B_BIG_ENDIAN, B_LITTLE_ENDIAN };

/* values for sample_format */
enum { 
  B_UNDEFINED_SAMPLES,
  B_LINEAR_SAMPLES,
  B_FLOAT_SAMPLES,
  B_MULAW_SAMPLES
  };

/* Audio device codes for BAudioSubscriber's
 * Get/SetVolume() and EnableDevice() calls 
 */
enum  {
	B_CD_THROUGH=0,
	B_LINE_IN_THROUGH,
	B_ADC_IN,
	B_LOOPBACK,
	B_DAC_OUT,
	B_MASTER_OUT,
	B_SPEAKER_OUT,
	B_SOUND_DEVICE_END
  };

/* ADC input codes */
enum {
	B_CD_IN,
	B_LINE_IN,
	B_MIC_IN 
  };

/* Audio Subscriber stream codes */
enum {
  B_DAC_STREAM = 2354,
  B_ADC_STREAM
  };

#endif	// #ifndef _MEDIA_DEFS_H
