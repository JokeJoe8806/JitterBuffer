
#include "Frame.h"

#include <assert.h>

CFrame::CFrame()
:
	mFragmentsRemaining(0),
    mFrameSizeInBytes(0)
{
}

void CFrame::Reset(const int numberOfFragments)
{
	mFragmentsRemaining = numberOfFragments;

	mSeenFragment.resize(numberOfFragments);
	std::fill(mSeenFragment.begin(), mSeenFragment.end(), false);

	mFragments.resize(numberOfFragments);

	mFrameSizeInBytes = 0;
}

void CFrame::AddFragment(const char* pBuffer,
						 const int   length,
					     const int   fragmentNumber)
{
	const bool bFragmentsRemaining     = mFragmentsRemaining > 0;
	const bool bFragmentNotSeenAlready = !(mSeenFragment[fragmentNumber]); 

	assert(bFragmentsRemaining);
	assert(bFragmentNotSeenAlready);

	if (bFragmentsRemaining && bFragmentNotSeenAlready)
	{
		mFragments[fragmentNumber].Copy(pBuffer, length);
		mSeenFragment[fragmentNumber] = true;

		mFragmentsRemaining--;
		mFrameSizeInBytes += length;
	}
}

bool CFrame::Completed() const
{
	return (0 == mFragmentsRemaining);
}

void CFrame::Combine(CLazyBuffer& outputBuffer)
{
    if (Completed())
    {
	    outputBuffer.SetCurrentSize(mFrameSizeInBytes);

	    int  offset = 0;
	    for (size_t i = 0; i < mFragments.size(); i++)
	    {
		    outputBuffer.SubCopy(mFragments[i].Pointer(), mFragments[i].CurrentSize(), offset); 
		    offset += mFragments[i].CurrentSize();
	    }
    }
}
