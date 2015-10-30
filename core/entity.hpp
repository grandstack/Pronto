#ifndef pronto_entity_header
#define pronto_entity_header

#include "alias.hpp"

#include <vector>

namespace pronto
{
	template <typename ... Segments>
	struct entity
	{
		entity() = default;

		entity(type::index_t const index);

		operator type::index_t () const;

	private:

		type::index_t index
		{
			static_cast<type::index_t>(0) - 1
		};
	};
}

#include "entity.inline.hpp"

#endif