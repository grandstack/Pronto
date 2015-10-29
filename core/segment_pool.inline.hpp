#ifndef pronto_segment_pool_inline_header
#define pronto_segment_pool_inline_header

namespace pronto
{
	namespace internal
	{
		template <typename Segment, typename ... Segments>
		template <typename ... Parameters>
		inline void segment_pool<entity<Segments ... >, Segment>::create(entity<Segments ... > object, Parameters const & ... arguments)
		{
			if (object >= size())
			{
				segments.emplace_back(arguments ...);
			}

			else

				segments[object] = Segment
			{
				arguments ...
			};
		}

		template <typename Segment, typename ... Segments>
		template <typename ... Parameters>
		inline void segment_pool<entity<Segments ... >, Segment>::create(bag<entity<Segments ... >> const & container, Parameters const & ... arguments)
		{
			for (auto object : container)
			{
				if (object >= size())
				{
					segments.emplace_back(arguments ... );
				}

				else

				{
					segments[object] = Segment
					{
						arguments ...
					};
				}
			}
		}

		template <typename Segment, typename ... Segments>
		inline Segment & segment_pool<entity<Segments ... >, Segment>::operator [] (entity<Segments ... > const object)
		{
			return segments[object];
		}

		template <typename Segment, typename ... Segments>
		inline type::index_t segment_pool<entity<Segments ... >, Segment>::size() const
		{
			return static_cast<type::index_t>(segments.size());
		}
	}
}

#endif