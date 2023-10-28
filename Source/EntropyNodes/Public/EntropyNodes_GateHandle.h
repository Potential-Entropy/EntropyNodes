#pragma once

/**
 * Executes a specified function if and only if the gate is open and provides functionality for opening/closing/toggling the gate.
 */
struct FGateHandle
{
private:
	const TFunction<void()> Function;
	bool bOpen = true;

public:
	/**
	 * @param Function The function to execute
	 */
	explicit FGateHandle(const TFunction<void()>& Function);

	/**
	 * Calls the specified function if the gate is open and does nothing otherwise
	 * @return A reference to the executed handle to support builder pattern like stuff
	 */
	FGateHandle& Execute();

	/**
	 * Opens the gate
	 */
	void Open();

	/**
	 * Closes the gate
	 */
	void Close();

	/**
	 * Toggles the state of this gate
	 */
	void Toggle();
};
