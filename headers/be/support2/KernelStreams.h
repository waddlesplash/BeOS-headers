/******************************************************************************
/
/	File:			KernelStreams.h
/
/	Copyright 1993-98, Be Incorporated
/
******************************************************************************/

#ifndef	_SUPPORT2_KERNELSTREAMS_H
#define	_SUPPORT2_KERNELSTREAMS_H

#include <sys/uio.h>
#include <support2/SupportDefs.h>
#include <support2/ByteStream.h>

namespace B {
namespace Support2 {

/*---------------------------------------------------------------------*/

class BKernelOStr : public LByteOutput
{
	public:
								BKernelOStr(int32 descriptor);
		virtual					~BKernelOStr();
		
		virtual	ssize_t			WriteV(const struct iovec *vector, ssize_t count, uint32 flags = 0);
		virtual	status_t		Sync();

	private:

				int32			m_descriptor;
};

/*-------------------------------------------------------------*/

class BKernelIStr : public LByteInput
{
	public:
								BKernelIStr(int32 descriptor);
		virtual					~BKernelIStr();
		
		virtual	ssize_t			ReadV(const struct iovec *vector, ssize_t count);

	private:

				int32			m_descriptor;
};

/*-------------------------------------------------------------*/

} } // namespace B::Support2

#endif /* _SUPPORT2_KERNELSTREAMS_H */
