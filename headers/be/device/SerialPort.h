//******************************************************************************
//
//	File:		SerialPort.h
//
//	Description:	Serial Port class header.
//	
//	Copyright 1995-96, Be Incorporated, All Rights Reserved.
//
//******************************************************************************

#ifndef	_SERIAL_PORT_H
#define	_SERIAL_PORT_H

// #include <termio.h>

#ifndef _OBJECT_H
#include <Object.h>
#endif

#ifndef _CLASS_INFO_H
#include <ClassInfo.h>
#endif

enum data_rate { B_0_BPS = 0, B_50_BPS, B_75_BPS, B_110_BPS, B_134_BPS,
				 B_150_BPS, B_200_BPS, B_300_BPS, B_600_BPS, B_1200_BPS,
				 B_1800_BPS, B_2400_BPS, B_4800_BPS, B_9600_BPS, B_19200_BPS,
				 B_38400_BPS, B_57600_BPS, B_115200_BPS };

enum data_bits { B_DATA_BITS_7, B_DATA_BITS_8 };

enum stop_bits { B_STOP_BITS_1, B_STOP_BITS_2 };
#define B_STOP_BIT_1	B_STOP_BITS_1

enum parity_mode { B_NO_PARITY, B_ODD_PARITY, B_EVEN_PARITY };

enum { B_NOFLOW_CONTROL = 0, B_HARDWARE_CONTROL = 0x00000001, 
								B_SOFTWARE_CONTROL = 0x00000002 };

// -----------------------------------------------------------------------
class BSerialPort : public BObject {
	B_DECLARE_CLASS_INFO(BObject);

public:
				BSerialPort();
virtual			~BSerialPort();

long			Open(const char *portName);
void			Close(void);

long			Read(void *buf, long count);
long			Write(const void *buf, long count);
void			SetBlocking(bool Blocking);
void			SetTimeout(double microSeconds);

void			SetDataRate(data_rate bitsPerSecond);
data_rate		DataRate(void);

void			SetDataBits(data_bits numBits);
data_bits		DataBits(void);
void			SetStopBits(stop_bits numBits);
stop_bits		StopBits(void);

void			SetParityMode(parity_mode which);
parity_mode		ParityMode(void);

void			ClearInput(void);
void			ClearOutput(void);

void			SetFlowControl(ulong method);
ulong			FlowControl(void);

long			SetDTR(bool asserted);
long			SetRTS(bool asserted);

bool			IsCTS(void);
bool			IsDSR(void);
bool			IsRI(void);
bool			IsDCD(void);

// -----------------------------------------------------------------------

private:

int				ffd;
data_rate		fBaudRate;
data_bits		fDataBits;
stop_bits		fStopBits;
parity_mode		fParityMode;
ulong			fFlow;
uchar			fTimeout;
bool			fBlocking;

int				DriverControl();
};

#endif
