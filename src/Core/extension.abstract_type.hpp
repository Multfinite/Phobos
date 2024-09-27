#pragma once

#include <AbstractTypeClass.h>

#include "extension.abstract.hpp"

template<> class Extension<AbstractTypeClass> : public Extension<AbstractClass>, public Formatter::IParseable
{
	__EXTENSION_BODY(AbstractTypeClass, Extension<AbstractClass>::Offset)
public:
	using parent_type = Extension<AbstractClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
public:
	void pre_parse(CCINIClass& ini, INI_EX& parser, std::string const& prefix) override {};
	void post_parse(CCINIClass& ini, INI_EX& parser, std::string const& prefix) override {};
	void post_init(CCINIClass& ini, INI_EX& parser, std::string const& prefix) override {};
};

template<> struct Proxy<AbstractTypeClass> : public AbstractClass
{
	__PROXY_BODY(AbstractTypeClass)
	__PROXY_MEMORY_MANAGEMENT
};

