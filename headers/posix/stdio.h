/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	stdio.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cstdio__
#define __cstdio__

#include <ansi_parms.h>

__namespace(__stdc_space(stdio))

#include <size_t.h>
#include <null.h>
#include <va_list.h>

#if __INTEL__
#include <wchar_t.h>
#endif

/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

enum __file_kinds {
	__closed_file,
	__disk_file,
	__console_file,
	__string_file,
	__unavailable_file
};

enum __open_modes {
	__must_exist,
	__create_if_necessary,
	__create_or_truncate
};

enum __io_modes {
	__read				= 1,
	__write				= 2,
	__read_write		= 3,
	__append			= 4
};

#if __dest_os == __be_os		/* Be-mani 980107a */

typedef struct {
	unsigned char	open_mode;
	unsigned char	io_mode;
	unsigned char	buffer_mode;
	unsigned char	file_kind;
	unsigned char	binary_io;
} __file_modes;

typedef struct {
	unsigned char	_io_state;
	unsigned char	_free_buffer;
	unsigned char	_eof;
	unsigned char	_error;
} __file_state;

#else /* __dest_os */			/* Be-mani 980107a */

typedef struct {
	unsigned int	open_mode		: 2;
	unsigned int	io_mode			: 3;
	unsigned int	buffer_mode		: 2;
	unsigned int	file_kind		: 2;
	unsigned int	binary_io		: 1;
} __file_modes;

typedef struct {
	unsigned int	_io_state	: 3;
	unsigned int	_free_buffer	: 1;
	unsigned char	_eof;
	unsigned char	_error;
} __file_state;


#endif /* __dest_os */			/* Be-mani 980107a */

enum __io_states {
	__neutral,
	__writing,
	__reading,
	__rereading
};

typedef unsigned long	__file_handle;
#if __dest_os == __be_os          /* mm 970708 */
typedef long long	fpos_t;   /* we have 64 bit file sizes & positions */     /* mm 970708 */
#else                             /* mm 970708 */
typedef unsigned long	fpos_t;
#endif                            /* mm 970708 */

typedef struct _FILE FILE;

enum __io_results {
     __no_io_error,
     __io_error,
     __io_EOF         /* mm 961031 */
};

typedef void (* __idle_proc)  (void);
typedef int  (* __pos_proc)   (__file_handle file, fpos_t * position, int mode, __idle_proc idle_proc);     /* mm 970708 */
typedef int  (* __io_proc)    (__file_handle file, unsigned char * buff, size_t * count, __idle_proc idle_proc);
typedef int	 (* __close_proc) (__file_handle file);

#define __ungetc_buffer_size	2

struct _FILE {
	__file_handle		handle;
	__file_modes		mode;
	__file_state		_state;			/* Be-mani 980107 */
	unsigned char		char_buffer;
	unsigned char		char_buffer_overflow;
	unsigned char		ungetc_buffer[__ungetc_buffer_size];
	fpos_t          	position;		/* bds 131097 */
	unsigned char *		buffer;
	unsigned long		buffer_size;
	unsigned char *		_buffer_ptr;	/* Be-mani 980107 */
	unsigned long		_buffer_len;	/* Be-mani 980107 */
	unsigned long		buffer_alignment;
	unsigned long		saved_buffer_len;
	fpos_t				buffer_pos;		/* bds 131097 */
	__pos_proc			position_proc;
	__io_proc			read_proc;
	__io_proc			write_proc;
	__close_proc		close_proc;
	__idle_proc			idle_proc;
};

#define _IONBF	0
#define _IOLBF	1
#define _IOFBF	2

#define BUFSIZ			 4096
#define EOF				   -1
#define FOPEN_MAX		   35
#define FILENAME_MAX	  256

#if __dest_os == __mac_os
#define L_tmpnam		 32
#else
#define	L_tmpnam		 512
#endif

#define TMP_MAX		32767

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

__extern_c               /* mm 970708 */

#if __dest_os == __be_os

#define L_ctermid  32
#define L_cuserid  32
#define STREAM_MAX FOPEN_MAX

_IMPEXP_ROOT FILE   *popen(const char *cmd, const char *type);/* mm 970708 */ /* Be-mani 980107b */
_IMPEXP_ROOT int     pclose(FILE *fp);                        /* mm 970708 */ /* Be-mani 980107b */

_IMPEXP_ROOT char   *tempnam (char *dir, char *pfx); /* Be-mani 980107b */
_IMPEXP_ROOT char   *mktemp(char *name); /* Be-mani 980107b */

#endif /* __be_os */

