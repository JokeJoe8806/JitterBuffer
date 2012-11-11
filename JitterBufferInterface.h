#ifndef _I_JITTER_BUFFER_H
#define _I_JITTER_BUFFER_H

class IDecoder;
class IRenderer;

class IJitterBuffer
{
public:
	/*
	Should copy the given buffer, as it may be deleted/reused immediately following this call.
	@param frameNumber - will start at zero for the call
	@param fragmentNumber � specifies what position this fragment is within the given
	frame � the first fragment number in each frame is number zero
	@param numFragmentsInThisFrame - is guaranteed to be identical for all fragments
	with the same frameNumber
	*/
	virtual void ReceivePacket( const char*        pBuffer,
								const unsigned int length,
								const unsigned int frameNumber,
								const unsigned int fragmentNumber,
								const unsigned int numFragmentsInThisFrame) = 0;
	
	virtual ~IJitterBuffer() {}
};

#endif // _I_JITTER_BUFFER_H


