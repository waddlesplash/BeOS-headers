/*
 *   iostream.h
 *
 *   C++ IOStreams and base classes.
 *
 *	   Copyright (c) 1991-1992, MetaWare Incorporated
 */

#ifndef __IOSTREAM_H
#define __IOSTREAM_H
#pragma push_align_members(64);

#c_include "memory.h"	
	// ANSI version of memory.h is shipped in C++ include directory
	// to avoid problem with UNIX's non-prototyped memory.h.
//   EOF and NULL may have been defined elsewhere.
#ifndef EOF
# define EOF (-1)
#endif

#ifndef NULL
# define NULL ((void*)(0))
#endif

#pragma Off(Behaved)
//   Extract a character from c, eliminating possibility of EOF.
#define zapeof(c) ((unsigned char)(c))

typedef long streampos;
typedef long streamoff;

class streambuf;
class ostream;



#pragma on(nodebug)
/*
 *   Class ios:
 *
 *      I/O Status values and access members.
 *
 */

class ios {

//   Public constants and enumerations.
public:
	// Stream status
	enum io_state   { 
	    goodbit	= 0x00,	// No error
	    eofbit	= 0x01,	// End-of-file reached
	    failbit     = 0x02,	// Insertion/extraction failed
	    range_errbit= 0x04,	// Value out of range
	    badbit	= 0x08,	// Access failed
	    hardfail    = 0x80 	// Unrecoverable error
	    };

	// Stream I/O mode
	enum open_mode  { 
	    in	     = 0x01,	// Input
	    out	     = 0x02,	// Output
	    ate	     = 0x04,	// Seek to EOF at open
	    app	     = 0x08,	// All operations append
	    trunc    = 0x10,	// Truncate file
	    nocreate = 0x20,	// Do not create file
	    noreplace= 0x40,	// Do not overwrite file
	    binary   = 0x80	// Binary file (no CR/LF translation).
	    };

	// Stream seek direction
	enum seek_dir   { 
	    beg	     = 0x00,	// Seek from beginning
	    cur	     = 0x01,	// Seek from current position
	    end	     = 0x02	// Seek from end
	    };

	// Formatting flags
	enum		{ 
	    skipws     = 0x01,	// Skip whitespace on input
				       
	    left       = 0x02,	// Padding location
	    right      = 0x04,
	    internal   = 0x08,	// Between sign and digits
					
	    dec	     = 0x10,	// Conversion base
	    oct	     = 0x20,
	    hex	     = 0x40,

	    showbase   = 0x80,	// Show base on output (eg. 0x)
	    showpoint  = 0x100,	// Print trailing zeros,decimals
	    uppercase  = 0x200,	// Use uppercase E,X
	    showpos    = 0x400,	// Print leading + for positive
				// Floating point notation
	    scientific = 0x800,	// 5.6789e3
	    fixed      = 0x1000,// 5678.9 
						    
	    unitbuf    = 0x2000,// Buffering--if set, flush after 
				// operation complete, not every character.
	    keepwidth  = 0x4000,// If set, width is NOT reset
				//  after each operation.
	    input_seps = 0x8000,// Allow digit separators on input.
	    char_width_1= 0x10000,// Char inserter ignores width setting.
	    fp_bases   = 0x20000,// Floating point inserters
				//  respect base setting.
	    stdio      = 0x40000// Flush stdout, stderr
	    };

	// Constants for use in second argument to setf().
	static const long basefield;		//  dec | oct | hex;
	static const long adjustfield;		//  left | right | internal;
	static const long floatfield;		//  scientific | fixed;

private:
	void		ios_check();
	// Privates for implementing allocated bits and words.
	static unsigned long     priv_nextbit;

			// NOTE:  AT&T and Borland both have this member as
			// static.  I don't see any reason for it to be static,
			// and I think that having it be static would cause
			// a significant waste of memory when user-defined
			// flag words are used.  See the documentation for
			// more on this.
	/*static*/ unsigned long     priv_nextword;

	long		priv_numuwords;
	union ios_user_union {
	    long	long_value;
	    void *	pointer_value;
	    };
	ios_user_union*   priv_userwords;
	int		priv_user_resize(long __newsize);


protected:

			ios(ios&);		// Declared but not defined.
	void		operator=(ios&);	// Causes error on copy.

