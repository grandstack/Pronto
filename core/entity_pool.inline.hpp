#ifndef pronto_entity_pool_inline_header
#define pronto_entity_pool_inline_header

namespace pronto
{
	namespace internal
	{
		template <typename ... Segments>
		inline entity<Segments ... > entity_pool<entity<Segments ... >>::create()
		{
			if (destroyed.empty())
			{
				activated.emplace_back(static_cast<type::index_t>(activated.size()));

				auto & back = activated.back();
				inflate_entity<Segments ... >(back);

				return back;
			}

			auto begin = std::begin(activated);
			auto end = std::end(activated);

			auto back = destroyed.back();
			destroyed.pop_back();

			inflate_entity<Segments ... >(back);
			activated.insert(std::upper_bound(begin, end, back), back);

			return back;
		}

		template <typename ... Segments>
		inline bag<entity<Segments ... >> entity_pool<entity<Segments ... >>::create(type::index_t size)
		{
			auto container = bag<entity<Segments ... >>
			{
				// ...
			};

			container.reserve(size);

			for (type::index_t i = 0; i < size; ++i)
			{
				container.insert(create());
			}

			return container;
		}

		template <typename ... Segments>
		inline void entity_pool<entity<Segments ... >>::destroy(entity<Segments ... > object)
		{
			if (valid(object))
			{
				auto begin = std::begin(activated);
				auto end = std::end(activated);

				auto position = std::find(begin, end, object);

				if (position != end)
				{
					destroyed.push_back(object);
					activated.erase(position);
				}
			}
		}

		template <typename ... Segments>
		inline void entity_pool<entity<Segments ... >>::destroy(bag<entity<Segments ... >> const & container)
		{
			for (auto object : container)
			{
				destroy(object);
			}
		}

		template <typename ... Segments>
		inline bool entity_pool<entity<Segments ... >>::contains(entity<Segments ... > object) const
		{
			if (object < (activated.size() + destroyed.size()))
			{
				return true;
			}

			return false;
		}

		template <typename ... Segments>
		inline bool entity_pool<entity<Segments ... >>::valid(entity<Segments ... > object) const
		{
			if (contains(object))
			{
				return std::binary_search(std::begin(activated), std::end(activated), object);
			}

			return false;
		}

		template <typename ... Segments>
		inline type::index_t entity_pool<entity<Segments ... >>::size() const
		{
			return static_cast<type::index_t>(activated.size() + destroyed.size());
		}

		template <typename ... Segments>
		inline type::index_t entity_pool<entity<Segments ... >>::size_activated() const
		{
			return static_cast<type::index_t>(activated.size());
		}

		template <typename ... Segments>
		inline type::index_t entity_pool<entity<Segments ... >>::size_destroyed() const
		{
			return static_cast<type::index_t>(destroyed.size());
		}
	}
}

#endif