/* ================

   FILE:  VideoModule.h
   REVS:  $Revision: 1.11 $
   NAME:  marc

   Copyright (c) 1997 by Be Incorporated.  All Rights Reserved.

================ */

#ifndef _VIDEO_MODULE_H
#define _VIDEO_MODULE_H

#include <MediaModule.h>
#include <Bitmap.h>
#include <File.h>

class BView;

struct FilmStripRec {
  int32 signature;
  int32 numFrames;
  int16 packing;
  int16 reserved;
  int16 width;
  int16 height;
  int16 leading;
  int16 framesPerSec;
  char spare[16];
};


class BVideoEvent : public BMediaEvent {
public:
  BVideoEvent(BRect bounds, color_space depth);
  BVideoEvent(void* live_buffer, int32 length, BRect bounds, color_space depth);
  BVideoEvent(BBitmap* bitmap);
  ~BVideoEvent();

  virtual mk_time		Start();
  virtual void			SetStart(mk_time);
  virtual bigtime_t		CaptureTime();
  virtual void			SetCaptureTime(bigtime_t);
  virtual int32			Destination();
  virtual void			SetDestination(int32);
  virtual BBitmap*		Bitmap(BBitmap* spare = NULL);
  virtual BMediaEvent*	Clone();
  virtual BRect			Bounds();
  virtual void*			Bits();
  virtual int32			BitsLength();
  virtual color_space	ColorSpace();

private:
  mk_time		fStart;
  BBitmap*		fBitmap;
  bool			fOwnBitmap;
  int32			fDestination;
  BRect			fBounds;
  void*			fBits;
  bool			fOwnBits;
  int32			fBitsLength;
  color_space	fColorSpace;
  bigtime_t		fCaptureTime;
};


class BVideoRenderer : public BMediaRenderer {
public:
  BVideoRenderer(const char* name = NULL);
  ~BVideoRenderer();

  BView*		View();
  void			SetView(BView*);
  mk_rate		Units();
  mk_time		Start();
  mk_time		Duration();
  void			OpenReceived();
  void			CloseReceived();
  void			WakeUpReceived();
  void			TransportChangedReceived(mk_time time, mk_rate rate,
										 transport_status status);
  void			StreamChangedReceived();

  virtual int32				FramesRendered();
  virtual BMediaChannel*	Channel();

private:
  BMediaChannel*	fChannel;
  BView*			fView;
  bool				fRunning;
  BBitmap*			fSpareBitmap;
  int32				fFramesRendered;
};


class BVideoFileStream : public BEventStream {
public:
  BVideoFileStream(BMediaChannel* channel, BFile* file,
				   mk_time start = B_UNDEFINED_MK_TIME);
  ~BVideoFileStream();

  BMediaEvent*		GetEvent(BMediaChannel* channel);
  BMediaEvent*		PeekEvent(BMediaChannel* channel, mk_time asap = 0);
  status_t			SeekToTime(BMediaChannel* channel, mk_time time);
  void				SetStart(mk_time start);

  virtual BRect				Bounds();
  virtual bigtime_t			CaptureTime();
  virtual BMediaChannel*	Channel();

private:
  BMediaChannel*	fChannel;
  BFile*			fFile;
  mk_time			fTime;
  BRect				fBounds;
  BVideoEvent*		fCurrentEvent;
  int32				fBitsLength;
  FilmStripRec		fTrailer;
};


struct Bt848_buffer;

class BBt848Stream : public BEventStream {
public:
  BBt848Stream(BMediaChannel* channel, int32 x_pixels, int32 y_pixels);
  ~BBt848Stream();

  BMediaEvent*	GetEvent(BMediaChannel* channel);
  BMediaEvent*	PeekEvent(BMediaChannel* channel, mk_time asap = 0);
  BRect			Bounds();

  virtual BMediaChannel*	Channel();

private:
  static int32	_CaptureThread(void*);
  void			CaptureThread();

  BMediaChannel*	fChannel;
  mk_time			fTime;
  BRect				fBounds;
  BVideoEvent*		fCurrentEvent;
  Bt848_buffer*		fBufferDesc;
  void*				fBuffer;
  int32				fBufferSize;
  int32				fBytesPerPixel;
  int32				fBytesPerRow;
  int32				fDriver;
  thread_id			fCaptureThread;
  bigtime_t			fCaptureTime;
  bigtime_t			fPrevCaptureTime;
  sem_id			fSem;
  bool				fBottomUp;
};


class BFilmStripRenderer : public BMediaRenderer {
public:
  BFilmStripRenderer(BFile* file, const char* name = NULL,
					 int32 priority = B_NORMAL_PRIORITY);
  ~BFilmStripRenderer();

  mk_rate	Units();
  mk_time	Start();
  mk_time	Duration();
  void		OpenReceived();
  void		CloseReceived();
  void		WakeUpReceived();
  void		TransportChangedReceived(mk_time time, mk_rate rate,
									  transport_status status);
  void		StreamChangedReceived();

  virtual BMediaChannel*	VideoChannel();
  virtual int32				FramesRendered();

private:
  BMediaChannel*	fChannel;
  bool				fRunning;
  bool				fFirstFrameSeen;
  BFile*			fFile;
  mk_time			fTime;
  BRect				fBounds;
  int32				fBitsLength;
  FilmStripRec		fTrailer;
  char*				fRowBuffer;
};

#endif
