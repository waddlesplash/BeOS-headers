//******************************************************************************
//
//	File:		A2D.h
//
//	Description:	Analog-to-Digital converter class header.
//	
//	Copyright 1996, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_A2D_H
#define	_A2D_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#ifndef _OBJECT_H
#include <Object.h>
#endif

// -----------------------------------------------------------------------
class BA2D : public BObject {

public:
				BA2D();
virtual			~BA2D();

long			Open(const char *portName);
void			Close(void);
bool			IsOpen(void);

long			Read(ushort *buf);

// -----------------------------------------------------------------------

private:

int				ffd;
};

#endif
