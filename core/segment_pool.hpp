#ifndef pronto_segment_pool_header
#define pronto_segment_pool_header

#include "segment_context.hpp"
#include "entity.hpp"
#include "bag.hpp"

#include <functional>
#include <utility>
#include <memory>
#include <vector>

namespace pronto
{
	namespace internal
	{
		template <typename, typename>
		struct segment_pool;

		template <typename Segment, typename ... Segments>
		struct segment_pool <entity<Segments ... >, Segment>
		{
			using value_type = Segment;

			template <typename ... Parameters>
			void create(entity<Segments ... >, Parameters const & ...);

			template <typename ... Parameters>
			void create(bag<entity<Segments ... >> const &, Parameters const & ...);

			Segment & operator [] (entity<Segments ... >);

			type::index_t size() const;

		private:

			std::vector<Segment> segments
			{
				// ...
			};
		};
	}
}

#include "segment_pool.inline.hpp"

#endif