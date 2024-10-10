#pragma once
#include "core.hpp"

/*!
* @author Multfinite
* @brief Interface for something that can be parsed from text file.
* @brief Now supports only INI files, but TODO: make parse(...) for JSON.
*/
struct IParseable
{
	/*!
	* @brief Parses data which object state-independent (invariant data). Any reference solving disallowed here.
	* @brief If something external can refer to own data of this object then all data must be initialized here (even instance created if nedeed).
	*/
	virtual void pre_parse(CCINIClass& ini, INI_EX& parser, std::string const& key) = 0;
	/*!
	* @brief Parses data which object state-dependent or need for lookup any other data.
	* @brief At this stage all object are exist and can be referensed by other objects. Reference solving should be placed here.
	*/
	virtual void post_parse(CCINIClass& ini, INI_EX& parser, std::string const& key) = 0;
	/*!
	* @briaf All object at this stage must be constructed already. Use to solve thing which can not be solvet at post_parse(...).
	*/
	virtual void post_init(CCINIClass& ini, INI_EX& parser, std::string const& key) = 0;
};