			// Special flags
	enum		{ skipping=0x200,	// Skipping whitespace
			  tied=0x400		// Tied to another stream
			};
			
	streambuf*	bp;			// streambuf for this ios

			// Set status to __new_state
	void		setstate(int __new_state) {
				state |= (__new_state & 0xff);
				}

	long		state;		// Userbits and error state
	long		ispecial;	// Input special flags
	long		ospecial;	// Output special flags
	long		isfx_special;	// Input suffix special flags
	long		osfx_special;	// Output suffix special flags
	long		delbuf;

	long		x_flags;	// Formatting flags
	short		x_width;	// Field width
	short		x_precision;	// Precision
	char		x_fill;		// Fill character
	char		x_decimal;	// Decimal character
	char		x_digsep;	// Digit separator character
	short		x_sepfreq;	// Digit separator frequency
	ostream*	x_tie;		// Link to tied output stream

	static void     (*stdioflush)();	// Function to flush stdio

			// Does the real work of a constructor.
	void		init(streambuf* __buffer);

			ios();  // No initialization. Needed by
				//  multiple-inheritance versions.
	int		assign_private;
				// Needed by with_assign classes.

public:

			ios(streambuf* __buffer);

	virtual		~ios();

			// Read flags.
	long		flags() { return x_flags; }

			// Set flags, return previous.
	long		flags(long __newflags);

			// Set flags, return previous.
	long		setf(long __setbits, long __field);

			// Turn on bits set in __setbits, return previous value.
	long		setf(long __setbits);

			// Turn off bits set in __unsetbits, return prev.
	long		unsetf(long __unsetbits);

    			// Return current width.
	int		width() { return x_width; }

			// Set width, return previous value.
	int		width(int __new_width)  {
				int temp = x_width;
				x_width = __new_width;
				return temp;
				}

			// Read tie value.
	ostream*	tie() { return x_tie; }

  			// Tie to __tie_stream.
	ostream*	tie(ostream* __tie_stream);

			// Read fill value.
	char		fill() { return x_fill; }

			// Set fill char to __fillc, return previous.
	char		fill(char __fillc);

			// Read decimal character
	char		decimal_point() { return x_decimal; }

			// Set decimal char to __decimalc, return previous.
	char		decimal_point(char __decimalc) {
				char tmp = x_decimal;
				if (__decimalc !=0) x_decimal = __decimalc;
				return tmp;
				}

			// Read digit separator character
	char		digit_sep() { return x_digsep; }

			// Set digit separator char to __sepchar
	char		digit_sep(char __sepchar) {
				char temp = x_digsep;
				x_digsep = __sepchar;
				return temp;
				}

			// Read digit separator character
	int		digit_sep_freq() { return x_sepfreq; }

			// Set digit separator frequenct to __sepfreq
	int		digit_sep_freq(char __sepfreq) {
				int temp = x_sepfreq;
				x_sepfreq = __sepfreq;
				return temp;
				}

			// Read current precision
	int		precision() { return x_precision; }

			// Set precision to __prec, return previous.
	int		precision(int __prec);

			// Read state.
	int		rdstate() { return state; }

			// Typecast operator.
			// Return valid pointer only if state is not bad.
			operator void*() {
				if(state&(failbit|badbit|hardfail)) return NULL;
				else return this;
				}

			// Check state -- 0 if state is bad, 1 otherwise
	int		operator!()
				{ return (state&(failbit|badbit|hardfail)); }

			// Check for EOF
	int		eof()   { return (state&eofbit); }

			// Check for failed operation
	int		fail()  { return (state&(failbit|badbit|hardfail)); }

			// Check for unusable stream
	int		hard_fail()  { return (state&(hardfail)); }

			// Check for bad stream status
	int		bad()   { return (state&badbit); }

			// Check for range error status
	int		range_err()   { return (state&range_errbit); }

			// Check for good stream status
	int		good()  { return (state==0); }

			// Clear status, set to __init
			// Note: Only modifies standard state flags
	void		clear(int __init = 0) {
				state =  (__init&0xff) | (state&hardfail);
				}

			// Clear status, set to __init
			// Use this function to modify user-defined
			//  state flags.
			// This function is the same as clear(), except
			//  that it modifies all state flags.
	virtual void	set_err(int __init = 0) {
				state =  __init | (state&hardfail);
				}

