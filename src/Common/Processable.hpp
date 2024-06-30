#pragma once

#include <concepts>

/* I notice you that AI() is the same with Process() */

template<typename T>
concept HasAI = requires(T x)
{
	T::Array; T::Array.empty(); T::Array.begin(); T::Array.end();
	//x.IsInLogic;
	x.AI();
};
template<typename T>
concept HasProcess = HasAI<T>;

template<typename ...TAI> requires (HasAI<TAI> && ...)
inline void __fastcall AI()
{
	([]
	{
		for (auto* pInstance : TAI::Array)
			//	if (pInstance->IsInLogic)
			pInstance->AI();
	}(), ...);
}
