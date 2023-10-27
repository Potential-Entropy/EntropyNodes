#include "EntropyNodes_FlipFlopHandle.h"

FFlipFlopHandle::FFlipFlopHandle(const TFunction<void()>& Flip, const TFunction<void()>& Flop)
	: Flip(Flip),
	  Flop(Flop)
{
}

FFlipFlopHandle& FFlipFlopHandle::Execute()
{
	if (bFlip)
	{
		Flip();
	}
	else
	{
		Flop();
	}
	bFlip = !bFlip;
	return *this;
}
