/*
 *   strstream.h
 *
 *   C++ IOStreams specialized for use with strings.
 *
 *           Copyright (c) 1991-1992, MetaWare Incorporated
 */

#ifndef __STRSTREAM_H
#define __STRSTREAM_H
#pragma push_align_members(64);

#c_include <iostream.h>

#pragma on(nodebug);

class strstreambuf : public streambuf {
private:
	void		init(char* __base, int __len,char* __put_origin);
	void*		(*alloc_fcn)(long);	// fcn used to allocate space
	void		(*free_fcn)(void*);	// fcn used to free space
	enum strflags	{
			  ignore_oflow =  0x01,	// Ignore overflow condition
			  auto_extend  =  0x02,	// Reallocate buffer when full
			  frozen       =  0x04	// Buffer frozen--inserts fail
			};
	long		_strflags;		// status flags
	int		next_min_alloc;

public: 
			strstreambuf();
			strstreambuf(int __min_size);
			strstreambuf(void* (*__alloc)(long),
					void (*__free)(void*));
			strstreambuf(char* __base, int __len,
					char* __put_origin = 0 );
			strstreambuf(unsigned char* __base, int __len,
					unsigned char* __put_origin = 0 );
			~strstreambuf();

	void		freeze(int __frozen=1);
	char*		str();
	virtual int	doallocate();
	virtual int	overflow(int __c);
	virtual int	underflow();
	virtual streambuf*
			setbuf(char*, int __len);
	virtual streampos
			seekoff(streamoff __offset, ios::seek_dir __dir,
					long __mode);

	};

class strstreambase : public virtual ios {
private:
	strstreambuf	buf; 
protected:	
			strstreambase(char* __base, int __len,
					char* __put_origin);
			strstreambase();
			~strstreambase();
public:
	strstreambuf*	rdbuf();
	};

class istrstream : public strstreambase, public istream {
public:
			istrstream(char* __base);
			istrstream(char* __base, int __len);
			~istrstream();
	};

class ostrstream : public strstreambase, public ostream {
public:
			ostrstream(char* __base, int __len,
					int __mode=ios::out);
			ostrstream();
			~ostrstream();
	char*		str();
	int		pcount();
	};


class strstream : public strstreambase, public iostream {
public:
			strstream();
			strstream(char* __base, int __len, int __mode);
			~strstream();
	char*		str();
	};

#pragma pop(nodebug);

#pragma pop_align_members();
#endif __STRSTREAM_H

/**          Copyright (c) 1991-1992, MetaWare Incorporated             **/
