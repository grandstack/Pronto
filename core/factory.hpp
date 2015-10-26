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
	bag<Entity> create(type::index_t const count);

	template <typename Entity>
	void destroy(Entity const object);

	template <typename Entity>
	void destroy(bag<Entity> const & container);

	template <typename Entity>
	bool validate(Entity const object);

	template <typename Entity>
	bool validate(bag<Entity> const & container);
}

#include "factory.inline.hpp"

#endif