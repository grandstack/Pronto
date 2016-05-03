#ifndef pronto_segment_pool_inline_header
#define pronto_segment_pool_inline_header

namespace pronto
{
	namespace internal
	{
		template <typename Segment, typename ... Segments>
		inline void segment_pool<entity<Segments ... >, Segment>::create(range<entity<Segments ... >> const & range)
		{
			segments.reserve(static_cast<std::size_t>((segments.size() + range.length()) * 1.5));

			for (auto object : range)
			{
				if (object >= segments.size())
				{
					segments.emplace_back();
				}

				else

				{
					segments[object] = Segment
					{
						// ...
					};
				}
			}
		}

		template <typename Segment, typename ... Segments>
		inline void segment_pool<entity<Segments ... >, Segment>::destroy(range<entity<Segments ... >> const & range)
		{
			if (segments.size() == range.back())
			{
				segments.resize(segments.size() - range.length());
				segments.shrink_to_fit();
			}
		}

		template <typename Segment, typename ... Segments>
		inline Segment & segment_pool<entity<Segments ... >, Segment>::operator [] (entity<Segments ... > const object)
		{
			return segments[object];
		}

		// ----------------------------------------->

		template <typename ... Segments>
		inline entity<Segments ... > segment_pool<entity<Segments ... >, entity<Segments ... >>::operator [] (entity<Segments ... > const object)
		{
			return segments[object];
		}
	}
}

#endif