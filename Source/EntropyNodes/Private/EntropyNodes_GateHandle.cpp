#include "EntropyNodes_GateHandle.h"

FGateHandle::FGateHandle(const TFunction<void()>& Function)
	: Function{Function}
{
}

FGateHandle& FGateHandle::Execute()
{
	if (bOpen)
	{
		Function();
	}
	return *this;
}

void FGateHandle::Open()
{
	bOpen = true;
}

void FGateHandle::Close()
{
	bOpen = false;
}

void FGateHandle::Toggle()
{
	bOpen = !bOpen;
}
