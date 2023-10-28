#pragma once

#include <array>
#include <tuple>

/**
 * A class mimicking the behaviour of the multigate Blueprint node.<br>
 * It is recommended to use the aliases FMultiGateHandle, FNonLoopingMultiGateHandle or FRandomMultiGateHandle. 
 * @tparam bLoop Whether the gate loops after calling every function
 * @tparam bRandom Whether the gate chooses a random function
 * @tparam Size The number of functions in this multigate. Deduced automatically
 */
template <bool bLoop = true, bool bRandom = false, int Size = 0>
struct TMultiGateHandle
{
private:
	std::array<TFunction<void()>, Size> Functions;
	std::conditional_t<bRandom, std::tuple<>, int> CurrentIndex;

public:
	/**
	 * @tparam T Should always be deduced automatically
	 * @param Functions The functions to be executed
	 */
	template <std::convertible_to<TFunction<void()>> ...T>
	explicit TMultiGateHandle(const T&... Functions);

	/**
	 * Executes a function specified by the behaviour and the state of this gate
	 * @return The handle this was executed on to support builder pattern like stuff
	 */
	TMultiGateHandle& Execute();

	/**
	 * Resets the gate to the default index (does nothing in random multigates)
	 */
	void Reset();
};

template <bool bLoop, bool bRandom, int Size>
template <std::convertible_to<TFunction<void()>> ... T>
TMultiGateHandle<bLoop, bRandom, Size>::TMultiGateHandle(const T&... Functions)
	: Functions{Functions...}
{
	static_assert(!(bLoop && bRandom), "You cannot loop in a random multigate!");
}

// Template deduction rule for the constructor
template <bool bLoop = true, bool bRandom = false, std::convertible_to<TFunction<void()>> ... T>
TMultiGateHandle(const T&...) -> TMultiGateHandle<bLoop, bRandom, sizeof...(T)>;

template <bool bLoop, bool bRandom, int Size>
TMultiGateHandle<bLoop, bRandom, Size>& TMultiGateHandle<bLoop, bRandom, Size>::Execute()
{
	if constexpr (bRandom)
	{
		Functions[FMath::RandRange(0, Size - 1)]();
	}
	else
	{
		if constexpr (!bLoop)
		{
			if (CurrentIndex >= Size)
			{
				return *this;
			}
		}
		Functions[CurrentIndex]();
		++CurrentIndex;
		if constexpr (bLoop)
		{
			CurrentIndex %= Size;
		}
	}
	return *this;
}

template <bool bLoop, bool bRandom, int Size>
void TMultiGateHandle<bLoop, bRandom, Size>::Reset()
{
	if constexpr (!bRandom)
	{
		CurrentIndex = 0;
	}
}

/**
 * Wrapper for TMultiGateHandle that loops, i.e., starts at index 0 ans returns to index 0 when the last function was called
 */
template <int Size>
struct FMultiGateHandle : TMultiGateHandle<true, false, Size>
{
	template<std::convertible_to<TFunction<void()>> ...T>
	explicit FMultiGateHandle(const T&... Functions) : TMultiGateHandle<true, false, Size>(Functions...)
	{
	}
};

template<std::convertible_to<TFunction<void()>> ...T>
FMultiGateHandle(const T&... Functions) -> FMultiGateHandle<sizeof...(T)>;

/**
 * Wrapper for TMultiGateHandle that starts at index 0 and stops once all functions were called until it is reset
 */
template <int Size>
struct FMultiGateNonLoopingHandle : TMultiGateHandle<false, false, Size>
{
	template<std::convertible_to<TFunction<void()>> ...T>
	explicit FMultiGateNonLoopingHandle(const T&... Functions) : TMultiGateHandle<false, false, Size>(Functions...)
	{
	}
};

template<std::convertible_to<TFunction<void()>> ...T>
FMultiGateNonLoopingHandle(const T&... Functions) -> FMultiGateNonLoopingHandle<sizeof...(T)>;

/**
 * Wrapper for TMultiGateHandle that randomizes execution.<br>
 * Calling reset on a FRandomMultiGateHandle does nothing.
 */
template <int Size>
struct FRandomMultiGateHandle : TMultiGateHandle<false, true, Size>
{
	template<std::convertible_to<TFunction<void()>> ...T>
	explicit FRandomMultiGateHandle(const T&... Functions) : TMultiGateHandle<false, true, Size>(Functions...)
	{
	}
};

template<std::convertible_to<TFunction<void()>> ...T>
FRandomMultiGateHandle(const T&... Functions) -> FRandomMultiGateHandle<sizeof...(T)>;
