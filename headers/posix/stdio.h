/*/  Metrowerks Standard Library  Version 1.6  1996 November 01  /*/

/*
 *	stdio.h
 *	
 *		Copyright © 1995-1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cstdio__
#define __cstdio__

#include <ansi_parms.h>


__namespace(__stdc_space(stdio))

#include <size_t.h>
#include <null.h>
#include <va_list.h>

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
	__read_write	= 3,
	__append			= 4
};

typedef struct {
	unsigned char	open_mode;
	unsigned char	io_mode;
	unsigned char	buffer_mode;
	unsigned char	file_kind;
	unsigned char	binary_io;
} __file_modes;

enum __io_states {
	__neutral,
	__writing,
	__reading,
	__rereading
};

typedef struct {
	unsigned char	_io_state;
	unsigned char	_free_buffer;
	unsigned char	_eof;
	unsigned char	_error;
} __file_state;

typedef unsigned long	__file_handle;
#if __dest_os == __be_os
typedef long long	fpos_t;   /* we have 64 bit file sizes & positions */
#else
typedef long  fpos_t;
#endif

typedef struct _FILE FILE;

enum __io_results {
     __no_io_error,
     __io_error,
     __io_EOF         /* mm 961031 */
};

typedef void (* __idle_proc)  (void);
typedef int  (* __pos_proc)   (__file_handle file, fpos_t * position, int mode, __idle_proc idle_proc);
typedef int  (* __io_proc)    (__file_handle file, unsigned char * buff, size_t * count, __idle_proc idle_proc);
typedef int	 (* __close_proc) (__file_handle file);

#define __ungetc_buffer_size	2

struct _FILE {
	__file_handle		handle;
	__file_modes		mode;
	__file_state		state;
	unsigned char		char_buffer;
	unsigned char		char_buffer_overflow;
	unsigned char		ungetc_buffer[__ungetc_buffer_size];
	fpos_t          position;
	unsigned char *	buffer;
	unsigned long		buffer_size;
	unsigned char *	buffer_ptr;
	unsigned long		buffer_len;
	unsigned long		buffer_alignment;
	unsigned long		saved_buffer_len;
	fpos_t					buffer_pos;
	__pos_proc			position_proc;
	__io_proc				read_proc;
	__io_proc				write_proc;
	__close_proc		close_proc;
	__idle_proc			idle_proc;
};

#define _IONBF	0
#define _IOLBF	1
#define _IOFBF	2

#define BUFSIZ			 4096
#define EOF						 -1
#define FOPEN_MAX			 35
#define FILENAME_MAX	256

#define L_tmpnam		 32
#define TMP_MAX		32767

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

__extern_c

#if __dest_os == __be_os

#define L_ctermid  32
#define L_cuserid  32
#define STREAM_MAX FOPEN_MAX

FILE   *popen(const char *cmd, const char *type);
int     pclose(FILE *fp);


#endif /* __be_os */

#define stdin  	(&_files[0])   /* mm 961031 */
#define stdout	(&_files[1])   /* mm 961031 */
#define stderr	(&_files[2])   /* mm 961031 */
extern FILE		_files[];        /* mm 961031 */

int			remove(const char * name);
int			rename(const char * old_name, const char * new_name);

char *	tmpnam(char * name);
FILE *	tmpfile(void);

void		setbuf (FILE * file, char * buff);
int			setvbuf(FILE * file, char * buff, int mode, size_t size);

#if __dest_os == __be_os
int         setbuffer(FILE *stream, char *buf, size_t size);
int         setlinebuf(FILE *stream);
#endif

int			fclose(FILE * file);
int			fflush(FILE * file);

FILE *	fopen  (const char * name, const char * mode);
FILE *	freopen(const char * name, const char * mode, FILE * file);

#if __dest_os == __be_os

FILE *  fdopen(int fd, const char *type);
int     fileno(FILE *fd);

#endif

void		setbuf (FILE * file, char * buff);
int			setvbuf(FILE * file, char * buff, int mode, size_t size);

int			fprintf(FILE * file, const char * format, ...);
int			fscanf (FILE * file, const char * format, ...);

int			printf(const char * format, ...);
int			scanf (const char * format, ...);

int			sprintf(      char * s, const char * format, ...);
int			sscanf (const char * s, const char * format, ...);

int			__vfscanf(FILE * file,    const char * format, va_list arg);
int			__vsscanf(const char * s, const char * format, va_list arg);

int			vfprintf(FILE * file, const char * format, va_list arg);
int			vprintf(const char * format, va_list arg);
int			vsprintf(char * s, const char * format, va_list arg);

int			fgetc(FILE * file);
char *	fgets(char * s, int n, FILE * file);

int			fputc(int c, FILE * file);
int			fputs(const char * s, FILE * file);

char *	gets(char * s);

int			puts(const char * s);

int			ungetc(int c, FILE * file);

size_t	fread (      void * ptr, size_t memb_size, size_t num_memb, FILE * file);
size_t	fwrite(const void * ptr, size_t memb_size, size_t num_memb, FILE * file);

int			fgetpos(FILE * file, fpos_t * pos);
long		ftell  (FILE * file);
fpos_t  _ftell(FILE * file);   /* for large files */

int			fsetpos(FILE * file, const fpos_t * pos);
int			fseek  (FILE * file, long offset, int mode);
int     _fseek(FILE * file, fpos_t offset, int mode); /* for large files */

void		rewind(FILE * file);

void		clearerr(FILE * file);

void		perror(const char * s);

int			__get_char(FILE * file);
int			__put_char(int c,FILE * file);

FILE *	__handle_open  (__file_handle handle, const char * mode);
FILE *	__handle_reopen(__file_handle handle, const char * mode, FILE * file);

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
	{ return file->buffer_len-- ? *file->buffer_ptr++ : __get_char(file); }

inline int putc(int c, FILE *file)
	{ return file->buffer_len-- ? (*file->buffer_ptr++ = c) : __put_char(c, file); }

inline int getchar()
	{ return getc(stdin); }

inline int putchar(int c)
	{ return putc(c, stdout); }

inline int feof(FILE * file)
	{ return file->state._eof; }

inline int ferror(FILE * file)
	{ return file->state._error; }

#else

int			getc(FILE * file);
int			putc(int c, FILE * file);

#define getc(file)		((file)->buffer_len-- ? (int)  *(file)->buffer_ptr++      : __std(__get_char)(file))
#define putc(c, file)	((file)->buffer_len-- ? (int) (*(file)->buffer_ptr++ = c) : __std(__put_char)(c, file))

int			getchar(void);
int			putchar(int c);

#define getchar()			__std(getc)(stdin)
#define putchar(c)		__std(putc)(c, stdout)

int			feof  (FILE * file);
int			ferror(FILE * file);

#define feof(file)		((file)->state._eof)
#define ferror(file)	((file)->state._error)

#endif

__end_namespace(stdc_space(stdio))

__import_stdc_into_std_space(stdio)

#pragma options align=reset

#endif /* __cstdio__ */

/*     Change record
mm 961031  Changes for Pascal
*/