#if __dest_os == __be_os
# define __files _files			/* Be-mani 980107a necessary for
								 * backward compatibility. */
#endif /* __dest_os */

#define stdin  	(&__files[0])   /* mm 961031 */    /*MW-mm 961203 */
#define stdout	(&__files[1])   /* mm 961031 */    /*MW-mm 961203 */
#define stderr	(&__files[2])   /* mm 961031 */    /*MW-mm 961203 */

_IMPEXP_ROOT extern FILE		__files[];      /* mm 961031 */    /*MW-mm 961203 */ /* Be-mani 980107b */

_IMPEXP_ROOT int remove(const char * name); /* Be-mani 980107b */
_IMPEXP_ROOT int rename(const char * old_name, const char * new_name); /* Be-mani 980107b */

_IMPEXP_ROOT char *	tmpnam(char * name); /* Be-mani 980107b */
_IMPEXP_ROOT FILE *	tmpfile(void); /* Be-mani 980107b */

_IMPEXP_ROOT void setbuf (FILE * file, char * buff); /* Be-mani 980107b */
_IMPEXP_ROOT int setvbuf(FILE * file, char * buff, int mode, size_t size); /* Be-mani 980107b */

#if __dest_os == __be_os                                        /* mm 970708 */
_IMPEXP_ROOT int setbuffer(FILE *stream, char *buf, size_t size);    /* mm 970708 */ /* Be-mani 980107b */
_IMPEXP_ROOT int setlinebuf(FILE *stream);                           /* mm 970708 */ /* Be-mani 980107b */
#endif                                                          /* mm 970708 */

_IMPEXP_ROOT int fclose(FILE * file); /* Be-mani 980107b */
_IMPEXP_ROOT int fflush(FILE * file); /* Be-mani 980107b */

_IMPEXP_ROOT FILE *	fopen  (const char * name, const char * mode); /* Be-mani 980107b */
_IMPEXP_ROOT FILE *	freopen(const char * name, const char * mode, FILE * file); /* Be-mani 980107b */

#if __dest_os == __be_os

_IMPEXP_ROOT FILE *  fdopen(int fd, const char *type); /* Be-mani 980107b */
_IMPEXP_ROOT int     fileno(FILE *fd); /* Be-mani 980107b */

#endif

_IMPEXP_ROOT void setbuf (FILE * file, char * buff); /* Be-mani 980107b */
_IMPEXP_ROOT int setvbuf(FILE * file, char * buff, int mode, size_t size); /* Be-mani 980107b */

_IMPEXP_ROOT int fprintf(FILE * file, const char * format, ...); /* Be-mani 980107b */
_IMPEXP_ROOT int fscanf (FILE * file, const char * format, ...); /* Be-mani 980107b */

_IMPEXP_ROOT int printf(const char * format, ...); /* Be-mani 980107b */
_IMPEXP_ROOT int scanf (const char * format, ...); /* Be-mani 980107b */

_IMPEXP_ROOT int sprintf(      char * s, const char * format, ...); /* Be-mani 980107b */
_IMPEXP_ROOT int sscanf (const char * s, const char * format, ...); /* Be-mani 980107b */
#if __INTEL__
_IMPEXP_ROOT int swprintf(wchar_t * s, const wchar_t * format, ...); /* Be-mani 980107b */
#endif


int			__vfscanf(FILE * file,    const char * format, va_list arg);
int			__vsscanf(const char * s, const char * format, va_list arg);

_IMPEXP_ROOT int vfprintf(FILE * file, const char * format, va_list arg); /* Be-mani 980107b */
_IMPEXP_ROOT int vprintf(const char * format, va_list arg); /* Be-mani 980107b */
_IMPEXP_ROOT int vsprintf(char * s, const char * format, va_list arg); /* Be-mani 980107b */

_IMPEXP_ROOT int fgetc(FILE * file); /* Be-mani 980107b */
_IMPEXP_ROOT char *	fgets(char * s, int n, FILE * file); /* Be-mani 980107b */

_IMPEXP_ROOT int fputc(int c, FILE * file); /* Be-mani 980107b */
_IMPEXP_ROOT int fputs(const char * s, FILE * file); /* Be-mani 980107b */

_IMPEXP_ROOT char *	gets(char * s); /* Be-mani 980107b */

_IMPEXP_ROOT int puts(const char * s); /* Be-mani 980107b */

_IMPEXP_ROOT int ungetc(int c, FILE * file); /* Be-mani 980107b */

