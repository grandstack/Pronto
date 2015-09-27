#ifndef pronto_entity_pool_header
#define pronto_entity_pool_header

#include "segment_context.hpp"
#include "utility.hpp"
#include "bag.hpp"

#include <algorithm>

namespace pronto
{
	template <typename>
	struct entity_pool;

	template <typename ... Segments>
	struct entity_pool<entity<Segments ... >>
	{
		using value_type = entity<Segments ... >;

		entity<Segments ... > create();
		bag<entity<Segments ... >> create(type::index_t);

		void destroy(entity<Segments ... >);
		void destroy(bag<entity<Segments ... >> const &);

		type::basic::bool_t contains(entity<Segments ... >) const;
		type::basic::bool_t valid(entity<Segments ... >) const;

		type::index_t size() const;

		type::index_t size_destroyed() const;
		type::index_t size_activated() const;
		
	private:

		std::vector<entity<Segments ... >> activated
		{
			// ...
		};

		std::vector<entity<Segments ... >> destroyed
		{
			// ...
		};
	};
}

#include "entity_pool.inline.hpp"

#endif