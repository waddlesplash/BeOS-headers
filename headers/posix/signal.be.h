/*
 *	signal.be.h
 *	
 *		Copyright © 1996 Be, Inc.
 *		All rights reserved.
 */

#ifndef _signal_be_h_
#define _signal_be_h_

/*
   The numbering of signals for BeOS attempts to maintain 
   some consistency with UN*X conventions so that things 
   like "kill -9" do what you expect.
*/   
#define	SIGHUP      1      /* hangup -- tty is gone! */
#define SIGINT      2      /* interrupt */
#define SIGQUIT     3      /* `quit' special character typed in tty  */
#define SIGILL	    4      /* illegal instruction */
#define SIGCHLD     5      /* child process exited */
#define SIGABRT	    6      /* abort() called, dont' catch */
#define SIGPIPE	    7      /* write to a pipe w/no readers */
#define SIGFPE	    8      /* floating point exception */
#define SIGKILL	    9      /* kill a team (not catchable) */
#define SIGSTOP	   10      /* suspend a thread (not catchable) */
#define SIGSEGV	   11      /* segmentation violation (read: invalid pointer) */
#define SIGCONT    12      /* continue execution if suspended */
#define SIGTSTP	   13      /* `stop' special character typed in tty */
#define SIGALRM    14      /* an alarm has gone off (see alarm()) */
#define SIGTERM	   15      /* termination requested */
#define SIGTTIN	   16      /* read of tty from bg process */
#define SIGTTOU	   17      /* write to tty from bg process */
#define SIGUSR1	   18      /* app defined signal 1 */
#define SIGUSR2	   19      /* app defined signal 2 */
#define SIGWINCH   20      /* tty window size changed */
#define SIGKILLTHR 21      /* be specific: kill just the thread, not team */

#define SIGBUS     SIGSEGV /* for old style code */

/*
   Signal numbers 22-32 are currently free but may be used in future
   releases.  Use them at your own peril (if you do use them, at least
   be smart and use them backwards from signal 32).
*/
#define __signal_max  21
#define NSIG (__signal_max+1)


typedef long sigset_t;

/*
   The Posix interface for signal handling functions isn't as useful
   as it could be.  The standard indicates that only a single argument
   (the signal number) is passed to the signal handler.  It is useful
   to have more information and the BeOS provides two extra arguments.
   However, to remain compatible with Posix and ANSI C, we declare the
   sa_handler field of the sigaction struct as type __signal_func_ptr.
   That means you'll need to cast any function you assign to the
   sa_handler field.  NOTE: C++ member functions can not be signal
   handlers (because they expect a "this" pointer as the first
   argument).

   The 3 arguments that the BeOS provides to signal handlers are as
   follows:
    - The first argument is the signal number (as an integer).
	- The next argument is whatever value is put in the sa_userdata field
      of the sigaction struct.
	- The last argument is a pointer to a vregs struct (defined
	  below).  The vregs struct contains the contents of the volatile
	  registers at the time the signal was delivered to your thread.
	  You can change the fields of the structure.  After your signal
	  handler completes, the OS uses this struct to reload the
	  registers for your thread (privileged registers are not loaded
	  of course).  The vregs struct is of course terribly machine
	  dependent and is guaranteed to change, potentially even between
	  different models of the PowerPC family.  If you use it, you
	  should expect to have to re-work your code when new processors
	  come out.  Nonetheless the ability to change the registers does 
	  open some interesting programming possibilities.
*/
struct sigaction {
	__signal_func_ptr sa_handler;
	sigset_t          sa_mask;
	int               sa_flags;
	void             *sa_userdata;  /* will be passed to the signal handler */
};

#define SA_NOCLDSTOP  1  /* for sa_flags */


#include <sys/types.h>  /* for pid_t */

#ifdef __cplusplus
extern "C" {
#endif

int sigaction(int sig, const struct sigaction *act, struct sigaction *oact);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
int sigismember(const sigset_t *set, int signo);
int sigprocmask(int how, const sigset_t *set, sigset_t *oset);

#define SIG_BLOCK    1   /* defines for the how arg of sigprocmask() */
#define SIG_UNBLOCK  2
#define SIG_SETMASK  3

int sigpending(sigset_t *set);
int sigsuspend(const sigset_t *mask);

int kill(pid_t pid, int sig);
int send_signal(pid_t tid, uint sig);


/* signal handlers get this as the last argument */
typedef struct vregs
{
	ulong pc,                                         /* program counter */
	      r0,                                         /* scratch */
	      r1,                                         /* stack ptr */
	      r2,                                         /* TOC */
	      r3,r4,r5,r6,r7,r8,r9,r10,                   /* volatile regs */
	      r11,r12;                                    /* scratch regs */

   double f0,                                         /* fp scratch */
	      f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13; /* fp volatile regs */

	ulong filler1,                                    /* place holder */
	      fpscr,                                      /* fp condition codes */
	      ctr, xer, cr, msr, lr;                      /* misc. status */
}vregs;


extern const char * const sys_siglist[];
extern const char *strsignal(int sig);

#ifdef __cplusplus
}
#endif 

#endif /* _signal_be_h_ */
