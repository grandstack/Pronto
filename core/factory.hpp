#ifndef pronto_factory_header
#define pronto_factory_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "synchronizer.hpp"
#include "process.hpp"

namespace pronto
{
	template <typename Entity>
	Entity create();

	template <typename Entity>
	bag<Entity> create(type::index_t);

	template <typename Entity>
	void destroy(Entity);

	template <typename Entity>
	void destroy(bag<Entity> const &);

	template <typename Entity>
	bool validate(Entity);

	template <typename Entity>
	bool validate(bag<Entity> const &);
}

#include "factory.inline.hpp"

#endif