/*
 *   fstream.h
 *
 *   C++ IOStreams specialized for use with files.
 *
 *           Copyright (c) 1991-1992, MetaWare Incorporated
 */

#ifndef __FSTREAM_H
#define __FSTREAM_H
#pragma push_align_members(64);

#c_include <iostream.h>


#pragma on(nodebug)
/*
 *   Class filebuf:
 *
 *      streambuf specialized for use with files.
 *      Supports associated file descriptor, seek, read and write
 *      to external file.
 *
 */

class  filebuf : public streambuf {

private:
	void		fb_checkstate();

protected:
	int		xfd;		// File descriptor for this filebuf.
	int		mode;		// Open mode of file descriptor.
	char		opened;		// TRUE == xfd is open.
	streampos	last_seek;	// Position after last seek.
	char* 		in_start;
	int		last_op();	// ???  Not implemented.
	char		lahead[2];	// Input buffer for unbuffered filebufs.
	int		phy_in_avail(); // Physical characters remaining

public:
	static const int openprot;	// Default permissions = 0644(rw,r,r)

	void		fb_dbp(int __level);

			filebuf();	// Buffered, no handle, not open.

					// Buffered, __handle already open.
			filebuf(int __handle);

					// Buffered, __handle already open.
			filebuf(int __handle, char* __buf, int __len);

	int		is_open() { return opened; }
	int		fd() { return xfd; }

					// Open file.
	filebuf*	open(const char *__pathname, long __mode,
				long __prot=filebuf::openprot);

					// Use __handle, fail if already open.
	filebuf*	attach(int __handle);

					// Sync and close file.
	filebuf* 	close();

					// Sync and close file.
			~filebuf();

// virtuals
	virtual int	overflow(int=EOF);
	virtual int	underflow();
	virtual int	sync();
	virtual streampos
			seekoff(streamoff __offset, ios::seek_dir __dir,
				long __mode);
	virtual streambuf*
			setbuf(char* __buf, int __len);
	};



/*
 *   Class fstreambase:
 *
 *      Base class for input/output functions on filebufs.
 *
 */

class fstreambase : virtual public ios { 

private:
	void		check_stat();
	filebuf		buf;

protected:
	void		verify(int);

public:
			fstreambase();
	
			fstreambase(const char* __name, long __mode,
					long __prot=filebuf::openprot);
			fstreambase(int __handle);
			fstreambase(int __handle, char* __buf, int __len);
			~fstreambase();
	void		open(const char* __name, long __mode, 
					long __prot=filebuf::openprot);
	void		attach(int __handle);
	void		close();
	filebuf*	setbuf(char* __buf, int __len);
	filebuf*	rdbuf() { return &buf; }
	};


/*
 *   Class ifstream:
 *
 *      istream specialized for files.
 *
 */

class ifstream : public fstreambase, public istream {
public:
			ifstream();
			ifstream(const char* __name, long __mode=ios::in,
					long __prot=filebuf::openprot);
			ifstream(int __handle);
			ifstream(int __handle, char* __buf, int __len);
			~ifstream();

	filebuf*	rdbuf() { return fstreambase::rdbuf(); }
	void		open(const char* __fname, long __mode=ios::in, 
					long __prot=filebuf::openprot);
	};


/*
 *   Class ofstream:
 *
 *      ostream specialized for files.
 *
 */

class ofstream : public fstreambase, public ostream {
public:
			ofstream();
			ofstream(const char* __name, long __mode=ios::out,
					long __prot=filebuf::openprot);
			ofstream(int __handle);
			ofstream(int __handle, char* __buf, int __len);
			~ofstream();

	filebuf*	rdbuf() { return fstreambase::rdbuf(); }
	void		open(const char* __name, long __mode=ios::out, 
					long __prot=filebuf::openprot);
	};


/*
 *   Class fstream:
 *
 *      iostream specialized for files.
 *
 */

class fstream : public fstreambase, public iostream {
public:
			fstream();
	
			fstream(const char* __name, long __mode,
					long __prot=filebuf::openprot);
			fstream(int __handle);
			fstream(int __handle, char* __buf, int __len);
			~fstream();
	filebuf*	rdbuf() { return fstreambase::rdbuf(); }
	void		open(const char* __name, long __mode, 
				long __prot=filebuf::openprot);
	};
#pragma pop(nodebug)


#pragma pop_align_members();
#endif // __FSTREAM_H


/**          Copyright (c) 1991-1992, MetaWare Incorporated             **/
