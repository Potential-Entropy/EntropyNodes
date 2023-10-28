#include "EntropyNodes_DoOnceHandle.h"

FDoOnceHandle::FDoOnceHandle(const TFunction<void()>& Function, const bool bStartClosed)
	: Function{Function},
	  bOpen{!bStartClosed}
{
}

FDoOnceHandle& FDoOnceHandle::Do()
{
	if (bOpen)
	{
		bOpen = false;
		Function();
	}
	return *this;
}

FDoOnceHandle& FDoOnceHandle::Reset()
{
	bOpen = true;
	return *this;
}

bool FDoOnceHandle::IsOpen()
{
	return bOpen;
}
