/******************************************************************************

	File:			SoundFile.h

	Description:	Interface for a format-insensitive sound file object.

	Copyright 1995-96, Be Incorporated

******************************************************************************/

#ifndef _SOUND_FILE_H
#define _SOUND_FILE_H

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

#ifndef _FILE_H
#include <File.h>
#endif

#ifndef _MEDIA_DEFS_H
#include <MediaDefs.h>
#endif

#ifndef _OBJECT_H
#include <Object.h>
#endif

#ifndef _STORAGE_DEFS_H
#include <StorageDefs.h>
#endif

enum { B_UNKNOWN_FILE, B_AIFF_FILE, B_WAV_FILE, B_UNIX_FILE };

class BSoundFile : public BFile {

	B_DECLARE_CLASS_INFO(BFile);


public:
					BSoundFile();
					BSoundFile(record_ref ref);
	virtual			~BSoundFile();

	long			FileFormat();
	long			SamplingRate();		/* aka sampling rate */
	long			CountChannels();		/* aka channel count */
	long			SampleSize();		/* aka sample size */
	long			ByteOrder();
	long			SampleFormat();
	long			FrameSize();
	long			CountFrames();

	bool			IsCompressed();
	long			CompressionType();
	char	 		*CompressionName();

	virtual long 	SetFileFormat(long format);
	virtual long	SetSamplingRate(long fps);
	virtual long	SetChannelCount(long spf);
	virtual long	SetSampleSize(long bps);
	virtual long	SetByteOrder(long bord);
	virtual long	SetSampleFormat(long fmt);
	virtual long	SetCompressionType(long type);
	virtual long   	SetCompressionName(char *name);
	virtual long	SetIsCompressed(bool tf);
	virtual	long	SetDataLocation(long offset);
	virtual long	SetFrameCount(long count);

	long			ReadFrames(char *buf, long count);
	virtual long	SeekToFrame(ulong n);
	long 			FrameIndex();
	long			FramesRemaining();

/* ================
   Protected members accessed directly by subclasses
   ================ */
protected:
virtual long 		set_ref(long volid, record_id id);
	long			fFileFormat;
	long			fSamplingRate;
	long 			fChannelCount;
	long			fSampleSize;
	long			fByteOrder;
	long			fSampleFormat;
	
	long			fByteOffset;	/* offset to first sample */

	long			fFrameCount;
	long			fFrameIndex;

	bool			fIsCompressed;
	long			fCompressionType;
	char			*fCompressionName;
private:

	void Initialize(void);
};

inline bool BSoundFile::IsCompressed()
{	return(fIsCompressed);	}

inline long BSoundFile::CompressionType()
{	return(fCompressionType);	}

inline char *BSoundFile::CompressionName()
{	return(fCompressionName);	}

inline long BSoundFile::FileFormat()
{	return(fFileFormat);	}

inline long BSoundFile::SamplingRate()
{	return(fSamplingRate);	}

inline long BSoundFile::CountChannels()
{	return(fChannelCount);	}

inline long BSoundFile::SampleSize()
{	return(fSampleSize);	}

inline long BSoundFile::ByteOrder()
{	return(fByteOrder);	}

inline long BSoundFile::SampleFormat()
{	return(fSampleFormat);	}

inline long BSoundFile::FrameSize()
{ 	return(fSampleSize * fChannelCount);	}

inline long BSoundFile::CountFrames()
{	return(fFrameCount);	}

inline long BSoundFile::FrameIndex()
{	return(fFrameIndex);	}

#endif			// #ifndef _SOUND_FILE_H
