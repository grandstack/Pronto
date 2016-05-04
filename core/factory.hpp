#ifndef pronto_factory_header
#define pronto_factory_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "synchronizer.hpp"
#include "processing.hpp"

namespace pronto
{
	template <typename Type>
	range<Type> create(type::index_t const count);

	template <typename Type>
	void destroy(range<Type> & range);
}

#include "factory.inline.hpp"

#endif