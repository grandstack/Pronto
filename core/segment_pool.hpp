#ifndef pronto_segment_pool_header
#define pronto_segment_pool_header

#include "segment_context.hpp"
#include "range.hpp"

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
			void create(range<entity<Segments ... >> const & range);
			void destroy(range<entity<Segments ... >> const & range);

			Segment & operator [] (entity<Segments ... > const object);

		private:

			std::vector<Segment> segments
			{
				// ...
			};
		};

		// ----------------------------------------->

		template <typename ... Segments>
		struct segment_pool <entity<Segments ... >, entity<Segments ... >>
		{
			entity<Segments ... > operator [] (entity<Segments ... > const object);

		private:

			range<entity<Segments ... >> const segments
			{
				0, value::infinity
			};
		};
	}
}

#include "segment_pool.inline.hpp"

#endif