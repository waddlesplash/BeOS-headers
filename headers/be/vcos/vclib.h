/* VCAS function prototypes
* Copyright 1992, AT&T Microelectronics, all rights reserved 
*/

#ifdef __CPLUSPLUS__
extern "C" {
#endif

long  vcBootDsp(int  Dspid);
long  vcResetDsp(int  Dspid);
long  vcStartDsp(int  Dspid);
long  vcStopDsp(int  Dspid);

long  vcStartTask(int  Tid);
long  vcAddTask(int  dspid,char  *Tname,int  *Tnum);
long  vcDeleteTask(int  Tsk_handle);
long  vcStopTask(int  tsk);

long  vcGetFifoSize(long  handle,long  *size);
long  vcGetFifoHandle(int  Tid,char  *IO_alias,long  *lvcFifoHandle);
long  vcGetHostParamPtr(int  Tid,char  *IO_alias,char  * *ptr);
long  vcGetDspParamHandle(int  Tid,char  *IO_alias,long  *lvcParamHandle);
long  vcUpdateDspParam(long  handle);
long  vcUpdateHostParam(long  handle);
long  vcUpdateHostParamItem(long  handle,long  ByteOffset,long  count);
long  vcUpdateDspParamItem(long  handle,long  ByteOffset,long  count);
long  vcWriteFifo(long  handle,long  count,long  *from);
long  vcReadFifo(long  handle,long  count,long  *from);
long  vcUpdateFifoReadPtr(long  handle,long  count);
long  vcUpdateFifoWritePtr(long  handle,long  count);
long  vcGetFifoReadCount(long  handle,long  *rcount);
long  vcGetFifoWriteCount(long  handle,long  *wcount);
long  vcGetFifoWritePtr(long  handle,long  *count,long  * *Writeptr);
long  vcGetFifoReadPtr(long  handle,long  *count,long  * *Readptr);
long  vcInitFifo(long  handle);
unsigned long  vcLogToDspPhys(unsigned long  laddr);
unsigned long  vcDspPhysToLog(unsigned long  paddr);

#ifdef __CPLUSPLUS__
}
#endif