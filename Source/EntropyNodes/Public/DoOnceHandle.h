#pragma once

/**
 * Handle for a DoOnce.<br>
 * Handles need to be kept alive to keep their state!<br>
 */
struct FDoOnceHandle
{
private:
	const TFunction<void()> Function;
	bool bOpen;

public:
	/**
	 * @param Function The function to execute by Do()
	 * @param bStartClosed Whether we start closed
	 */
	explicit FDoOnceHandle(const TFunction<void()>& Function, const bool bStartClosed = false);

	/**
	 * Execute the assigned function if we are open
	 * @return The handle it was executed on (returned for support for builder pattern like stuff, i.e., FDoOnceHandle([]{}).Do())
	 */
	FDoOnceHandle& Do();

	/**
	 * Resets the Handle to open
	 * @return The handle it was executed on (returned for support for builder pattern like stuff)
	 */
	FDoOnceHandle& Reset();
};
