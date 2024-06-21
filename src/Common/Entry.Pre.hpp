#pragma once

template<typename T, typename TExtension>
concept IsDataEntriedType = requires(
	typename T::data_entry * dePtr,
	typename T::data_entry & de,
	typename T::parent_type * parent, typename TExtension::ExtData * pExt)
{
	typename T::parent_type;
	typename T::data_entry;
	dePtr = T::EntryOf(parent);
	de = T::template EntryOf(pExt);
};
