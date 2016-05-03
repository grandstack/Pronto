#ifndef pronto_entity_pool_header
#define pronto_entity_pool_header

#include "segment_context.hpp"
#include "inflation.hpp"
#include "utility.hpp"
#include "range.hpp"

#include <algorithm>

namespace pronto
{
	namespace internal
	{
		template <typename>
		struct entity_pool;

		template <typename ... Segments>
		struct entity_pool<entity<Segments ... >>
		{
			using value_type = entity<Segments ... >;

			range<entity<Segments ... >> create(type::index_t const count);

			void destroy(range<entity<Segments ... >> & range);

		private:

			std::vector<range<entity<Segments ... >>> activated
			{
				// ...
			};

			std::vector<range<entity<Segments ... >>> destroyed
			{
				// ...
			};
		};
	}
}

#include "entity_pool.inline.hpp"

#endif