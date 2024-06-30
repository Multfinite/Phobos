#pragma once

#include <Utilities/Concepts.h>

template<typename TExtension, typename T>
concept __IsExtensionInitializable_HasInitialize_Template = requires(typename TExtension::base_type* x)
{
	T::template Initialize<TExtension>(x);
};
template<typename TExtension, typename T>
concept __IsExtensionInitializable_HasInitialize_Overload= requires(typename TExtension::base_type* x)
{
	T::Initialize(x);
};

template<typename TExtension, typename T>
concept IsExtensionInitializable =
		__IsExtensionInitializable_HasInitialize_Template<TExtension, T>
	//||  __IsExtensionInitializable_HasInitialize_Overload<TExtension, T>
;

template<typename TExtension, typename ...T> requires (IsExtensionInitializable<TExtension, T> && ...)
inline void __fastcall Initialize(typename TExtension::base_type* on)
{
	([&]
	{
		//if (__IsExtensionInitializable_HasInitialize_Overload<TExtension, T>)
		//	T::Initialize(on);
		//else if (__IsExtensionInitializable_HasInitialize_Template<TExtension, T>)
			T::template Initialize<TExtension>(on);
		//else
		//	static_assert(false, "T::Initialize template/overload not found.");
	}(), ...);
}
