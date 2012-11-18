#ifndef _C_JITTER_BUFFER_H
#define _C_JITTER_BUFFER_H

#include "JitterBufferInterface.h"

#include "Frame.h"
#include "LazyBuffer.h"

class CJitterBuffer : public IJitterBuffer
{
public:
	CJitterBuffer(IDecoder* pDecoder, IRenderer* pRenderer);
	
	/*
	Should copy the given buffer, as it may be deleted/reused immediately following this call.
	@param frameNumber - will start at zero for the call
	@param fragmentNumber � specifies what position this fragment is within the given
	frame � the first fragment number in each frame is number zero
	@param numFragmentsInThisFrame - is guaranteed to be identical for all fragments
	with the same frameNumber
	*/
	void ReceivePacket(const char*	pBuffer,
					   int			length,
					   int			frameNumber,
					   int			fragmentNumber,
					   int			numFragmentsInThisFrame);
	
	~CJitterBuffer();

private:
	CFrame			 mFrame;

	CLazyBuffer		 mRecievedFrame;

	char*			 mpDecodedFrame;
	int				 mDecodedFrameSize;

	int				 mLastCompletedFrameReceived; 

	IDecoder*		 mpDecoder;
	IRenderer*		 mpRenderer;

	static const int mOneMegabyte = 1024 * 1024;
};

#endif // _C_JITTER_BUFFER_H