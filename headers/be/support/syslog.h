/*
 * Copyright (c) 1996-97, Be Inc.
 *
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)syslog.h	7.20 (Berkeley) 2/23/91
 */

#ifndef _SYS_LOG_H
#define	_SYS_LOG_H

/*
 * priorities, facilities and flags are encoded into a single 32-bit quantity,
 * where the bottom 3 bits are the priority (0-7), the next 7 bits are the
 * facility, and a couple of nybbles in the middle represent additional
 * output flags.  Both the priorities and the facilities map roughly
 * one-to-one to strings.  This mapping is included in this file.
 *
 * priorities (these are ordered)
 */
#define	LOG_EMERG	0	/* system is unusable */
#define LOG_PANIC	LOG_EMERG
#define	LOG_ALERT	1	/* action must be taken immediately */
#define	LOG_CRIT	2	/* critical conditions */
#define	LOG_ERR		3	/* error conditions */
#define	LOG_WARNING	4	/* warning conditions */
#define	LOG_NOTICE	5	/* normal but significant condition */
#define	LOG_INFO	6	/* informational */
#define	LOG_DEBUG	7	/* debug-level messages */

#define LOG_NPRIORITIES	8
#define	LOG_PRIMASK	0x07	/* mask to extract priority part (internal) */
				/* extract priority */
#define	LOG_PRI(p)				((p) & LOG_PRIMASK)
#define	LOG_MAKEPRI(fac, pri)	(((fac) << 3) | (pri))

#ifdef SYSLOG_NAMES
#define	INTERNAL_NOPRI	0x8		/* the "no priority" priority */
				/* mark "facility" */
#define	INTERNAL_MARK	LOG_MAKEPRI(LOG_NFACILITIES, 0)

static char *prioritynames[] = {
	"panic",					/* LOG_EMERG */
	"alert",					/* LOG_ALERT */
	"crit",						/* LOG_CRIT */
	"err",						/* LOG_ERR */
	"warning",					/* LOG_WARNING */
	"notice",					/* LOG_NOTICE */
	"info",						/* LOG_INFO */
	"debug",					/* LOG_DEBUG */
	"none",						/* INTERNAL_NOPRI */
	NULL
};

#endif

/* facility codes */
#define	LOG_KERN	(0<<3)	/* kernel messages */
#define	LOG_USER	(1<<3)	/* random user-level messages */
#define	LOG_MAIL	(2<<3)	/* mail system */
#define	LOG_DAEMON	(3<<3)	/* system daemons */
#define	LOG_AUTH	(4<<3)	/* security/authorization messages */
#define	LOG_SYSLOG	(5<<3)	/* messages generated internally by syslogd */
#define	LOG_LPR		(6<<3)	/* line printer subsystem */
#define	LOG_NEWS	(7<<3)	/* network news subsystem */
#define	LOG_UUCP	(8<<3)	/* UUCP subsystem */
#define	LOG_CRON	(9<<3)	/* clock daemon */
#define	LOG_AUTHPRIV	(10<<3)	/* security/authorization messages (private) */

/* other codes through 15 reserved for system use */
#define	LOG_LOCAL0	(16<<3)	/* reserved for local use */
#define	LOG_LOCAL1	(17<<3)	/* reserved for local use */
#define	LOG_LOCAL2	(18<<3)	/* reserved for local use */
#define	LOG_LOCAL3	(19<<3)	/* reserved for local use */
#define	LOG_LOCAL4	(20<<3)	/* reserved for local use */
#define	LOG_LOCAL5	(21<<3)	/* reserved for local use */
#define	LOG_LOCAL6	(22<<3)	/* reserved for local use */
#define	LOG_LOCAL7	(23<<3)	/* reserved for local use */

#define	LOG_NFACILITIES	24	/* current number of facilities */
#define	LOG_FACMASK	0x03f8	/* mask to extract facility part */
				/* facility of pri */
#define	LOG_FAC(p)	(((p) & LOG_FACMASK) >> 3)

#ifdef SYSLOG_NAMES

static char *facilitynames[] = {
	"kern", "user", "mail", "daemon",
	"auth", "syslogd", "lpr", "news",
	"uucp", "cron", "authpriv", "",
	"", "", "", "",
	"local0", "local1", "local2", "local3",
	"local4", "local5", "local6", "local7",
	NULL
};

#endif

#ifdef KERNEL
#define	LOG_PRINTF	-1	/* pseudo-priority to indicate use of printf */
#endif

/*
 * arguments to setlogmask.
 */
#define	LOG_MASK(pri)	(1 << (pri))		/* mask for one priority */
#define	LOG_UPTO(pri)	((1 << ((pri)+1)) - 1)	/* all priorities through pri */

/*
 * Option flags for openlog.
 *
 * LOG_ODELAY no longer does anything.
 * LOG_NDELAY is the inverse of what it used to be.
 */
#define LOG_OPTIONSMASK	0x000ff000
#define LOG_OPTIONS(p)	((p) & LOG_OPTIONSMASK)

#define	LOG_PID		(0x01<<12)	/* log the pid with each message */
#define LOG_THID	LOG_PID
#define LOG_TMID	LOG_PID
#define	LOG_CONS	(0x02<<12)	/* here for compatibility -- does nothing */
#define	LOG_ODELAY	(0x04<<12)	/* irrelevant in BeOS -- here for compatibility */
#define	LOG_NDELAY	(0x08<<12)	/* irrelevant in BeOS -- here for comptaibility */
#define LOG_SERIAL	(0x10<<12)	/* log to serial port as well */
#define	LOG_PERROR	(0x20<<12)	/* log to stderr as well */


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Logging interface.
 */

void	closelog (void);
void	closelog_team (void);
void	closelog_thread (void);
void	openlog (char *, int, int);
void	openlog_team (char *, int, int);
void	openlog_thread (char *, int, int);
void	syslog (int, char *, ...);
void	log_team (int, char *, ...);
void	log_thread (int, char *, ...);
int		setlogmask (int);
int		setlogmask_team (int);
int		setlogmask_thread (int);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_LOG_H */
