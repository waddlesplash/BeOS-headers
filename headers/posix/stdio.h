/*
 *	stdio.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __stdio__
#define __stdio__

#include <ansi_parms.h>
#include <size_t.h>
#include <null.h>
#include <va_list.h>

#pragma options align=mac68k

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
	unsigned int	open_mode		: 2;
	unsigned int	io_mode			: 3;
	unsigned int	buffer_mode	: 2;
	unsigned int	file_kind		: 2;
	unsigned int	binary_io		: 1;
} __file_modes;

enum __io_states {
	__neutral,
	__reading,
	__rereading,
	__writing
};

typedef struct {
	unsigned int	io_state		: 2;
	unsigned int	free_buffer	: 1;
	unsigned char	eof;
	unsigned char	error;
} __file_state;

typedef unsigned long	__file_handle;
typedef unsigned long	fpos_t;

typedef struct _FILE FILE;

enum __io_results {
	__no_io_error,
	__io_error,
	__EOF
};

typedef int (* __pos_proc)  (__file_handle file, long * position, int mode);
typedef int (* __io_proc)		(__file_handle file, unsigned char * buff, size_t * count);
typedef int (* __close_proc)(__file_handle file);

struct _FILE {
	__file_handle		handle;
	__file_modes		mode;
	__file_state		state;
	unsigned char		char_buffer;
	unsigned char		ungetc_buffer;
	unsigned long		position;
	unsigned char *	buffer;
	unsigned long		buffer_size;
	unsigned char *	buffer_ptr;
	unsigned long		buffer_len;
	unsigned long		buffer_alignment;
	unsigned long		saved_buffer_len;
	unsigned long		buffer_pos;
	__pos_proc			position_proc;
	__io_proc				read_proc;
	__io_proc				write_proc;
	__close_proc		close_proc;
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


extern FILE *	stdin;
extern FILE *	stdout;
extern FILE *	stderr;

int			remove(const char * name);
int			rename(const char * old_name, const char * new_name);

char *	tmpnam(char * name);
FILE *	tmpfile(void);

void		setbuf (FILE * file, char * buff);
int			setvbuf(FILE * file, char * buff, int mode, size_t size);

int			fclose(FILE * file);
int			fflush(FILE * file);

FILE *	fopen  (const char * name, const char * mode);
FILE *	freopen(const char * name, const char * mode, FILE * file);

FILE *  fdopen(int fd, const char *type);
int     fileno(FILE *fd);

void		setbuf (FILE * file, char * buff);
int			setvbuf(FILE * file, char * buff, int mode, size_t size);

int			fprintf(FILE * file, const char * format, ...);
int			fscanf (FILE * file, const char * format, ...);

int			printf(const char * format, ...);
int			scanf (const char * format, ...);

int			sprintf(      char * s, const char * format, ...);
int			sscanf (const char * s, const char * format, ...);

int			vfprintf(FILE * file, const char * format, va_list arg);
int			vprintf(const char * format, va_list arg);
int			vsprintf(char * s, const char * format, va_list arg);

int			fgetc(FILE * file);
char *	fgets(char * s, int n, FILE * file);

int			fputc(int c, FILE * file);
int			fputs(const char * s, FILE * file);

int			getc(FILE * file);
int			getchar(void);
char *	gets(char * s);

int			putc(int c, FILE * file);
int			putchar(int c);
int			puts(const char * s);

int			ungetc(int c, FILE * file);

size_t	fread (      void * ptr, size_t memb_size, size_t num_memb, FILE * file);
size_t	fwrite(const void * ptr, size_t memb_size, size_t num_memb, FILE * file);

int			fgetpos(FILE * file, fpos_t * pos);
long		ftell  (FILE * file);

int			fsetpos(FILE * file, const fpos_t * pos);
int			fseek  (FILE * file, long offset, int mode);

void		rewind(FILE * file);

void		clearerr(FILE * file);

int			feof  (FILE * file);
int			ferror(FILE * file);

void		perror(const char * s);

int			__get_char(FILE * file);
int			__put_char(int c,FILE * file);

__end_extern_c

#define getc(file)		((file)->buffer_len-- ? (int)  *(file)->buffer_ptr++      : __get_char(file))
#define putc(c, file)	((file)->buffer_len-- ? (int) (*(file)->buffer_ptr++ = c) : __put_char(c, file))

#define getchar()			getc(stdin)
#define putchar(c)		putc(c, stdout)

#define feof(file)		((file)->state.eof)
#define ferror(file)	((file)->state.error)

#pragma options align=reset

#endif /* __stdio__ */
