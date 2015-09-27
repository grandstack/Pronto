#ifndef pronto_entity_context_header
#define pronto_entity_context_header

#include "entity_pool.hpp"

namespace pronto
{
	template <typename>
	struct entity_context;

	template <typename ... Segments>
	struct entity_context<entity<Segments ... >>
	{
		static entity_pool<entity<Segments ... >> & get_pool();
	};
}

#include "entity_context.inline.hpp"

#endif