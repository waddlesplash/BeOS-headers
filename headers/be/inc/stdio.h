/*
 *   stdio.h -- ANSI 
 *
 *   Standard input/output facilities.
 *
 *           Copyright (c) 1990, 1993 MetaWare Incorporated
 */

#ifndef _STDIO_H
#define _STDIO_H
#pragma push_align_members(64);


#ifdef __CPLUSPLUS__
extern "C" {
#endif

#if (_I286 || _VMS)
    #define BUFSIZ	   (512)
#elif _R3000    
    #define BUFSIZ	  (4096)
#elif _IBMESA || (_BSD && _I386)
    #define BUFSIZ	  (8192)
#elif _IBM370 || (_AIX && _I386)
    #define BUFSIZ	  (4096)
#else
    #define BUFSIZ	  (1024)
#endif

#define EOF (-1)

#ifndef NULL
    #define NULL ((void	*)0)
#endif

#ifndef _SIZET_H
#include <sizet.h>
#endif

#ifndef _UNICHAR_DEFINED
    typedef unsigned short _UNICHAR;
    #define _unichar _UNICHAR
    #define _UNICHAR_DEFINED
#endif

typedef long fpos_t;

/* maximum number of open files */
#if _IBMESA || (_BSD && _I386)
    #define FOPEN_MAX	(64)
#elif _IBM370 || (_AIX && _I386)
    #define FOPEN_MAX	(200)
#elif ((_ATT || _ATT4)	&& _I386 || _SUN || _MC68 || _UPA)
    #define FOPEN_MAX	(60)
#elif _VMS
    #define FOPEN_MAX	(20)
#elif _NEXT
    #define FOPEN_MAX	(256)
#elif _HOBBIT
    #define FOPEN_MAX	(130)
#elif _SOL
    /* solaris begins with an initial allocation of 20
     * entries in the IOB, and then mallocs 40 more if
     * this value is exceeded
     */
    #define FOPEN_MAX	(60)
    #define _FOPEN_MAX1 (20)
#else
    #define FOPEN_MAX	(50)
#endif
#define _NFILE FOPEN_MAX


#if _NEXT
    #define FILENAME_MAX (1024)
#else
    #define FILENAME_MAX (255)  /* max name len guaranteed */
#endif

/*
 * the FILE table (_IOB) is structured in one of three ways:
 *   _IOB_FIXED
 *       a fixed-size array, with size FOPEN_MAX
 *   _IOB_EXTENSION
 *       a fixed-size array, but may also contain a second array,
 *       not contiguous to the first, for expansion if required.
 *       Overall size is still FOPEN_MAX, but the size of the first
 *       table is _FOPEN_MAX1.
 *   _IOB_LIST
 *       the _IOB is implemented as a linked list, with the first three
 *       entries static, but all remaining entries allocated with malloc,
 *       and linked together with link fields
 */

#define		_IOB_FIXED	1
#define		_IOB_EXTENSION	2
#define		_IOB_LIST	3

#if _SOL
#    define _IOB_FORMAT     _IOB_EXTENSION
#elif _HOBBIT && defined(_REENTRANT)
#    define _IOB_FORMAT     _IOB_LIST
#else
#    define _IOB_FORMAT     _IOB_FIXED
#endif

/*  _IOB semantics:
 *
 *  _flag semantics:
 *    _IOFBF, _IONBF, _IOLBF:
 *        specify buffering.  Note that _IOFBF is 0, and thus,
 *        no flag implies full buffering.
 *
 *    _IOREAD, _IOWRT, _IORW:
 *        set at open time as follows:
 *            _IOREAD		open "r"
 *            _IOWRT		open "w"
 *	      _IORW		open "r+", "w+", "a+"
 *        open update (the "+" guys): 
 *            _IOREAD and _IOWRT are or'd in for read/write 
 *            operations.  At seek time, the buffer is flushed,
 *            if necessary, and the _IOREAD/_IOWRT flags are
 *            cleared.  Note that the user must issue an
 *            intervening seek before switching between read/
 *            write operations.  Thus, at seek time, the buffer
 *            is cleared, and the only remaining flag is _IORW.
 *            _IORW is set at open time, and remains set until
 *            the file is closed.
 *        open append:
 *            The append requirement is passed to the system
 *            open routine.  Thus, all writes are automatically
 *            appended, and no record of the append status is
 *            kept in the _IOB.  Note that DOS does not have
 *            an open append system call, and thus we track
 *            file position in the _FIOSEEKEOF flag.
 *        open read/write:
 *            _IOREAD/_IOWRITE are set at open time, and remain
 *            set until the file is closed.
 *
 *     _IOMYBUF
 *        if set, then the buffer allocated at open time
 *        belongs to the i/o system (as opposed to the user), 
 *        and it's the i/o system's responsibility to free
 *        the buffer at close time.
 *
 *  _cnt semantics:
 *    if _IOREAD
 *        _cnt specifies the number of characters remaining
 *        to be read in the buffer.
 *    else if _IOWRT
 *        _cnt specifies the number of unused bytes remaining
 *        in the buffer.
 *    endif
 *
 *  _base semantics:
 *    pointer to beginning of buffer.  This value remains
 *    constant after open.
 *
 *  _ptr semantics:
 *    if _IOREAD
 *       _ptr specifies the location of the next byte to be read.
 *    else if _IOWRT
 *       _ptr specifies the location of the next unused byte.
 *    endif
 *
 *  _file semantics:
 *    contains the low-level system file handle.
 *
 *  miscellaneous:
 *    to determine buffer size, one of the following must 
 *    be present:
 *      _bufsiz   	size of buffer (_IOB_BUFSIZ)
 *      _bufendp	pointer to byte following buffer (_IOB_BUFENDP)
 *      _bufendtab[]	a table of bufendp pointers (_IOB_BUFENDTAB)
 *      _bufsiz & _bufendp both of the first two (_IOB_BUFSIZ_ENDP)
 *
 */


#if _MSDOS || _OS2 || _MSNT || (_I860 && _ATT) || _AM29K
    #define _TEXTFILES 1
#else
    #define _TEXTFILES 0
#endif

#if _MSDOS || _OS2 || _MSNT || (_I860 && _ATT)
    #define _NEWLINE_XLATE 1
#else
    #define _NEWLINE_XLATE 0
#endif

#if _AM29K
    #define _SYSTEM_NEWLINE_XLATE 1
#else
    #define _SYSTEM_NEWLINE_XLATE 0
#endif

/* specify _WRITEAPPEND if we must supply our own APPEND on WRITE */
/* This is required on MSDOS, as there is no OPEN APPEND */
#if _MSDOS || _OS2 || _MSNT
    #define _WRITEAPPEND 1
#else
    #define _WRITEAPPEND 0
#endif

#if _MSDOS || _OS2 || _MSNT
    #define _FLUSH_SYSCALL_REQUIRED 1
#else
    #define _FLUSH_SYSCALL_REQUIRED 0
#endif


/* minimum file descriptor for user stream */
#if _MSDOS
    #define _MIN_USER_STREAM 5
#else
    #define _MIN_USER_STREAM 3
#endif

/*
 *  extra information provided as follows:
 *    _FIOAPPEND	required by WRITE so SEEK END may be done
 *                      if required.
 *    _FIOTEXT		required by READ/WRITE so CR/LF translation
 *                      may be done if required.
 *    _FIOSEEKEOF	not required, but improves response for
 *                      DOS (saves a SEEK END on every WRITE APPEND)
 */

typedef enum {
    _FIOAPPEND =   	0x0001,         /* open append */
    #if _TEXTFILES
	_FIOTEXT =     	0x0002,         /* text file */
    #endif
    #if _WRITEAPPEND
	_FIOSEEKEOF =   0x0004,         /* last SEEK was to EOF */
    #endif
    __ansi_cant_end_enums_in_comma	/* Must be here else isn't -Hansi. */
    } _iob_fioflag_t;

/* support for ungetc */
typedef struct {
    int _iob_cnt;        	/* _cnt, copied from _iob  */
    int _bufsiz;        	/* ungetc buffer size */
    unsigned char *_base;	/* ungetc pointer to buffer */
    unsigned char *_ptr;	/* ungetc pointer to current byte */
    } _iob_unget_t;


#define _IOB_BUFSIZ 	1
#define _IOB_BUFENDP    2
#define _IOB_BUFENDTAB  3
#define _IOB_BUFSIZ_ENDP 4

#if _BSD && _I386	/* OSF/1 386 */

    #define _IOB_BUFTYP _IOB_BUFSIZ_ENDP
    #define _IOB_CHAR_FLAG 0

    typedef int _iob_cnt_t;
    typedef unsigned char _iob_ptr_t;
    typedef int _bufsiz_t;
    typedef short _iob_flag_t;
    typedef short _iob_file_t;

    typedef struct {
	_iob_cnt_t	_cnt;
	_iob_ptr_t	*_ptr;
	_iob_ptr_t	*_base;
	_bufsiz_t	_bufsiz;
	_iob_flag_t	_flag;
	_iob_file_t	_file;
	int		_unused[3];	/* Believe it or not. */
	unsigned char   *_bufendp;
	} FILE;

#elif _BSD || _SUN || _EPI || _ISIS || _NEXT || _NEWS 

    #define _IOB_BUFTYP _IOB_BUFSIZ

    #define _IOB_CHAR_FLAG 0

    typedef int _iob_cnt_t;
    typedef char _iob_ptr_t;
    typedef int _bufsiz_t;
    typedef short _iob_flag_t;
    typedef char _iob_file_t;

    typedef struct {
	_iob_cnt_t _cnt;
	_iob_ptr_t *_ptr;
	_iob_ptr_t *_base;
	_bufsiz_t _bufsiz;
	_iob_flag_t _flag;
	_iob_file_t _file;
	char _unused[1];    /* in case align_members is off */
	} FILE;

#elif _IBMESA	/* AIX and ESA have ptr/cnt switched. */

    #define _IOB_BUFTYP _IOB_BUFSIZ_ENDP

    #define _IOB_CHAR_FLAG 0

    typedef int _iob_cnt_t;
    typedef unsigned char _iob_ptr_t;
    typedef short _iob_flag_t;
    typedef short _iob_file_t;
    typedef int _bufsiz_t;

    /* Both bufsiz and bufendp are included in the iob. */
    typedef struct {
	_iob_cnt_t _cnt;
	_iob_ptr_t *_ptr;
	_iob_ptr_t *_base;
	_bufsiz_t _bufsiz;
	_iob_flag_t _flag;
	_iob_file_t _file;
#if defined(_REENTRANT) || defined(_THREAD_SAFE)	/* IBM's names here. */
	int _unused[2];
	void *_lock;			/* lock for thread safe library */
#else
	int _unused[3];  /* in case align_members is off */
#endif
	_iob_ptr_t *_bufendp;
	} FILE;

#elif _AIX

    #define _IOB_BUFTYP _IOB_BUFENDP

    #define _IOB_CHAR_FLAG 0

    typedef int _iob_cnt_t;
    typedef unsigned char _iob_ptr_t;
    typedef short _iob_flag_t;
    typedef short _iob_file_t;

    typedef struct {
	_iob_ptr_t *_ptr;
	_iob_cnt_t _cnt;
	_iob_ptr_t *_base;
	_iob_ptr_t *_bufendp;
	_iob_flag_t _flag;
	_iob_file_t _file;
	int _unused[3];  /* in case align_members is off */
	} FILE;

#elif _R3000  /* MIPS R2000/R3000 */

    #define _IOB_BUFTYP _IOB_BUFENDTAB

    #define _IOB_CHAR_FLAG 1

    typedef int _iob_cnt_t;
    typedef unsigned char _iob_ptr_t;
    typedef char _iob_flag_t;
    typedef char _iob_file_t;

    extern _iob_ptr_t *_bufendtab[];

    typedef struct {
	_iob_cnt_t _cnt;
	_iob_ptr_t *_ptr;
	_iob_ptr_t *_base;
	_iob_flag_t _flag;
	_iob_file_t _file;
	char _unused[2];    /* in case align_members is off */
	} FILE;

#elif _HP9000

    #define _IOB_BUFTYP _IOB_BUFENDTAB

    #define _IOB_CHAR_FLAG 1

    typedef int _iob_cnt_t;
    typedef char _iob_ptr_t;
    typedef short int _iob_flag_t;
    typedef char _iob_file_t;

    extern _iob_ptr_t *_bufendtab[];

    typedef struct {
	_iob_cnt_t _cnt;
	_iob_ptr_t *_ptr;
	_iob_ptr_t *_base;
	_iob_flag_t _flag;
	_iob_file_t _file;
	char _unused[1];    /* in case align_members is off */
	} FILE;

#elif _HOBBIT
    #define _IOB_BUFTYP _IOB_BUFSIZ

    #define _IOB_CHAR_FLAG 0

    typedef int _iob_cnt_t;
    typedef char _iob_ptr_t;
    typedef int _bufsiz_t;
    typedef int _iob_flag_t;
    typedef int  _iob_file_t;

    #if (_IOB_FORMAT == _IOB_LIST)

	/* for reentrant hobbit, the _iob is a linked list.  Because the 
	   _iob-parallel table concept doesn't work, we include the fields
	   that would normally be in the parallel tables directly into
	   the _iob entry definition.
	*/
	typedef struct _iob_ent_type {
	    _iob_cnt_t _cnt;
	    _iob_ptr_t *_ptr;
	    _iob_ptr_t *_base;
	    _bufsiz_t _bufsiz;
	    _iob_flag_t _flag;
	    _iob_file_t _file;
	    _iob_unget_t _iob_unget;
	    _iob_fioflag_t _iob_fioflag;
	    struct _iob_ent_type *_link;  /* link to next FILE structure */
	    } FILE;
    #else
	typedef struct {
	    _iob_cnt_t _cnt;
	    _iob_ptr_t *_ptr;
	    _iob_ptr_t *_base;
	    _bufsiz_t _bufsiz;
	    _iob_flag_t _flag;
	    _iob_file_t _file;
	    } FILE;
    #endif

#elif _ATT || _ATT4 || _SOL
    #if _ATT && _I860
	#define _IOB_BUFTYP _IOB_BUFENDTAB

	#define _IOB_CHAR_FLAG 0

	typedef int _iob_cnt_t;
	typedef char _iob_ptr_t;
	typedef short _iob_flag_t;
	typedef char _iob_file_t;

	extern _iob_ptr_t *_bufendtab[];

	typedef struct {
	    _iob_cnt_t _cnt;
	    _iob_ptr_t *_ptr;
	    _iob_ptr_t *_base;
	    _iob_flag_t _flag;
	    _iob_file_t _file;
	    char _unused[1];    /* in case align_members is off */
	    } FILE;

    #else

	#define _IOB_BUFTYP _IOB_BUFENDTAB

	#define _IOB_CHAR_FLAG 1

	typedef int _iob_cnt_t;
#if _ATT4 && _I860
	typedef unsigned char _iob_ptr_t;
#else
	typedef char _iob_ptr_t;
#endif
	typedef unsigned char _iob_flag_t;
	typedef unsigned char _iob_file_t;

	extern _iob_ptr_t *_bufendtab[];

	    /* _STDIO_REVERSE appears in AT&Ts stdio.h.  We have it here
	       in case they have some other include file that activates it */
	typedef struct {
	    #if _STDIO_REVERSE
		_iob_ptr_t *_ptr;
		_iob_cnt_t _cnt;
	    #else
		_iob_cnt_t _cnt;
		_iob_ptr_t *_ptr;
	    #endif
	    _iob_ptr_t *_base;
	    _iob_flag_t _flag;
	    _iob_file_t _file;
	    char _unused[2];    /* in case align_members is off */
	    } FILE;
    #endif

    #if _SOL
	/* an extra 60 entries of iob and bufendtab, if needed */
	extern FILE *_iob_more;
	extern _iob_ptr_t **_bufendtab_more;
    #endif

#elif _MSDOS || _OS2

    #define _IOB_BUFTYP _IOB_BUFENDTAB

    #define _IOB_CHAR_FLAG 0

    typedef int _iob_cnt_t;
    typedef char _iob_ptr_t;
    typedef short int _iob_flag_t;
    typedef char _iob_file_t;

    extern _iob_ptr_t *_bufendtab[];

    typedef struct {
        _iob_ptr_t *_ptr;
        _iob_cnt_t _cnt;
        _iob_ptr_t *_base;
        _iob_flag_t _flag;
        _iob_file_t _file;
        char _unused[5];    /* in case align_members is off */
        } FILE;

#elif _MSNT
    #define _IOB_BUFTYP _IOB_BUFENDTAB
    #define _IOB_CHAR_FLAG 1
    typedef int _iob_cnt_t;
    typedef char _iob_ptr_t;
    extern _iob_ptr_t *_bufendtab[];
    typedef struct {
      _iob_ptr_t *_ptr;
      _iob_cnt_t   _cnt;
      _iob_ptr_t *_base;
      int   _flag;
      int   _file;
      int   _charbuf;		/* not used */
      int   _bufsiz;		/* not used */
      int   _tmpnum;		/* not used */
      } FILE;
#elif _UPA
    #define _IOB_BUFTYP _IOB_BUFENDTAB

    #define _IOB_CHAR_FLAG 1

    typedef int _iob_cnt_t;
    typedef unsigned char _iob_ptr_t;
    typedef unsigned short _iob_flag_t;
    typedef unsigned short _iob_file_t;

    extern _iob_ptr_t *__bufendtab[];

    typedef struct {
	_iob_cnt_t _cnt;
	_iob_ptr_t *_ptr;
	_iob_ptr_t *_base;
	_iob_flag_t _flag;
	_iob_file_t _file;
	} FILE;

#else
    #error Error in compilation:  OS not specified: __FILE__, line __LINE__.
#endif

/* ordinal for _flag */
enum {
    _IOFBF =		0x0000,		/* full	bufferring */
    _IOREAD =		0x0001,		/* reading */
    _IOWRT =		0x0002,		/* writing */
    _IONBF =		0x0004,		/* no buffering	*/
    _IOMYBUF =		0x0008,		/* free	buffer on close */
    _IOEOF =		0x0010,		/* eof reached */
    _IOERR =		0x0020,		/* error occurred */
    #if _IOB_CHAR_FLAG
	_IOSTRG =       0x0040,         /* string buffering */
	_IOLBF =	0x0040,		/* line buffering */
	_IORW =		0x0080,		/* read/write enabled */
    #else
	_IOSTRG =     	0x0040,         /* string buffering */
	_IOLBF =	0x0080,		/* line	buffering */
	_IORW =		0x0100,		/* read/write enabled */
    #endif
    _IOSHRMEM =		0x0200		/* entry and buffer in shared mem? */
    };

/* ANSI requires these to be macros: */
#define _IOFBF	_IOFBF
#define _IOLBF	_IOLBF
#define _IONBF	_IONBF
#if _ATT
    #define L_tmpnam (25)	/* length of file tmpnam string: system V */
#elif defined(_IBMESA) || defined(_UPA) || defined(_SUN)
    #define L_tmpnam (sizeof(_P_tmpdir)+15)    
#else
    #define L_tmpnam (18)	/* length of file tmpnam string */
#endif

#if defined(_REENTRANT) && !(_MSNT || _OS2)
    #ifndef _STATIC_H
	#include <static.h>
    #endif
#else
    /* only _iob.c need be recompiled if FOPEN_MAX or BUFSIZ is changed */
    extern int _fopen_max;
    extern int _bufsiz_dflt;

    /* associated IOB tables */
    extern char *_iob_tmpnam[];		/* ptr to tmp filename */
    extern _iob_fioflag_t _iob_fioflag[];	/* _FIO... flags */
    extern _iob_unget_t _iob_unget[];	/* support for ungetc */
    #if _SYSTEM_NEWLINE_XLATE
	/* file position for start of buffer for READ */
	extern long _iob_bufpos[];
    #endif
    #if (_IOB_FORMAT == _IOB_LIST)
	extern FILE *_iob_head;
    #endif
    #if _ATT4 || __ATTSTDC || _UPA	/* UNIX 5v4 uses __iob */
        #define _IOB __iob
    #else
        #define _IOB _iob
    #endif
    extern FILE _IOB [];
#endif

#define stdin	(&_IOB[0])
#define stdout	(&_IOB[1])
#define stderr	(&_IOB[2])

#if _MSDOS && __HIGHC__
#    define stdaux (&_IOB[3])
#    define stdprn (&_IOB[4])
#endif

#if _MSDOS || _OS2 || _MSNT
#    define _P_tmpdir "\\"
#elif _UPA || _SUN
#    define _P_tmpdir "/usr/tmp/"
#elif _HOBBIT
#    define _P_tmpdir ""
#else
#    define _P_tmpdir "/tmp/"
#endif

#if __HIGHC__
    #define P_tmpdir _P_tmpdir
#endif

#if _UPA
#define TMP_MAX  (17576)
#else
#define TMP_MAX  (1000)  /* min number	of unique tmpnames */
#endif

#ifndef SEEK_SET
#define SEEK_SET (0)	  /*From_beginning*/
#define SEEK_CUR (1)	  /*From_current*/
#define SEEK_END (2)	  /*From_end*/
#endif

extern	int remove(const char *__pathname);
extern	int rename(const char *__old, const char *__new);
extern	FILE *tmpfile(void);
extern	char *tmpnam(char *__s);
extern	int fclose(FILE	*__stream);
extern	int fflush(FILE	*__stream);
extern	FILE *fopen(const char *__pathname, const char *__type);
#if  !(_MSDOS || _MSNT || _OS2 || _VMS)
    extern FILE *fdopen(int __fd, const char *__type);
#endif
extern	FILE *freopen(const char *__pathname, const char *__type, FILE *__stream);
extern	void setbuf(FILE *__stream, char *__buf);
extern	int setvbuf(FILE *__stream, char *__buf, int __type, size_t __size);
extern	size_t fread
	 (void *__ptr, size_t __size, size_t __nelem, FILE *__stream);
extern	size_t fwrite
	 (const	void *__ptr, size_t __size, size_t __nelem, FILE *__stream);
extern	int fgetc(FILE *__stream);
extern	int _filbuf(FILE *__stream);

#undef	getc
extern	int getc(FILE *__stream);
#if !(defined(_REENTRANT) && (_MSNT || _OS2))
    #define getc(p)	 (--(p)->_cnt>=0? *(p)->_ptr++&0377:_filbuf(p))
#endif

#undef	getchar
extern	int getchar(void);
#define getchar() (getc(stdin))

#undef	putc
extern	int putc(int __c, FILE *__stream);

#undef	putchar
extern int putchar(int	__c);
#define putchar(c) (putc((c), stdout))
extern int puts(const char *__s);
extern int ungetc(int __c, FILE *__stream);
extern char *gets(char	*__s);
extern char *fgets(char *__s, int __N,	FILE *__stream);
extern int fputs(const	char *__s, FILE	*__stream);
extern int fputc(int __c, FILE	*__stream);
extern int fseek(FILE *__stream, long __offset, int __ptrname);
extern long ftell(FILE	*__stream);
extern void rewind(FILE *__stream);
extern int fsetpos(FILE *__stream, const fpos_t *__pos);
extern int fgetpos(FILE *__stream, fpos_t *__pos);

#undef	clearerr
extern void clearerr(FILE *__stream);
/* clear _IOERR and _IOEOF */
#define clearerr(__stream) ((__stream)->_flag &= ~(_IOERR | _IOEOF))

#undef feof
extern int feof(FILE *__stream);
#define feof(__stream)	((__stream)->_flag & _IOEOF)

#undef ferror
extern int ferror(FILE	*__stream);
#define ferror(__stream) ((__stream)->_flag & _IOERR)

extern void perror(const char *__s);

#if __HIGHC__
    #include <stdarg.h>
#else
    #include <_stdarg.h>
#endif

extern int vprintf(const char *__format, __va_list __arg);
extern int vfprintf(FILE *__stream, const char	*__format, __va_list __arg);
extern int vsprintf(char *__s,	const char *__format, __va_list __arg);
extern int printf(const char *__format, ...);
extern int fprintf(FILE *__stream, const char *__format, ...);
extern int sprintf(char *__s, const char *__format, ...);
extern int fscanf(FILE	*__stream, const char *__format, ...);
extern int scanf(const	char *__format,	...);
extern int sscanf(const char *__s, const char *__format, ...);
extern int _vfscanf( FILE *f, const char *format, __va_list args );
extern int _vscanf( const char *format, __va_list args);
extern int _vsscanf( const char *s, const char *format, __va_list args );
extern int _vbprintf( char *buf, unsigned int bufsize, const char *format,
	__va_list args );
extern int _bprintf(char *buf, unsigned int bufsize, const char *format, ...);

extern long _filelength(int );
extern long _tell(int );
extern int _fcloseall(void);
extern int _flushall(void);
extern int _fputchar(int __c);
extern int _fgetchar(void);

#include <_na.h>
#if _NA_NAMES
    _NA(filelength)
    _NA(tell)
    _NA(fcloseall)
    _NA(flushall)
    _NA(fputchar)
    _NA(fgetchar)
    _NA(vfscanf)
    _NA(vscanf)
    _NA(vsscanf)
#elif _MSDOS && __HIGHC__
    extern long filelength(int );
    extern long tell(int );
    extern int fcloseall(void);
    extern int flushall(void);
    extern int fputchar(int __c);
    extern int fgetchar(void);
    extern int vfscanf( FILE *f, const char *format, __va_list args );
    extern int vscanf( const char *format, __va_list args );
    extern int vsscanf( const char *s, const char *format, __va_list args );
#endif

extern int _fileno (FILE *__stream);
#if _UPA
    #define __fileno(__stream) \
	(((((__stream)->_file)>>8)|(((__stream)->_file)<<8)) & 0xffff)
    #if __HIGHC__
	#define fileno(__stream)  __fileno(__stream)
    #endif
#else
    #define __fileno(__stream) ((__stream)->_file)
    #if __HIGHC__
	#define fileno(__stream)  ((__stream)->_file)
    #endif
#endif

#if _MSDOS || _OS2 || _MSNT
    #if __HIGHC__
	#define BUFSIZE (BUFSIZ)
    #endif

    extern FILE *_fdopen(int __fd, const char *__type);
    extern FILE *_fsopen(const char *__pathname, const char *__type,
	    int __share_flags);
    extern int _getw(FILE *_stream);
    extern int _putw(int _int1, FILE * _stream);
    extern void _stkdmp(int __filehandle);
    extern char *_tempnam(char *dir,char *prefix);
    extern int _unlink(const char *__pathname);
    #if _OS2 || _MSNT
	extern FILE *_popen(const char *__command, const char *__mode);
	extern int   _pclose(FILE *__f);
    #endif


    #include <_na.h>
    #if _NA_NAMES
	_NA(fdopen)
	_NA(fsopen)
	_NA(getw)
	_NA(putw)
	_NA(tempnam)
	_NA(unlink)
    #elif _MSDOS && __HIGHC__
	extern FILE *fdopen(int __fd, const char *__type);
	extern FILE *fsopen(const char *__pathname, const char *__type,
		int __share_flags);
	extern int getw(FILE *_stream);
	extern int putw(int _int1, FILE * _stream);
	extern char *tempnam(char *dir,char *prefix);
	extern int unlink(const char *__pathname);
    #endif
#endif

/* I860 used to be ifdefd out here */

#if _ATT || _ATT4 || _SUN || _SOL || _UPA
    extern char *tempnam(char *dir,char *prefix);
#endif


#if _TEXTFILES
    #define _O_TEXT      	0x4000
    #ifdef _AM29K
	#define _O_BINARY	0x0000
    #else
        #define _O_BINARY 	0x8000
    #endif

    #define _TEXT    		(0)
    #define _BINARY  		(1)
    extern int _setmode(FILE *__stream, int __mode);
    #if _NA_NAMES
	_NA(setmode)
    #endif

    /* ***** DO NOT USE *****. USE _TEXT and _BINARY ONLY
       To change the program-startup streams, either explicitly call
       _setmode for stdin, stdout, stderr, or modify the source file
       _iob.c provided and replace in the library.
    */
    #define _USER_FILES_BINARY	  	_BINARY
    #define _STDIN_AND_STDOUT_BINARY 	_BINARY
    #define _STDERR_BINARY		_BINARY
    #define _ALL_FILES_BINARY	  	_BINARY
    #define _ALL_FILES_TEXT	  	_TEXT
    #define _USER_FILES_TEXT	  	_TEXT
    #define _STDIN_AND_STDOUT_TEXT	_TEXT
    #define _STDERR_TEXT		_TEXT
#endif


/* Unicode functions */

extern int	 _u_bprintf(_unichar *buf, unsigned int bufsize,
			const _unichar *format, ...);
extern int	 _u_vbprintf(_unichar *buf, unsigned int bufsize,
			const _unichar *format, __va_list args );
extern FILE *    _ufdopen(int __fd, const _unichar *__type);
extern int   	 _ufgetc(FILE *__stream);
extern int   	 _ufgetchar(void);
extern _unichar *_ufgets(_unichar *__s, int __N, FILE *__stream);
extern FILE *	 _ufopen(const _unichar *__pathname, const _unichar *__type);
extern int   	 _ufprintf(FILE *__stream, const _unichar *__format, ...);
extern int   	 _ufputc(int __c, FILE *__stream);
extern int	 _ufputchar(int __c);
extern int   	 _ufputs(const _unichar *__s, FILE *__stream);
extern FILE *    _ufreopen(const _unichar *__pathname, const _unichar *__type,
			FILE *__stream);
extern int   	 _ufscanf(FILE *__stream, const _unichar *__format, ...);
extern int   	 _ugetc(FILE *__stream);
extern int   	 _ugetchar(void);
extern _unichar *_ugets(_unichar *__s);
extern void	 _uperror(const _unichar *__s);
extern int	 _uprintf(const _unichar *__format, ...);
extern int	 _uputc(int __c, FILE *__stream);
extern int	 _uputchar(int __c);
extern int	 _uputs(const _unichar *__s);
extern int	 _uremove(const _unichar *__pathname);
extern int	 _urename(const _unichar *__old, const _unichar *__new);
extern int	 _uscanf(const _unichar *__format,  ...);
extern int	 _usprintf(_unichar *__s, const _unichar *__format, ...);
extern int	 _usscanf(const _unichar *__s, const _unichar *__format, ...);
extern _unichar *_utmpnam(_unichar *__s);
extern int	 _uungetc(int __c, FILE *__stream);
extern int	 _uvfprintf(FILE *__stream, const _unichar *__format,
			__va_list __arg);
extern int	 _uvfscanf(FILE *f, const _unichar *format, __va_list args );
extern int	 _uvprintf(const _unichar *__format, __va_list __arg);
extern int	 _uvscanf(const _unichar *format, __va_list args);
extern int	 _uvsprintf(_unichar *__s, const _unichar *__format,
			__va_list __arg);
extern int	 _uvsscanf(const _unichar *s, const _unichar *format,
			__va_list args );

#if __HIGHC__
  #ifdef __UNICODE__
    #define U_bprintf  _u_bprintf
    #define U_vbprintf _u_vbprintf
    #define Ufdopen    _ufdopen
    #define Ufgetc     _ufgetc
    #define Ufgetchar  _ufgetchar
    #define Ufgets     _ufgets
    #define Ufopen     _ufopen
    #define Ufprintf   _ufprintf
    #define Ufputc     _ufputc
    #define Ufputchar  _ufputchar
    #define Ufputs     _ufputs
    #define Ufreopen   _ufreopen
    #define Ufscanf    _ufscanf
    #define Ugetc      _ufgetc
    #define Ugetchar   _ugetchar
    #define Ugets      _ugets
    #define Uperror    _uperror
    #define Uprintf    _uprintf
    #define Uputc      _uputc
    #define Uputchar   _uputchar
    #define Uputs      _uputs
    #define Uscanf     _uscanf
    #define Usprintf   _usprintf
    #define Usscanf    _usscanf
    #define Utmpnam    _utmpnam
    #define Uungetc    _uungetc
    #define Uvfprintf  _uvfprintf
    #define Uvfscanf   _uvfscanf
    #define Uvprintf   _uvprintf
    #define Uvscanf    _uvscanf
    #define Uvsprintf  _uvsprintf
    #define Uvsscanf   _uvsscanf
  #else	/* ! __UNICODE__ */
    #define U_bprintf  _bprintf
    #define U_vbprintf _vbprintf
    #define Ufdopen    fdopen
    #define Ufgetc     fgetc
    #define Ufgetchar  _fgetchar
    #define Ufgets     fgets
    #define Ufopen     fopen
    #define Ufprintf   fprintf
    #define Ufputc     fputc
    #define Ufputchar  fputchar
    #define Ufputs     fputs
    #define Ufreopen   freopen
    #define Ufscanf    fscanf
    #define Ugetc      getc
    #define Ugetchar   getchar
    #define Ugets      gets
    #define Uperror    perror
    #define Uprintf    printf
    #define Uputc      putc
    #define Uputchar   putchar
    #define Uputs      puts
    #define Uscanf     scanf
    #define Usprintf   sprintf
    #define Usscanf    sscanf
    #define Utmpnam    tmpnam
    #define Uungetc    ungetc
    #define Uvfprintf  vfprintf
    #define Uvfscanf   _vfscanf
    #define Uvprintf   vprintf
    #define Uvscanf    _vscanf
    #define Uvsprintf  vsprintf
    #define Uvsscanf   _vsscanf
  #endif /* __UNICODE__ */
#endif /* __HIGHC__ */



#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();
#endif /*_STDIO_H*/
