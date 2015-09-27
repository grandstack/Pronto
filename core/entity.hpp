#ifndef pronto_entity_header
#define pronto_entity_header

#include "alias.hpp"

namespace pronto
{
	template <typename ... Segments>
	struct entity
	{
		entity(type::index_t);

		operator type::index_t () const;

	private:

		type::index_t index;
	};
}

#include "entity.inline.hpp"

#endif