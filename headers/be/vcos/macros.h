/*****************************************************************************/
/*    MACROS.H
/*****************************************************************************/
/*                               VCOS (c)
/*                    Visible Caching Operating System
/*         Copyright 1989, 1990, 1991, 1992, AT&T Microelectronics
/*                         All Rights Reserved
/*
/* DSP3210 Register Usage Conventions:
/*     System macros destroy:               a0, a1, r1-r4, r16, r17
/*     System macros preserve:              a2, a3, r5-r15, r19
/*     System return pointer:               r18
/*     Error exception return pc:           r20      <-- don't modify
/*     System stack pointer, use only       r21
/*       for Push() and Pop():
/*     Interrupt vector pointer:            r22      <-- don't modify
/*
/* Warning! never use r1-r4, r16, or r17 as inputs to the macros.
/*          Instead, use r5-r15, or r19.
/*****************************************************************************/
#define   sp               r21           /* system stack pointer             */
#define   sAIAO            1             /* section type -- AIAO             */
#define   sFIFO            2             /* section type -- FIFO             */
#define   sPARAM           3             /* section type -- PARAM            */
#define   sPROG            0x100         /* section type -- CODE             */
/*===========================================================================*/




/*****************************************************************************/
/*    Module Header offsets
/*****************************************************************************/
#define   _mod_next       0
#define   _mod_flags      _mod_next  + 16
#define   _mod_entry      _mod_flags +  4
#define   _mod_sect0      _mod_entry +  4
/*===========================================================================*/




/*****************************************************************************/
/*    Section Header offsets
/*****************************************************************************/
#define   sect_cflags     0
#define   sect_tflags     sect_cflags + 4
#define   sect_daddr      sect_tflags + 4
#define   sect_haddr      sect_daddr  + 4
#define   sect_caddr      sect_haddr  + 4
#define   sect_size       sect_caddr  + 4
#define   sect_next       sect_size   + 4
/*===========================================================================*/




/*****************************************************************************/
/*    NewModule()
/*****************************************************************************/
#define NewModule(EntryPoint)                                                \
.align 4;                                                                    \
.rsect "__ModH",TEXT;                                                        \
.global _ModH;                                                               \
.global ___ModH;                                                             \
 ___ModH:                                                                    \
 2*long   0;               \
 2*long   0;               \
   long   1;               \
   long   EntryPoint;      \
 2*long   0;               \
   long   0;               \
 2*long   0;               \
   long   0;               \
   long   0;               \
   long   0;               \
 _ModH:                    
/*===========================================================================*/




/*****************************************************************************/
/*    NewSection()
/*****************************************************************************/
#define NewSection(SectionName, SectionType)                                 \
.align 4;                                                                    \
.rsect  @_cat "_" @_str SectionName,TEXT;                                    \
.global SectionName;                                                         \
.global @_lab @_cat "__" @_str SectionName;                                  \
@_lab @_cat "__" @_str SectionName:                                          \
   long   0;              \
   long   SectionType;    \
   long   0;              \
   long   0;              \
   long   0;              \
   long   0;              \
 2*long   0;              \
 SectionName:
/*===========================================================================*/




/*****************************************************************************/
/*    AppendSection()
/*****************************************************************************/
#define AppendSection(SectionName)                                           \
.align 4;                                                                    \
.rsect  @_cat "_" @_str SectionName,TEXT;
/*===========================================================================*/




/*****************************************************************************/
/*    LoadRunSection()
/*****************************************************************************/
#define LoadRunSection(SectionName, EntryName)                               \
    !r2= (long) _load;                                                       \
    r18= (long) EntryName;                                                   \
    !r1= (long) @_lab @_cat "__" @_str SectionName;                          \
    goto r2;                                                                 \
    nop;
/*===========================================================================*/




/*****************************************************************************/
/*    LoadSection()
/*****************************************************************************/
#define LoadSection(SectionName)                                             \
 !r2= (long) _load;                                                          \
 !r1= @_lab @_cat "__" @_str SectionName;                                    \
 call r2 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    SaveSection()
/*****************************************************************************/
#define SaveSection(SectionName)                                             \
 !r2= (long) _save;                                                          \
 !r1= @_lab @_cat "__" @_str SectionName;                                    \
 call r2 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    Push()
/*****************************************************************************/
#define Push(rS)                                                             \
 *sp++= (long) rS;          /* push extended registers (only) onto stack  */
/*===========================================================================*/




/*****************************************************************************/
/*    Pop()
/*****************************************************************************/
#define Pop(rD)                                                              \
 rD= (long)sp-4;            /* Load reg with top of stack                 */ \
 rD= (long)*rD;             /* pop it                                     */ \
 sp= (long)sp-4;            /* decrement sp                               */
/*===========================================================================*/




/*****************************************************************************/
/*    ReadFifo()
/*****************************************************************************/
/*
/* returns:
/*         r4= actual number of bytes transferred.
/*****************************************************************************/
#define ReadFifo(SectionName, ByteCount, DestinationAddress)                 \
 !r4= (long) _ReadFIFO;                                                      \
 r2=  ByteCount;                                                             \
 r3=  (long) DestinationAddress;                                             \
 !r1= (long) @_lab @_cat "__" @_str SectionName + sect_daddr;                \
 call r4 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    WriteFifo()
