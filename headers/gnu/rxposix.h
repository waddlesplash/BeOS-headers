/* classes: h_files */

#ifndef INST_RXPOSIXH
#define INST_RXPOSIXH
/***********************************************************

Copyright 1995 by Tom Lord

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of the copyright holder not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

Tom Lord DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
EVENT SHALL TOM LORD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

******************************************************************/



struct rx_posix_regex
{
  struct rexp_node * pattern;
  struct rexp_node ** subexps;
  int n_subexps;
  unsigned char * translate;
  unsigned int newline_anchor:1;/* If true, an anchor at a newline matches.*/
  unsigned int no_sub:1;	/* If set, don't  return register offsets. */
  unsigned int is_anchored:1;
  unsigned char fastmap[256];
};

typedef struct rx_posix_regex regex_t;


/*
 * POSIX `cflags' bits (i.e., information for `regcomp').
 */

/* If this bit is set, then use extended regular expression syntax.
 * If not set, then use basic regular expression syntax.  
 */
#define REG_EXTENDED 1

/* If this bit is set, then ignore case when matching.
 * If not set, then case is significant.
 */
#define REG_ICASE (REG_EXTENDED << 1)
 
/* If this bit is set, then anchors do not match at newline
 *   characters in the string.
 * If not set, then anchors do match at newlines.  
 */
#define REG_NEWLINE (REG_ICASE << 1)

/* If this bit is set, then report only success or fail in regexec.
 * If not set, then returns differ between not matching and errors.  
 */
#define REG_NOSUB (REG_NEWLINE << 1)


/*
 * POSIX `eflags' bits (i.e., information for regexec).  
 */

/* If this bit is set, then the beginning-of-line operator doesn't match
 *   the beginning of the string (presumably because it's not the
 *   beginning of a line).
 * If not set, then the beginning-of-line operator does match the
 *   beginning of the string.  
 */
#define REG_NOTBOL 1

/* Like REG_NOTBOL, except for the end-of-line.  
 */
#define REG_NOTEOL (1 << 1)


#ifdef __STDC__
extern int regcomp (regex_t * preg, const char * pattern, int cflags);
extern size_t regerror (int errcode, const regex_t *preg,
			char *errbuf, size_t errbuf_size);
extern int rx_regmatch (regmatch_t *pmatch,
			regex_t *preg,
			struct rx_context_rules * rules,
			int start, int end, char *string);
extern int rx_regexec (regmatch_t *pmatch,
		       regex_t *preg,
		       struct rx_context_rules * rules,
		       int start,
		       int end,
		       char *string);
extern int regnexec (regex_t *preg, int len, char *string,
		     size_t nmatch, regmatch_t *pmatch,
		     int eflags);
extern int regexec (regex_t *preg, char *string,
		    size_t nmatch, regmatch_t *pmatch,
		    int eflags);
extern void regfree (regex_t *preg);

#else /* STDC */
extern int regcomp ();
extern size_t regerror ();
extern int rx_regmatch ();
extern int rx_regexec ();
extern int regnexec ();
extern int regexec ();
extern void regfree ();

#endif /* STDC */






#endif  /* INST_RXPOSIXH */
