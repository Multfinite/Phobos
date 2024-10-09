#pragma once

#include <TaskForceClass.h>

#include "extension.abstract_type.hpp"

template<> class Extension<TaskForceClass> : public Extension<AbstractTypeClass>
{
	__EXTENSION_BODY(TaskForceClass, Extension<AbstractTypeClass>::Offset)
public:
	using parent_type = Extension<AbstractTypeClass>;
protected:
	constexpr Extension(base_type& base) : parent_type(base) { }
};

template<> struct Proxy<TaskForceClass> : public TaskForceClass
{
	__PROXY_BODY(TaskForceClass)
	__PROXY_MEMORY_MANAGEMENT
};

