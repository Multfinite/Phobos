#pragma once

/*!
* @brief This must be specialized;
* @param T can be any Extension or ExtensionType
*/
template<typename T>
#if 1
struct extension_traits;
#else
struct extension_traits
{
	using type = AbstractTypeClassExt;
	using instance = AbstractClassExt;
};
#endif
