/* ++++++++++
	mmio.h
	Copyright (C) 1992 Company X.  All Rights Reserved.
	Definitions for the DSP3210 memory mapped io registers.

	Taken from "DSP3210 Signal Processor, The Multimedia Solution"
	information manual, September 1991 (the grey book).

	Modification History (most recent first):
	15 may 92	rwh	new today
+++++ */

#ifndef _mmioh_
#define _mmioh_

/* ---
   memory mapped i/o register addresses
--- */

#define ibuf	0x404		/* (32 bits) serial input buffer */
#define obuf	0x408		/* (32) serial output buffer */
#define ioc	0x40c		/* (32) serial input/output control */

#define tcon	0x413		/* (8) timer control */
#define timer	0x414		/* (32) timer value */

#define bioc	0x41b		/* (8) bit i/o configuration */
#define bio	0x41e		/* (16) bit i/o value */

#define idp	0x420		/* (32) dma input pointer */
#define odp	0x424		/* (32) dma output pointer */
#define icnt	0x42a		/* (16) dma input transfer count */
#define ocnt	0x42e		/* (16) dma output transfer count */
#define dmac	0x433		/* (8) dma configuration */

/* ---
   ioc (serial input/output control) bit definitions (manual page 9-4,5)
--- */

#define ioc_ASY    0x00000001	/* 1/0 SY internal/external */
#define ioc_BC     0x00000002	/* 1/0 use OCK/ICK to get load, SY */
#define ioc_SLEN   0x0000000C	/* internal SY timing - see below */
#define ioc_AIC    0x00000010	/* 1/0 ICK internal/external */
#define ioc_AIL    0x00000020	/* 1/0 ILD internal/external */
#define ioc_ILEN   0x000000C0	/* # input bits - see below */
#define ioc_AOC    0x00000100	/* 1/0 OCK internal/external */
#define ioc_AOL    0x00000200	/* 1/0 OLD internal/external */
#define ioc_OLEN   0x00001C00	/* # output bits - see below */
#define ioc_BO     0x00002000	/* 1/0 intrnl OLD is burst/([IO]CK/32) */
#define ioc_IIC    0x00004000	/* 1/0 ICK inverted/not inverted */
#define ioc_SAN    0x00008000	/* 1/0 set/clear sanity bit */
#define ioc_IN     0x00010000	/* 1/0 receive MSB/LSB first */
#define ioc_OUT    0x00020000	/* 1/0 send MSB/LSB first */
#define ioc_ISZ    0x00040000	/* 1/0 input dma xfer size = ILEN/32 */
#define ioc_OSZ    0x00080000	/* 1/0 output dma xfer size = OLEN/32 */
#define ioc_ICN    0x00F00000	/* dsp clock divisor for internal bit clock */

/* ---
   ioc_SLEN (internal SY timing) definitions (manual p 9-4,5)
--- */

#define ioc_SLEN_32   0x00000000	/* internal SY = internal load/32 */
#define ioc_SLEN_8    0x00000004	/* internal SY = internal load/8 */
#define ioc_SLEN_16   0x00000008	/* internal SY = internal load/16 */
#define ioc_SLEN_32x  0x0000000C	/* internal SY = internal load/32 */

/* ---
   ioc_ILEN (length of serial input data) definitions (manual p 9-4,5)
--- */

#define ioc_ILEN_32p  0x00000000	/* input length = 32 bits, prior to ILD */
#define ioc_ILEN_8    0x00000040	/* input length = 8 bits, after ILD */
#define ioc_ILEN_16   0x00000080	/* input length = 16 bits, after ILD */
#define ioc_ILEN_32   0x000000C0	/* input length = 32 bits, after ILD */

/* ---
   ioc_OLEN (length of serial output data) definitions (manual p 9-4,5)
--- */

#define ioc_OLEN_8    0x00000400	/* output length = 8 bits */
#define ioc_OLEN_16   0x00000800	/* output length = 16 bits */
#define ioc_OLEN_32   0x00000C00	/* output length = 32 bits */
#define ioc_OLEN_24   0x00001000	/* output length = 24 bits */

/* ---
   ioc_ICN (internal clock divisor) values (manual p 9-4,6,10)
--- */
#define ioc_ICN_off	0x00000000	/* internal clock disabled */
#define ioc_ICN_div4	0x00100000	/* bit clock = CKI/4 */
#define ioc_ICN_div8	0x00200000	/* bit clock = CKI/8 */
#define ioc_ICN_div12	0x00300000	/* bit clock = CKI/12 */
#define ioc_ICN_div16	0x00400000	/* bit clock = CKI/16 */
#define ioc_ICN_div20	0x00500000	/* bit clock = CKI/20 */
#define ioc_ICN_div24	0x00600000	/* bit clock = CKI/24 */
#define ioc_ICN_div28	0x00700000	/* bit clock = CKI/28 */
#define ioc_ICN_div32	0x00800000	/* bit clock = CKI/32 */
#define ioc_ICN_div36	0x00900000	/* bit clock = CKI/36 */
#define ioc_ICN_div40	0x00A00000	/* bit clock = CKI/49 */
#define ioc_ICN_div44	0x00B00000	/* bit clock = CKI/44 */
#define ioc_ICN_div48	0x00C00000	/* bit clock = CKI/48 */
#define ioc_ICN_div52	0x00D00000	/* bit clock = CKI/52 */
#define ioc_ICN_div56	0x00E00000	/* bit clock = CKI/56 */
#define ioc_ICN_div60	0x00F00000	/* bit clock = CKI/60 */

/* ---
   dmac (dma configuration) bit definitions (manual page 9-20)
--- */

#define dmac_OCS	0x01	/* 1/0 change/preserve output settings */
				/*     dmac[1,2] on write */
#define dmac_ODE	0x02	/* 1/0 output dma enable/disable */
#define dmac_ORS	0x04	/* 1/0 reload/stop on output dma complete */
#define dmac_ORB	0x08	/* 1/0 wait/don't wait for bus for output (??) */
#define dmac_ICS	0x10	/* 1/0 change/preserve input settings */
				/*     dmac[4,5] on write */
#define dmac_IDE	0x20	/* 1/0 input dma enable/disable */
#define dmac_IRS	0x40	/* 1/0 reload/stop on input dma complete */
#define dmac_IRB	0x80	/* 1/0 wait/don't wait for bus for input (??) */

/* ---
   tcon (timer configuration) bit definitions (manual page 9-23)
--- */

#define tcon_E_HN	0x01	/* 1/0 enable/hold count */
#define tcon_R_SN	0x02	/* 1/0 reload/stop on zero count */
#define tcon_T_PN	0x04	/* 1/0 output is toggled/pulsed on zero count */
#define tcon_H_LN	0x08	/* 1/0 if pulsed, pulse is active high/low */
#define tcon_OUT	0x01	/* 1/0 en/disable timer output to BIO1 pin */
#define tcon_SRC	0xE0	/* select timer clock source (see below) */

/* ---
   tcon_SRC (select timer clock source) definitions (manual p 9-23)
--- */

#define tcon_SRC_CKI_2		0x00	/* timer clock = dsp clock (CKI) / 2 */
#define tcon_SRC_CKI_4		0x20	/* timer clock = dsp clock (CKI) / 4 */
#define tcon_SRC_BIO0_rise	0xA0	/* timer clock = BIO[0], rising edge */
#define tcon_SRC_BIO0_fall	0xC0	/* timer clock = BIO[0], falling edge */

#endif