/*****************************************************************************/
/*
/* returns:
/*          r4= actual number of bytes transferred.
/*****************************************************************************/
#define WriteFifo(SectionName, ByteCount, SourceAddress)                     \
 !r4= (long)_WriteFIFO                                                       \
 r2=  ByteCount;                                                             \
 r3=  (long)SourceAddress;                                                   \
 !r1= (long)@_lab @_cat "__" @_str SectionName + sect_daddr;                 \
 call r4 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    GetFifoReadCount()
/*****************************************************************************/
/*
/* returns:
/*          r2= # of bytes available to be read from fifo.
/*****************************************************************************/
#define GetFifoReadCount(SectionName)                                        \
 !r2= (long) _FIFOReadCount;                                                 \
 !r1= (long) @_lab @_cat "__" @_str SectionName + sect_daddr;                \
 call r2 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    GetFifoWriteCount()
/*****************************************************************************/
/*
/* returns:
/*          r2= # of bytes that can be written to fifo.
/*****************************************************************************/
#define GetFifoWriteCount(SectionName)                                       \
 !r2= (long) _FIFOWriteCount;                                                \
 !r1= (long) @_lab @_cat "__" @_str SectionName + sect_daddr;                \
 call r2 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    GetFifoSize()
/*****************************************************************************/
/*
/* returns:
/*          r2= total fifo bytesize.
/*****************************************************************************/
#define GetFifoSize(SectionName)                                             \
 !r2= (long) _FIFOSize;                                                      \
 !r1= (long) @_lab @_cat "__" @_str SectionName + sect_daddr;                \
 call r2 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    GetSectionSize()
/*****************************************************************************/
/*
/* returns:
/*          r2= size of section in bytes.
/*****************************************************************************/
#define GetSectionSize(SectionName)                                          \
 !r1= (long) @_lab @_cat "__" @_str SectionName + sect_size;                 \
 r2=  (long)*r1;                                                             \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    SetBaseSR()
/*****************************************************************************/
#define SetBaseSR(LAB, rB)                                                   \
 !rB= sect LAB;
/*===========================================================================*/




/*****************************************************************************/
/*    SetBaseHSR()
/*****************************************************************************/
#define SetBaseHSR(LAB, rB)                                                  \
 !rB= host LAB;
/*===========================================================================*/




/*****************************************************************************/
/*    AddressSR()
/*****************************************************************************/
#define AddressSR(LAB, rB) rB + offset LAB
/*===========================================================================*/




/*****************************************************************************/
/*    AddressPR()
/*****************************************************************************/
#define AddressPR(LAB) pc + LAB - (.+8)
/*===========================================================================*/




/*****************************************************************************/
/*    Signal()
/*****************************************************************************/
#define Signal(VALUE)                                                        \
 !r1=  (long) _c_Signal + _mod_entry;    /* set by loader            */      \
 r2=   (long)*r1;                                                            \
 r17=  (long) VALUE;                                                         \
 !r16= (long)___ModH;                    /* r16 is ID of this module */      \
 call r2 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    CallChild()
/*****************************************************************************/
#define CallChild(ModuleName)                                                \
 !r1= (long) @_lab @_cat "_c_" @_str ModuleName + _mod_entry;                \
 r2=  (long)*r1;                                                             \
 nop;                                                                        \
 call r2 (r18);                                                              \
 nop;
/*===========================================================================*/




/*****************************************************************************/
/*    SetEntryPoint()
/*****************************************************************************/
#define SetEntryPoint(EntryPoint)                                            \
 !r1= (long)___ModH+_mod_entry;                                              \
 !r2= (long)EntryPoint;                                                      \
 *r1= (long)r2;
/*===========================================================================*/




/*****************************************************************************/
/*    SetIntVector()
/*****************************************************************************/
/* The user should note that vcos maintains the exception vector table
/* and a 2nd table called the isr vector table.  The exception vector table
/* is where execution begins immediately after an interrupt.  The isr vector
/* table contains 16 longs which are the 16 vectors set by this macro.
/* When an interrupt occurs, code in the exception vector table jumps to
/* a routine in vcos that pushes r1 and then fetches the appropriate vector
/* from the isr vector table.  The vcos routine then jumps to the vector (ie:
/* the user's isr). There are 7 instr after the interrupt before the users isr.
/*
/* To init an isr, the user should first invoke this macro, and then set one
/* interrupt enable bit in the emr.   NEVER modify any other bits in the emr.
/* NEVER modify r22 (r22= evtp = exception vector table ptr).    Beware! the
/* original r1 is already pushed by vcos before entering the user's isr.  The
/* user's isr should NOT push r1, but MUST pop r1 before executing an ireturn.
/*****************************************************************************/
#define SetIntVector(vectornum,isr_addr)          /* vectornum= 0 -> 15 */   \
 r1=  (long)isr_addr;                                                        \
 r2=  (long)r22 + (4*vectornum + 128);                                       \
 *r2= (long)r1;
/*========================  End Of Macros.h =================================*/