_IMPEXP_ROOT size_t	fread (      void * ptr, size_t memb_size, size_t num_memb, FILE * file); /* Be-mani 980107b */
_IMPEXP_ROOT size_t	fwrite(const void * ptr, size_t memb_size, size_t num_memb, FILE * file); /* Be-mani 980107b */

_IMPEXP_ROOT int			fgetpos(FILE * file, fpos_t * pos); /* Be-mani 980107b */
_IMPEXP_ROOT long		ftell  (FILE * file); /* Be-mani 980107b */
_IMPEXP_ROOT fpos_t     _ftell(FILE *);                    /* mm 970708 */ /* Be-mani 980107b */

_IMPEXP_ROOT int			fsetpos(FILE * file, const fpos_t * pos); /* Be-mani 980107b */
_IMPEXP_ROOT int			fseek  (FILE * file, long offset, int mode); /* Be-mani 980107b */
_IMPEXP_ROOT int         _fseek(FILE *, fpos_t, int);     /* mm 970708 */ /* Be-mani 980107b */

_IMPEXP_ROOT void		rewind(FILE * file); /* Be-mani 980107b */

_IMPEXP_ROOT void		clearerr(FILE * file); /* Be-mani 980107b */

_IMPEXP_ROOT void		perror(const char * s); /* Be-mani 980107b */

_IMPEXP_ROOT int			__get_char(FILE * file); /* Be-mani 980107b */
_IMPEXP_ROOT int			__put_char(int c,FILE * file); /* Be-mani 980107b */

_IMPEXP_ROOT FILE *	__handle_open  (__file_handle handle, const char * mode); /* Be-mani 980107b */
_IMPEXP_ROOT FILE *	__handle_reopen(__file_handle handle, const char * mode, FILE * file); /* Be-mani 980107b */

void		__set_idle_proc(FILE * file, __idle_proc idle_proc);

#if (__dest_os	== __win32_os)

	/*
	 * I'm putting this declaration here because it is in Visual C++'s stdio.h
	 * I copied this declaration from unix.win32.h. They should match.
	 */
	 FILE *fdopen(int fildes, char *type);

#endif


__end_extern_c

#ifdef __cplusplus

inline int getc(FILE * file)
	{ return file->_buffer_len-- ? *file->_buffer_ptr++ : __get_char(file); } /* Be-mani 980107 */

inline int putc(int c, FILE *file)
	{ return file->_buffer_len-- ? (*file->_buffer_ptr++ = c) : __put_char(c, file); } /* Be-mani 980107 */

inline int getchar()
	{ return getc(stdin); }

inline int putchar(int c)
	{ return putc(c, stdout); }

inline int feof(FILE * file)
	{ return file->_state._eof; }  /* Be-mani 980107 */

inline int ferror(FILE * file)
	{ return file->_state._error; }	/* Be-mani 980107 */

#else

_IMPEXP_ROOT int			getc(FILE * file); /* Be-mani 980107b */
_IMPEXP_ROOT int			putc(int c, FILE * file); /* Be-mani 980107b */

#define getc(file)		((file)->_buffer_len-- ? (int)  *(file)->_buffer_ptr++      : __std(__get_char)(file)) /* Be-mani 980107 */
#define putc(c, file)	((file)->_buffer_len-- ? (int) (*(file)->_buffer_ptr++ = c) : __std(__put_char)(c, file)) /* Be-mani 980107 */

_IMPEXP_ROOT int			getchar(void); /* Be-mani 980107b */
_IMPEXP_ROOT int			putchar(int c); /* Be-mani 980107b */

#define getchar()			__std(getc)(stdin)
#define putchar(c)		__std(putc)(c, stdout)

_IMPEXP_ROOT int			feof  (FILE * file); /* Be-mani 980107b */
_IMPEXP_ROOT int			ferror(FILE * file); /* Be-mani 980107b */

#define feof(file)		((file)->_state._eof)	/* Be-mani 980107 */
#define ferror(file)	((file)->_state._error)	/* Be-mani 980107 */

#endif

__end_namespace(stdc_space(stdio))

__import_stdc_into_std_space(stdio)

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */

#endif /* __cstdio__ */

/*     Change record
 * mm 961031  Changes for Pascal
 * mm 961203  Changed files to __files
 * mm 970708  Inserted Be changes
 * bds 131097 Be changes
 * Be-mani 980107a Backward compatility changes for BeOS shared libs.
 * Be-mani 980107b shared lib changes for BeOS
 * Be-mani 980107 Prepend certain stdio.h private
 *                struct members with underscores. This prevents pollution
 *				  of user namespace.  Otherwise, #define's can destroy
 *				  correct compilation.
 */