			// Get pointer to associated streambuf
	streambuf*	rdbuf() { return bp;}

	// Members related to user-allocated bits and words.

			// Returns __index_num'th user-defined flag word.
	long &		iword(int __index_num);

			// Returns __index_num'th user-defined flag word.
	void* &		pword(int __index_num);

			// Returns a long with one previously-unused bit set.
			// This can be used as a user error flag.
	static long	bitalloc();

			// Returns a previously-unused index into an array of
			//  words available for use as format state variables.
			// For use by derived classes.

			// NOTE:  AT&T and Borland both have this function as
			// static.  I don't see any reason for it to be static,
			// and I think that having it be static would cause
			// a significant waste of memory when user-defined
			// flag words are used.  See the documentation for
			// more on this.
	/*static*/ int	xalloc();

			// Allows mixed use of stdio FILE*'s and streams.
			// Has an effect only the first time called.
	static void	sync_with_stdio();
	};



/*
 *   Class streambuf
 *
 *      Base stream-buffer class.
 *
 */

class streambuf {

private:
	void		check_stat();
	short		priv_alloc;	// TRUE == Delete buffer on setbuf
	short		priv_unbuf;	// TRUE == unbuffered stream
	char*		priv_base;	// Base of reserve area.
	char*		priv_ebuf;	// Byte after end of reserve area.
	char*		priv_pbase;	// Base of put area.
	char*		priv_pptr;	// Current position in put area.
	char*		priv_epptr;	// Byte after end of put area.
	char*		priv_gptr;	// Current position in get area.
	char*		priv_egptr;	// Byte after end of get area.
	char*		priv_eback;	// Lower bound of gptr -- space
					//  available for putback.

	int		priv_snextc();
	
protected:
			// Copy operators declared but not defined.
			// Declaring as protected causes compiler to produce
			//  an error if an assignment of a streambuf is 
			//  attempted.  This is desirable, as assignment
			//  of streambufs is not well-defined.
			streambuf(streambuf&);
	void		operator=(streambuf&);
	
			streambuf();
			streambuf(char* __buf, int __len);

	char*		base()  { return priv_base; }
	char*		pbase() { return priv_pbase; }
	char*		pptr()  { return priv_pptr; }
	char*		epptr() { return priv_epptr; }
	char*		gptr()  { return priv_gptr; }
	char*		egptr() { return priv_egptr; }
	char*		eback() { return priv_eback; }
	char*		ebuf()  { return priv_ebuf; }
	int		blen()  {
				return ((priv_ebuf>priv_base)
					? (priv_ebuf-priv_base)
					: 0);
				}

	void		setp(char*  __p, char*  __ep) {
				priv_pbase=priv_pptr=__p; priv_epptr=__ep;
				}

	void		setg(char*  __eb, char*  __g, char*  __eg) {
				priv_eback=__eb; priv_gptr=__g; priv_egptr=__eg;
				}

	void		pbump(int __num) {
				priv_pptr+=__num;
				}

	void		gbump(int __num) {
				priv_gptr+=__num;
				}

	void		setb(char* __b, char* __eb, int __a = 0 ) {
				if ( priv_alloc && priv_base ) delete priv_base;
				priv_base = __b;
				priv_ebuf = __eb;
				priv_alloc = __a;
				priv_unbuf = (__eb<=__b?1:0);
				}

	int		unbuffered() { return priv_unbuf; }

	void		unbuffered(int __unb) { priv_unbuf = (__unb!=0); }

	int		allocate() {
				if ( priv_base == 0 && !unbuffered() )
					return doallocate();
				else
					return 0;
				}

	virtual int	doallocate();
	
	virtual int	xsputn(const char* __str, int __num);
	virtual int	xsgetn(char* __str,int __num);

public :
	void		dbp(int __level=0);
	virtual int	overflow(int __c=EOF);
	virtual int	underflow();
	virtual int	pbackfail(int __c);
	virtual int	sync();
	
	virtual streampos
			seekoff(streamoff __offset, ios::seek_dir __dir,
				long __mode=ios::in|ios::out);
	virtual streampos
			seekpos(streampos __pos, long __mode=ios::in|ios::out);

	int		in_avail() {
				return (priv_gptr<priv_egptr
					? priv_egptr-priv_gptr
					: 0);
				}

