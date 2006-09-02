/* stripped down from Linux headers */

/* Copyright (C) 1996, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#ifndef	_SYS_IO_H
#define	_SYS_IO_H	1


/* If TURN_ON is TRUE, request for permission to do direct i/o on the
   port numbers in the range [FROM,FROM+NUM-1].  Otherwise, turn I/O
   permission off for that range.  This call requires root privileges.

   Portability note: not all Linux platforms support this call.  Most
   platforms based on the PC I/O architecture probably will, however.
   E.g., Linux/Alpha for Alpha PCs supports this.  */
extern int ioperm (unsigned long int __from, unsigned long int __num,
                   int __turn_on);

/* Set the I/O privilege level to LEVEL.  If LEVEL>3, permission to
   access any I/O port is granted.  This call requires root
   privileges. */
extern int iopl (int __level);

extern unsigned char
inb (unsigned short int port);

extern unsigned char
inb_p (unsigned short int port);

extern unsigned short int
inw (unsigned short int port);

extern unsigned short int
inw_p (unsigned short int port);

extern unsigned int
inl (unsigned short int port);

extern unsigned int
inl_p (unsigned short int port);

extern void
outb (unsigned char value, unsigned short int port);

extern void
outb_p (unsigned char value, unsigned short int port);

extern void
outw (unsigned short int value, unsigned short int port);

extern void
outw_p (unsigned short int value, unsigned short int port);

extern void
outl (unsigned int value, unsigned short int port);

extern void
outl_p (unsigned int value, unsigned short int port);

extern void
insb (unsigned short int port, void *addr, unsigned long int count);

extern void
insw (unsigned short int port, void *addr, unsigned long int count);

extern void
insl (unsigned short int port, void *addr, unsigned long int count);

extern void
outsb (unsigned short int port, const void *addr, unsigned long int count);

extern void
outsw (unsigned short int port, const void *addr, unsigned long int count);

extern void
outsl (unsigned short int port, const void *addr, unsigned long int count);

#endif /* _SYS_IO_H */
