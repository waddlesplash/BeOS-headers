/*
 *   (c) Copyright 1991, MetaWare, Inc.
 *
 *   static.h:  support for reentrant libraries.
 *              All static variables in the runtime
 *              library should be defined here.
 */

#ifndef _STATIC_H
    #define _STATIC_H
#pragma push_align_members(64);

    #ifdef _REENTRANT

	/************************************
	 *                                  *
	 *  definitions of static variables *
	 *         reentrant version        *
	 *                                  *
	 ************************************/

	#ifndef _STDIO_H
	    #include <stdio.h>
	#endif

	#if _NEWLINE_XLATE
	    #ifndef _LINETERM_CF
		#include <lineterm.cf>
	    #endif
	#endif

	#ifndef _LOCALE_H
	    #include <locale.h>
	#endif

	#ifndef _FLOAT_H
	    #include <float.h>
	#endif

	#ifndef _TIME_H
	    #include <time.h>
	#endif

	#ifndef _MATH_H
	    #include <math.h>
	#endif

	#ifndef _SIGNAL_H
	    #include <signal.h>
	#endif

	#if _MSDOS
	    #ifndef _MALLOC_I_H
		#include <malloc_i.h>
	    #endif

	    #ifndef _MWCTOR_H
		#include <mwctor.h>
	    #endif

	    #ifndef _DOS_H
		#include <dos.h>
	    #endif
	#endif

	#if _HOBBIT
	    #define _BASESIZE 9
	#elif _MSDOS || _MSNT || _OS2
	#else
	    #error __FILE__:  _BASESIZE not defined
	    /*
	    #define _BASESIZE 9
	    */
	#endif

/*
 * errno cannot be declared volatile.
 * See errno.h for information.
 */
	/* task data */
	typedef struct {

	    /* Data common to all implementations.
	     */
	    int			errno;
	    char 		_tmpnam_s0[L_tmpnam + 1];
	    _unichar		_utmpnam_s0[L_tmpnam + 1];
	    char		_doecvt_buf[LDBL_DIG + sizeof(long) * 2 + 1];
	    _unichar		_udoecvt_buf[LDBL_DIG + sizeof(long) * 2 + 1];
	    unsigned long 	_rand_random;
	    char *		_strtok_sp;
	    _unichar *		_ustrtok_sp;
	    #define _STRERR_LEN 128     /* must agree with strerror.c */
	    char		_strerror_buffer[_STRERR_LEN];
	    _unichar		_ustrerror_buffer[_STRERR_LEN];
	    char		_asctime_buf[32];
	    char		_ctime_buf[32];
	    _unichar		_uasctime_buf[32];
	    _unichar		_uctime_buf[32];
	    struct tm		_localtime_tm;
	    struct tm		_gmtime_tm;

	    /* DOS-specific data.  On other systems, these variables
	     * are not used, or their use is controlled by semaphores.
	     */
	    #if _MSDOS
		ct_array 	_mwdestructors;
		unsigned long	_mwn_destructors;

		char ** 	_environ;   /* see _putenv/envinit modules */
		char *** 	_mwenvip;   /* see getenv/envinit modules */
		_Far char *	_mwenvp;    /* see cinit/getenv modules */
		#define _GETENV_STRSIZE 256 /* must agree with getenv.c */
		char 	_mwtmp_env_buf[2][_GETENV_STRSIZE];
		int 	_mwgetenvbufnum;    /* Index into buffer array */
		int 	_mwnextenv;         /* for supporting getenv(NULL) iteration */
		char *	_mwgetenv_heapptr;  /* when _GETENV_STRSIZE isn't enough */

		int (* 	_mwdefault_raise)(int);

		long 	_clock_start;       /* see clock.c */
		struct _dosdate_t _mw_gdate;/* see time.c */
		int 	_mw_lastime;	    /* see time.c */

		/* data for conio functions */
		int _mw_ungetch_x; /* a place to save one ungotten character */
	    #endif

	    /* Data common to DOS, NT, and OS/2.
	     */
	    #if _MSDOS || _MSNT || _OS2
		int  _doserrno;
		unsigned short int _mwfp_status;  /* see _fpreset.c, etc. */
	    #endif

	    /* Data common to NT and OS/2.
	     */
	    #if _MSNT || _OS2
		void (*_mw_sighandlers[_NSIG])(int);
		    /* pointer to exception registration record,
		       so _endthread can unlink it from the chain. */
		void *_mwexcregp;
	    #endif

	    #if _MSNT
		#define _GETENV_MAX 512  /* must agree with msnt_t/getenv.c */
		char _mwgetenv_buf[2][_GETENV_MAX];
	    #endif

	    /* Heap manager data.  OS/2 and NT use the same heap manager
	     * as DOS, but use of the global variables is governed by
	     * a semaphore.
	     */
	    #if _MSDOS
		char 		_mwh_corrupt_flag;
		char 		_mwhfirst_time;
                int 		_alignment_offset; 
                char 		_mwhfirst_fit;
                int 		_malloc_level;
                unsigned 	_mwhitem_header_size;
                unsigned 	_mwhsegment_header_size;
                _SEGMENT_HEADER *_mwhsegment_chain;
                _ITEM_HEADER 	_mwhbucket[_BUCKET_COUNT];
	    #elif  _HOBBIT && !defined(__PENPOINT__)
		unsigned long 	_malloc_base[_BASESIZE];
		unsigned long *	_malloc_allocp;
	    #endif

	    /* FILE stream data, and other data for non-threading systems.
	     */
	    #if _MSDOS || _HOBBIT
		#if (_IOB_FORMAT == _IOB_LIST)
		    FILE 		_IOB[_MIN_USER_STREAM];
		    FILE *		_iob_head;
		#else
		    FILE 		_IOB[FOPEN_MAX];
		    _iob_fioflag_t 	_iob_fioflag[FOPEN_MAX];
		    _iob_unget_t 	_iob_unget[FOPEN_MAX];	
		    char *		_iob_tmpnam[FOPEN_MAX];
		#endif
		#if (_IOB_BUFTYP == _IOB_BUFENDTAB)
	             _iob_ptr_t *	_bufendtab[FOPEN_MAX];
		#endif
		int 		_iob_fopen_max;  /* keep if _IOB_LIST? */
		int 		_iob_bufsiz_dflt;
		int 		_iob_fmode;
		int 		_iob_pmode;

		#if _NEWLINE_XLATE
		    _ltconv 	_mwLTConv_in;
		    _ltconv 	_mwLTConv_out;
		    int 	_mw_textmode_eof;
		#endif

		int		_tmpnam_n;
		void 		(*_exitv)(void); /* see atexit.c */
		#define MAXEX	36
		void 		(*_atexit_list[MAXEX])(void);  
		int 		_atexit_count;

		char 		_current_locale[ 2 ];
		char *		_get_tz_cp;
		char 		_get_tz_DST_enabled;
		int 		_get_tz_GMT_less_local;
	    #endif

	    /* Timezone information.
	     */
	    #if _MSDOS
		int 		_daylight;
		long 		_timezone;
		char *		_tzname[2];
                _unichar *	_utzname[2];
		char 		__tzname0[33];
		char 		__tzname1[33];
		_unichar 	__utzname0[33];
		_unichar 	__utzname1[33];
		long 		_timezone_std;
		long 		_timezone_dst;
	    #endif

	    int (*_matherr_handler)(struct _exception *err_info);

	    } _static_t;


