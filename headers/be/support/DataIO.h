//****************************************************************************
//
//	File:		DataIO.h
//
//	Description:	IO classes
//						BDataIO 
//						BPositionIO
//						BMallocIO
//
//	Copyright 1997, Be Incorporated
//
//****************************************************************************
#pragma once

#ifndef	_DATA_IO_H
#define	_DATA_IO_H

#include <SupportDefs.h>

class BDataIO {
public:
					BDataIO();
virtual				~BDataIO();

virtual	ssize_t		Read(void *buffer, size_t size) = 0;
virtual	ssize_t		Write(const void *buffer, size_t size) =0;

private:

virtual	void		_ReservedDataIO1();
virtual	void		_ReservedDataIO2();
virtual	void		_ReservedDataIO3();
virtual	void		_ReservedDataIO4();

					BDataIO(const BDataIO &);
		BDataIO		&operator=(const BDataIO &);

		int32		_reserved[2];
};


class BPositionIO : public BDataIO {
public:
					BPositionIO();
virtual				~BPositionIO();

virtual	ssize_t		Read(void *buffer, size_t size);
virtual	ssize_t		Write(const void *buffer, size_t size);

virtual	ssize_t		ReadAt(off_t pos, void *buffer, size_t size) = 0;
virtual	ssize_t		WriteAt(off_t pos, const void *buffer, size_t size) = 0;

virtual off_t		Seek(off_t position, uint32 seek_mode) = 0;
virtual	off_t		Position() const = 0;

virtual status_t	SetSize(off_t size);

private:
virtual	void		_ReservedPositionIO1();
virtual	void		_ReservedPositionIO2();
virtual void		_ReservedPositionIO3();
virtual void		_ReservedPositionIO4();
		int32		_reserved[2];
};

// ---------------------------------------------------------------- //

class BMallocIO : public BPositionIO {
public:
					BMallocIO();
virtual				~BMallocIO();

virtual	ssize_t		ReadAt(off_t pos, void *buffer, size_t size);
virtual	ssize_t		WriteAt(off_t pos, const void *buffer, size_t size);

virtual	off_t		Seek(off_t pos, uint32 seek_mode);
virtual off_t		Position() const;
virtual status_t	SetSize(off_t size);

		void		SetBlockSize(size_t blocksize);

const	void		*Buffer() const;
		size_t		BufferLength() const;

private:

virtual	void		_ReservedMallocIO1();
virtual	void		_ReservedMallocIO2();

					BMallocIO(const BMallocIO &);
		BMallocIO	&operator=(const BMallocIO &);

		size_t		fBlockSize;
		size_t		fMallocSize;
		size_t		fPosition;
		size_t		fLength;
		char		*fData;
		int32		_reserved[2];
};

// ---------------------------------------------------------------- //

class BMemoryIO : public BPositionIO {
public:
					BMemoryIO(void *p, size_t len);
					BMemoryIO(const void *p, size_t len);
virtual				~BMemoryIO();

virtual	ssize_t		ReadAt(off_t pos, void *buffer, size_t size);
virtual	ssize_t		WriteAt(off_t pos, const void *buffer, size_t size);

virtual	off_t		Seek(off_t pos, uint32 seek_mode);
virtual off_t		Position() const;

private:

virtual	void		_ReservedMemoryIO1();
virtual	void		_ReservedMemoryIO2();

					BMemoryIO(const BMemoryIO &);
		BMemoryIO	&operator=(const BMemoryIO &);

		bool		fReadOnly;
		char		*fBuf;
		size_t		fLen;
		size_t		fPos;

		int32		_reserved[2];
};

#endif
