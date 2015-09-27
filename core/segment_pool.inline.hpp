#ifndef pronto_segment_pool_inline_header
#define pronto_segment_pool_inline_header

namespace pronto
{
	template <typename Segment, typename ... Segments>
	inline void segment_pool<entity<Segments ... >, Segment>::create(entity<Segments ... > object)
	{
		if (object >= size())
		{
			segments.resize(static_cast<std::size_t>(object * 1.5));
			deleters.resize(static_cast<std::size_t>(object * 1.5));
		}
		
		auto pointer = new (std::addressof(segments[object])) Segment
		{
			// ...
		};

		auto & deleter = deleters[object];
		deleter.reset(pointer);
	}

	template <typename Segment, typename ... Segments>
	inline void segment_pool<entity<Segments ... >, Segment>::create(bag<entity<Segments ... >> const & container)
	{
		if (container.max() >= size())
		{
			segments.resize(size() + (container.max() - size()));
			deleters.resize(size() + (container.max() - size()));
		}

		for (auto object : container)
		{
			auto pointer = new (std::addressof(segments[object])) Segment
			{
				// ...
			};

			auto & deleter = deleters[object];
			deleter.reset(pointer);
		}
	}

	template <typename Segment, typename ... Segments>
	inline void segment_pool<entity<Segments ... >, Segment>::destroy(entity<Segments ... > object)
	{
		auto & deleter = deleters[object];
		deleter.reset();
	}

	template <typename Segment, typename ... Segments>
	inline void segment_pool<entity<Segments ... >, Segment>::destroy(bag<entity<Segments ... >> const & container)
	{
		for (auto object : container)
		{
			auto & deleter = deleters[object];
			deleter.reset();
		}
	}

	template <typename Segment, typename ... Segments>
	inline Segment & segment_pool<entity<Segments ... >, Segment>::operator [] (entity<Segments ... > object)
	{
		return reinterpret_cast<Segment(&)>(segments[object]);
	}

	template <typename Segment, typename ... Segments>
	inline type::index_t segment_pool<entity<Segments ... >, Segment>::size() const
	{
		return static_cast<type::index_t>(segments.size());
	}
}

#endif