/* Definition of system-dependent entry point for retrieving the pointer 
   to the static data.
*/
	#if _HOBBIT
	    #define _TASK_DATA_PTR OSTaskRWData
	    #define _TASK_DATA_SET OSTaskRWDataSet
	#elif _MSDOS || _MSNT || _OS2
	    #define _TASK_DATA_PTR _OSTaskRWData
	    #define _TASK_DATA_SET _OSTaskRWDataSet
	#else
	    #error _TASK_DATA_PTR not defined in static.h
	#endif

	/* retrieve task data pointer, normally a pointer to _static_t */
	extern void *_TASK_DATA_PTR();
	/* set task data pointer. input is normally a pointer to _static_t */
	extern void _TASK_DATA_SET(void *p);

/* Initializes the static area.  Must be called before "main" at runtime. 
   This routine will call _TASK_DATA_PTR to get access to the data area
   needing initialization */
	extern void _static_initialize();



	#define _STATIC(x)(((_static_t *)_TASK_DATA_PTR())->x)

	/* macros used to access fields in task data */

	#define errno 			_STATIC(errno)
	#define _tmpnam_s0		_STATIC(_tmpnam_s0)
	#define _utmpnam_s0		_STATIC(_utmpnam_s0)
        #define _doecvt_buf		_STATIC(_doecvt_buf)
        #define _udoecvt_buf		_STATIC(_udoecvt_buf)
        #define _random			_STATIC(_rand_random)
        #define	_strtok_sp		_STATIC(_strtok_sp)
        #define	_ustrtok_sp		_STATIC(_ustrtok_sp)
	#define _strerror_buffer	_STATIC(_strerror_buffer)
	#define _ustrerror_buffer	_STATIC(_ustrerror_buffer)
        #define _asctime_buf		_STATIC(_asctime_buf)
        #define _ctime_buf		_STATIC(_ctime_buf)
	#define _uasctime_buf		_STATIC(_uasctime_buf)
	#define _uctime_buf		_STATIC(_uctime_buf)
        #define _localtime_tm		_STATIC(_localtime_tm)
        #define _gmtime_tm		_STATIC(_gmtime_tm)

	#if _MSDOS
	    #define _mwdestructors	_STATIC(_mwdestructors)
	    #define _mwn_destructors	_STATIC(_mwn_destructors)

	    #define _environ	_STATIC(_environ)
	    #if __HIGHC__
		#define environ	_STATIC(_environ)
	    #endif
	    #define _mwenvip		_STATIC(_mwenvip)
	    #define _mwenvp		_STATIC(_mwenvp)
	    #define _mwtmp_env_buf	_STATIC(_mwtmp_env_buf)
	    #define _mwgetenvbufnum	_STATIC(_mwgetenvbufnum)
	    #define _mwnextenv		_STATIC(_mwnextenv)
	    #define _mwgetenv_heapptr	_STATIC(_mwgetenv_heapptr)
	    #define _mwdefault_raise	_STATIC(_mwdefault_raise)
	    #define _clock_start	_STATIC(_clock_start)
	    #define _mw_gdate		_STATIC(_mw_gdate)
	    #define _mw_lastime		_STATIC(_mw_lastime)
	    #define _mw_ungetch_x	_STATIC(_mw_ungetch_x)
	#endif

	#if _MSDOS || _MSNT || _OS2
	    #define _mwfp_status	_STATIC(_mwfp_status)
	    #define _doserrno		_STATIC(_doserrno)
	#endif

	#if _MSNT || _OS2
	    #define _mw_sighandlers	_STATIC(_mw_sighandlers)
	    #define _mwexcregp		_STATIC(_mwexcregp)
	#endif

	#if _MSNT
	    #define _mwgetenv_buf	_STATIC(_mwgetenv_buf)
	#endif

	#if _MSDOS
	    #define  _mwh_corrupt_flag	_STATIC(_mwh_corrupt_flag)
	    #define  _mwhfirst_time	_STATIC(_mwhfirst_time)
	    #define  _alignment_offset 	_STATIC(_alignment_offset)
	    #define  _mwhfirst_fit	_STATIC(_mwhfirst_fit)
	    #define  _malloc_level	_STATIC(_malloc_level)
	    #define  _mwhitem_header_size	_STATIC(_mwhitem_header_size)
	    #define  _mwhsegment_header_size	_STATIC(_mwhsegment_header_size)
	    #define  _mwhsegment_chain	_STATIC(_mwhsegment_chain)
	    #define  _mwhbucket		_STATIC(_mwhbucket)
	#elif _HOBBIT && !defined(__PENPOINT__)
	    #define _malloc_base 	_STATIC(_malloc_base)
	    #define _malloc_allocp	_STATIC(_malloc_allocp)
	#endif


	#if _MSDOS || _HOBBIT
	    #if (_IOB_FORMAT == _IOB_LIST)
		#define _iob_head		_STATIC(_iob_head)
	    #else
		#define _iob_fioflag		_STATIC(_iob_fioflag)
		#define _iob_unget		_STATIC(_iob_unget)
		#define _iob_tmpnam		_STATIC(_iob_tmpnam)
	    #endif
	    #define _IOB			_STATIC(_IOB)
	    #if (_IOB_BUFTYP == _IOB_BUFENDTAB)
		#define _bufendtab		_STATIC(_bufendtab)
	    #endif
	    #define _fopen_max			_STATIC(_iob_fopen_max)
	    #define _bufsiz_dflt		_STATIC(_iob_bufsiz_dflt)
	    #define _fmode			_STATIC(_iob_fmode)
	    #define _pmode			_STATIC(_iob_pmode)

	    #if _NEWLINE_XLATE
		#define _mwLTConv_in		_STATIC(_mwLTConv_in)
		#define _mwLTConv_out		_STATIC(_mwLTConv_out)
		#define _mw_textmode_eof	_STATIC(_mw_textmode_eof)
	    #endif

	    #define _tmpnam_n			_STATIC(_tmpnam_n)
	    #define _exitv			_STATIC(_exitv)
	    #define _atexit_list		_STATIC(_atexit_list)
	    #define _atexit_count		_STATIC(_atexit_count)

	    #define _current_locale		_STATIC(_current_locale)
	    #define _get_tz_cp			_STATIC(_get_tz_cp)
	    #define _get_tz_DST_enabled		_STATIC(_get_tz_DST_enabled)
	    #define _get_tz_GMT_less_local	_STATIC(_get_tz_GMT_less_local)
	#endif

	#if _MSDOS
	    #define _daylight		_STATIC(_daylight)
	    #define _timezone		_STATIC(_timezone)
	    #define _tzname		_STATIC(_tzname)
            #define _utzname		_STATIC(_utzname)
	    #define __tzname0		_STATIC(__tzname0)
	    #define __tzname1		_STATIC(__tzname1)
	    #define __utzname0		_STATIC(__utzname0)
	    #define __utzname1		_STATIC(__utzname1)
	    #define _timezone_std	_STATIC(_timezone_std)
	    #define _timezone_dst	_STATIC(_timezone_dst)
	    #if __HIGHC__
		#define daylight	_STATIC(_daylight)
		#define timezone	_STATIC(_timezone)
		#define tzname		_STATIC(_tzname)
	    #endif
	#endif

	#define _matherr_handler	_STATIC(_matherr_handler)

    #endif
#pragma pop_align_members();
#endif
