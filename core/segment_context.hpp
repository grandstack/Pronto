#ifndef pronto_segment_context_header
#define pronto_segment_context_header

#include "segment_pool.hpp"

namespace pronto
{
	namespace internal
	{
		template <typename, typename>
		struct segment_context;

		template <typename Segment, typename ... Segments>
		struct segment_context<entity<Segments ... >, Segment>
		{
			static segment_pool<entity<Segments ... >, Segment> & get_pool();
		};
	}
}

#include "segment_context.inline.hpp"

#endif