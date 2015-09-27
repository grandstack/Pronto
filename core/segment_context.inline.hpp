#ifndef pronto_segment_context_inline_header
#define pronto_segment_context_inline_header

namespace pronto
{
	template <typename Segment, typename ... Segments>
	inline segment_pool<entity<Segments ... >, Segment> & segment_context<entity<Segments ... >, Segment>::get_pool()
	{
		static segment_pool<entity<Segments ... >, Segment> pool
		{
			// ...
		};

		return pool;
	}
}

#endif