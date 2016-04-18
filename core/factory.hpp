#ifndef pronto_factory_header
#define pronto_factory_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "synchronizer.hpp"
#include "process.hpp"

namespace pronto
{
	template <typename Entity>
	range<Entity> create(type::index_t const count);

	template <typename Entity>
	void destroy(range<Entity> const & range);
}

#include "factory.inline.hpp"

#endif