	int		out_waiting() {
				if ( priv_pptr ) return priv_pptr-priv_pbase;
				else return 0;
				}

			// *** WARNING: sgetc does not bump the get pointer
	int		sgetc() {
				return (priv_gptr>=priv_egptr)
					? underflow()
					: zapeof(*priv_gptr);
				}

	int		snextc() {
				return (++priv_gptr>=priv_egptr)
					? priv_snextc()
					: zapeof(*priv_gptr);
				}

	int		sbumpc() {
				return ((priv_gptr>=priv_egptr
					  && underflow()==EOF)
					? EOF
					: zapeof(*priv_gptr++));
				}

	void		stossc() {
				if (priv_gptr>=priv_egptr) underflow();
				else ++priv_gptr;
				}

	int		sputbackc(char __c) {
				if (priv_gptr > priv_egptr) return EOF;
				if (priv_gptr > priv_eback ) {
					if ( *--priv_gptr == __c )
						return zapeof(__c);
					else return zapeof(*priv_gptr=__c);
					}
				else {
					return pbackfail(__c);
					}
				}

	int		sputc(int __c) {
				return (priv_pptr>=priv_epptr)
					? overflow((int)zapeof(__c))
					: zapeof(*priv_pptr++=__c);
				}

	int		sputn(const char* __str,int __num) {
				if ( __num <= (priv_epptr-priv_pptr) ) {
					memcpy(priv_pptr, __str, __num);
					pbump(__num);
					return __num;
					}
				else {
					return xsputn(__str, __num);
					}
				}

	int		sgetn(char* __str,int __num) {
				if ( __num <= (priv_egptr-priv_gptr) ) {
					memcpy(__str,(const char*)priv_gptr,
					       __num);
					gbump(__num);
					return __num;
					}
				else {
					return xsgetn(__str, __num);
					}
				}

	virtual streambuf*
			setbuf(char* __buf, int __len);

	streambuf*	setbuf(unsigned char* __buf, int __len) {
				return (setbuf((char*)__buf, __len));
				}

	virtual		~streambuf();
	};



class istream : virtual public ios {

private:
	int		priv_gcount;		// Keep track of # of chars
						//  last extracted.
	void		ischeck_state();
	void		_doget(char* __c);	// Actually does a get.

protected:
	int		do_ipfx(int __noskipws);
	void		do_isfx();
	int		eatwhite(void);
			istream();
			
public:
			istream(streambuf *__buffer);
	virtual		~istream();
	
	int		ipfx(int __noskipws=0) {
				if ( __noskipws?(ispecial&~skipping):ispecial) {
					return do_ipfx(__noskipws);
					}
				else return 1;
				}

	void		isfx() {
				if (isfx_special) do_isfx();
				}

	istream&	seekg(streampos __position);
			
	istream&	seekg(streamoff __offset, ios::seek_dir __dir);

			// Returns the current offset into the get buffer.
	streampos	tellg();

			// For manipulators.
	istream&	operator>> (istream& (*__fcn)(istream&)) {
				return (*__fcn)(*this);
				}

			// For manipulators.
	istream&	operator>> (ios& (*__fcn)(ios&) );

	istream&	operator>>(char *__cp);
	istream&	operator>>(unsigned char *__ucp);
	istream&	operator>>(unsigned char &__ucr);
	istream&	operator>>(char& __cr);
	istream&	operator>>(short& __sr);
	istream&	operator>>(int& __ir);
	istream&	operator>>(long& __lr);
	istream&	operator>>(unsigned short& __usr);
	istream&	operator>>(unsigned int& __uir);
	istream&	operator>>(unsigned long& __ulr);
	istream&	operator>>(float& __fr);
	istream&	operator>>(double& __dr);
	istream&	operator>>(long double& __ldr);
	istream&	operator>>(streambuf* __sp);

			// Read and extract characters ending in delim,
			//  up to a maximum of lim characters.
			// delim IS NOT stored in buffer.
	istream&	get(char* __buffer, int __lim, char __delim='\n');
	istream&	get(unsigned char* __buffer, int __lim, char __delim='\n');
	istream&	get(char* __buffer, int __lim, char *__delims);
	istream&	get(unsigned char* __buffer, int __lim, char *__delims);

