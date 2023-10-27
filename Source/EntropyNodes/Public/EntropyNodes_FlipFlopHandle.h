#pragma once

/**
 * Handle for a FlipFlop.<br>
 * Handles need to be kept alive to keep their state!
 */
struct FFlipFlopHandle
{
private:
	TFunction<void()> Flip;
	TFunction<void()> Flop;
	bool bFlip = true;

public:
	/**
	 * @param Flip First function to be executed
	 * @param Flop Second function to be executed
	 */
	FFlipFlopHandle(const TFunction<void()>& Flip, const TFunction<void()>& Flop);

	/**
	 * Executes one of the functions associated with this handle depending on its state
	 * @return A reference to the handle it was executed on to support builder pattern like stuff
	 */
	FFlipFlopHandle& Execute();
};
