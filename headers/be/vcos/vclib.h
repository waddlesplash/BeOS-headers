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

long  vcAddTask(int  dspid,char  *Tname,int  *Tnum);
long  vcDeleteTask(int  Tsk_handle);
long  vcStartTask(int  Tid);
long  vcStopTask(int  tsk);
long  vcAddTaskIndirect (int dspid, char *TaskName, char *tbdbuf, int *Tid);
long  vcInitTaskIos (int Tid);

long  vcGetFifoHandle(int  Tid,char  *IO_alias,long  *lvcFifoHandle);
long  vcGetFifoReadCount(long  handle,long  *rcount);
long  vcGetFifoWriteCount(long  handle,long  *wcount);
long  vcMergeFifo (int Tid, char *ioname1, char *ioname2);
long  vcReadFifo(long  handle,long  count,long  *from);
long  vcWriteFifo(long  handle,long  count,long  *from);
long  vcGetFifoSize(long  handle,long  *size);
long  vcInitFifo(long  handle);

long  vcGetFifoReadPtr(long  handle,long  *count,long  * *Readptr);
long  vcGetFifoWritePtr(long  handle,long  *count,long  * *Writeptr);
long  vcUpdateFifoWritePtr(long  handle,long  count);
long  vcUpdateFifoReadPtr(long  handle,long  count);

long  vcGetHostParamPtr(int  Tid,char  *IO_alias,char  * *ptr);
long  vcGetDspParamHandle(int  Tid,char  *IO_alias,long  *lvcParamHandle);
long  vcUpdateHostParam(long  handle);
long  vcUpdateDspParam(long  handle);
long  vcUpdateDspParamItem(long  handle,long  ByteOffset,long  count);
long  vcUpdateHostParamItem(long  handle,long  ByteOffset,long  count);
long  vcReadAtomic (long ParamHandle, long Offset);
long  vcWriteAtomic (long ParamHandle, long Offset, long Value);

#ifdef __CPLUSPLUS__
}
#endif