			// Read and extract characters ending in delim,
			//  up to a maximum of lim characters.
			// delim IS stored in buffer if space allows.
	istream&	getline(char* __buffer, int __lim, char __delim='\n');
	istream&	getline(unsigned char* __buffer,int __lim, char __delim='\n'); 
	istream&	getline(char* __buffer, int __lim, char *__delims);
	istream&	getline(unsigned char* __buffer,int __lim, char *__delims); 
			// Read and extract character.
	istream&	get(streambuf& __sb, char __delim ='\n');
	istream&	get(unsigned char& __c);
	istream&	get(char& __c);
	int		get();

			// Read next character, but don't extract.
	int		peek() {
				if ( ipfx(-1) ) return rdbuf()->sgetc();
				else return EOF;
				}

			// Extract and trash n characters, stopping
			//  if delim is encountered.
	istream&	ignore(int __num=1,int __delim=EOF);

	istream&	read(char* __buf,int __num);
	istream&	read(unsigned char* __buf,int __num) {
				return read((char*)__buf,__num);
				}
	int		gcount() { return priv_gcount; }
	istream&	putback(char __c);
	int		sync()  { return rdbuf()->sync(); }
	};



class ostream : virtual public ios {

protected:
	int		do_opfx();
	void		do_osfx();
			ostream();

public:
			ostream(streambuf *__sbp);
	virtual		~ostream();

	int		opfx() {
				if (!good()) return 0;
				else if (ospecial) return do_opfx();
				else return 1;
				}

	void		osfx() {
				if (osfx_special) do_osfx();
				}

	ostream&	flush();

	ostream&	seekp(streampos __pos);

	ostream&	seekp(streamoff __off, ios::seek_dir __dir);

	streampos	tellp();

	ostream&	put(char __c);

	ostream&	operator<<(char __c) {
				return put(__c);
				}

	ostream&	operator<<(unsigned char __uc) {
				return put(__uc);
				}

	ostream&	operator<<(const char* __ccp);

	ostream&	operator<<(int __i);
				
	ostream&	operator<<(long __l);

	ostream&	operator<<(double __d);

	ostream&	operator<<(long double __ld);

	ostream&	operator<<(float __f);

	ostream&	operator<<(unsigned int  __ui);

	ostream&	operator<<(unsigned long __ul);

	ostream&	operator<<(void* __vp);

	ostream&	operator<<(streambuf* __sbp);

	ostream&	operator<<(short __s);

	ostream&	operator<<(unsigned short __us);

			// For manipulators.
	ostream&	operator<<(ostream& (*__fcn)(ostream&)) {
				return (*__fcn)(*this);
				}

			// For manipulators.
	ostream&	operator<<(ios& (*__fcn)(ios&) );

	ostream&	write(const char* __str,int __num);
	ostream&	write(const unsigned char* __str, int __num) {
				return write((const char*)__str,__num);
				}
	};


class iostream : public istream, public ostream {
protected:
			iostream();

public:
			iostream(streambuf* __sbp);
	virtual		~iostream();
	};


class istream_withassign : public istream {
public:
				istream_withassign();
	virtual			~istream_withassign();
	istream_withassign&	operator=(istream&);
	istream_withassign&	operator=(streambuf*);
	};


class ostream_withassign : public ostream {
public:
				ostream_withassign();
	virtual			~ostream_withassign();
	ostream_withassign&	operator=(ostream&);
	ostream_withassign&	operator=(streambuf*);
	};


class iostream_withassign : public iostream {
public:
				iostream_withassign();
	virtual			~iostream_withassign();
	iostream_withassign&	operator=(ios&);
	iostream_withassign&	operator=(streambuf*);
	};
#pragma pop(nodebug)


extern istream_withassign cin;
extern ostream_withassign cout;
extern ostream_withassign cerr;
extern ostream_withassign clog;
#ifdef _MSDOS
// Additional standard streams provided under DOS
extern ostream_withassign caux;
extern ostream_withassign cprn;
#endif

extern ostream&		endl(ostream& os);
extern ostream&		ends(ostream& os);
extern ostream&		flush(ostream& os);
extern ios&		dec(ios& iosr);
extern ios&		oct(ios& iosr);
extern ios&		hex(ios& iosr);
extern istream&		ws(istream& is);


#pragma Pop(Behaved)
#pragma pop_align_members();
#endif


/**	  Copyright (c) 1991-1992, MetaWare Incorporated	     **/
