/* ++++++++++
	debugdsp.h
	Copyright (C) 1993 Be Inc.  All Rights Reserved.
	Definitions for debugging dsp code

	Modification History (most recent first):
	28 may 93	rwh	new today
+++++ */

#ifndef _debugdsph_
#define _debugdsph_

/* ---
   Some usesful macros for tracing your code with a logic analyser:

   debughere (constant_val)
	writes the constant (-32768..32767) to the location db_loc. 
	trashes: r1, r2

   debugval (expression)
	writes the expression to the location db_loc + 4.  Any expression
	that can be used in the statment "r2 = expression" is legal.
	trashes: r1, r2
--- */

#ifndef DEBUG

#define debughere(constant_val)
#define debugval(expression)

#else

#define db_loc 0x60000050
#define db_loc_reg r1
#define db_val_reg r2
#define debughere(constant_val) \
	!db_loc_reg = db_loc \
	db_val_reg = r0 + constant_val \
	*db_loc_reg = db_val_reg

#define debugval(expression) \
	db_val_reg = expression \
	!db_loc_reg = db_loc+4 \
	*db_loc_reg = db_val_reg

#define debugfreg(freg) \
	!db_loc_reg = db_loc+4 \
	*db_loc_reg = freg = freg
#endif

/* ---
   A macro for working around the doblock bug in F10 and F11 parts.
--- */

#define FixDoBlock(src_expr, dstreg, cntreg, scratch1, scratch2, label) \
	scratch1 = cntreg - 7 \
	scratch2 = dstreg \
	scratch2 = scratch2 >> 2 \
	scratch2 = scratch2 & 3 \
	scratch1 = scratch1 - scratch2 \
	scratch1 = scratch1 & 3 \
	if (ne) pcgoto @_lab @_cat "ok_" @_str label \
	scratch2 = cntreg - 1 \
	doblock scratch2 \
	a0 = (*dstreg++ = src_expr)*a0 \
	a0 = (*dstreg++ = src_expr)*a0 \
	pcgoto @_lab @_cat "end_" @_str label \
	nop \
@_lab @_cat "ok_" @_str label: \
	doblock cntreg \
	a0 = (*dstreg++ = src_expr)*a0 \
@_lab @_cat "end_" @_str label: \
	nop \
	nop \
	nop

#endif
