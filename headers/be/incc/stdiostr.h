/*
 *   stdiostr.h
 *
 *   C++ IOStreams specialized for use in conjunction with
 *   stdio FILEs.
 *
 *           Copyright (c) 1991-1992, MetaWare Incorporated
 */

#ifndef __STDIOSTREAM_H
#define __STDIOSTREAM_H
#pragma push_align_members(64);

#c_include <iostream.h>
#c_include <stdio.h>

#pragma on(nodebug)

/*
 *  Class stdiobuf is provided to support concurrent use of the C stdio
 *  and C++ iostreams standard input and output streams.  Using stdiobufs
 *  can cause a severe degradation in performance.  It should not be
 *  necessary to use stdiobufs if the standard output streams are set for
 *  unit buffering (ios::unitbuf) and all input operations on cin are
 *  line-oriented on a cooked input stream.
 *
 *  Use of class stdiobuf should be avoided whenever possible.
 */

class stdiobuf : public streambuf {

private:
	FILE*		_fp;			
	char		_tmp_buf[2];

public:
	virtual int	overflow(int=EOF);
	virtual int	underflow();
	virtual int	sync();
	virtual streampos
			seekoff(streamoff,ios::seek_dir,long);
	virtual int	pbackfail(int __c);

			stdiobuf(FILE* __fp);
	FILE*		stdiofile() { return _fp; }
	virtual		~stdiobuf();
	};

class stdiostream : public ios {
private:
	stdiobuf	_buf;

public:
			stdiostream(FILE* __fp);
			~stdiostream();
	stdiobuf*	rdbuf() { return &_buf; }
	};

#pragma pop(nodebug)


#pragma pop_align_members();
#endif __STDIOSTREAM_H

/**          Copyright (c) 1991-1992, MetaWare Incorporated             **/
