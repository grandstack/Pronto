#ifndef pronto_entity_lock_header
#define pronto_entity_lock_header

#include "entity.hpp"

namespace pronto
{
	namespace internal
	{
		template <typename>
		struct entity_lock;

		template <typename ... Segments>
		struct entity_lock<entity<Segments ... >>
		{
			static type::atomic::bool_t & get_state();
		};
	}
}

#include "entity_lock.inline.hpp"

#endif