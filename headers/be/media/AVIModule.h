/* ================

   FILE:  AVIModule.h
   REVS:  $Revision: 1.6 $
   NAME:  marc

   Copyright (c) 1997 by Be Incorporated.  All Rights Reserved.

================ */

#ifndef _AVI_MODULE_H
#define _AVI_MODULE_H

#include <MediaModule.h>
#include <Rect.h>
#include <stdio.h>

class AVIidx1Entry;
class BVideoEvent;
class BAudioEvent;
class BFile;

class BAVISource : public BEventStream {
public:
  BAVISource(BMediaChannel* video_channel, BMediaChannel* audio_channel,
			 BFile* file, mk_time start = 0);
  ~BAVISource();

  BMediaEvent*		GetEvent(BMediaChannel* channel);
  BMediaEvent*		PeekEvent(BMediaChannel* channel, mk_time asap = 0);
  status_t			SeekToTime(BMediaChannel* channel, mk_time time);
  void				SetStart(mk_time start);

  virtual BRect				Bounds();
  virtual bigtime_t			CaptureTime();
  virtual BMediaChannel*	VideoChannel();
  virtual BMediaChannel*	AudioChannel();

private:
  virtual char*				ReadHeader();

  BMediaChannel*	fVideoChannel;
  BMediaChannel*	fAudioChannel;
  BFile*			fFile;
  BVideoEvent*		fVideoEvent;
  BAudioEvent*		fAudioEvent;
  int32				fVideoFrame;
  int32				fAudioSample;
  BRect				fBounds;
  int32				fWidth;
  int32				fHeight;
  int32				fBitsLength;
  int32				fNumFrames;
  int32				fNumSamples;
  mk_rate			fFrameRate;
  mk_rate			fSamplingRate;
  fpos_t			fMoviStart;
  AVIidx1Entry*		fIndex;
  int32				fIndexSize;
  int32				fIndexVideo;
  int32				fIndexAudio;
  short*			fAudioBuffer;
  int32				fAudioBufferSize;
  bool				fStereo;
};


class BAVIRenderer : public BMediaRenderer {
public:
  BAVIRenderer(BFile* file, const char* name = NULL,
			   int32 priority = B_NORMAL_PRIORITY);
  ~BAVIRenderer();

  mk_time	Start();
  mk_time	Duration();
  void		OpenReceived();
  void		CloseReceived();
  void		WakeUpReceived();
  void		TransportChangedReceived(mk_time time, mk_rate rate,
									  transport_status status);
  void		StreamChangedReceived();

  virtual BMediaChannel*	VideoChannel();
  virtual mk_rate			FrameRate();
  virtual int32				FramesRendered();
  virtual BMediaChannel*	AudioChannel();
  virtual mk_rate			SamplingRate();

private:
  virtual void				WriteHeader();
  virtual void				AddIndexEntry(int32, int32, int32, int32);

  BMediaChannel*	fVideoChannel;
  BMediaChannel*	fAudioChannel;
  BFile*			fFile;
  BList				fIndex;
  int32				fIndexOffset;
  BRect				fBounds;
  int32				fWidth;
  int32				fHeight;
  int32				fBitsLength;
  int32				fNumFrames;
  int32				fStartFrame;
  mk_time			fAudioTime;
  mk_time			fStartTime;
  mk_time			fCurrentTime;
  mk_time			fAccumulatedTime;
  int32				fNumSamples;
  short*			fBuffer;
  int32				fBufferSamples;
  bool				fRunning;
  bool				fStereo;
};

#endif
