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
				auto entity_index = static_cast<type::index_t>(activated.size());

				inflate_entity<Segments ... >(entity_index);
				activated.emplace_back(entity_index);

				return back;
			}

			auto back = destroyed.back();
			destroyed.pop_back();

			auto insertion_point = std::upper_bound(std::begin(activated), std::end(activated), back);

			inflate_entity<Segments ... >(back);
			activated.insert(insertion_point, back);

			return back;
		}

		template <typename ... Segments>
		inline bag<entity<Segments ... >> entity_pool<entity<Segments ... >>::create(type::index_t const count)
		{
			auto container = std::vector<entity<Segments ... >>
			{
				// ...
			};

			container.reserve(count);
			activated.reserve(count);

			auto available = destroyed.size();

			if (available > count)
			{
				auto head = destroyed.front();
				auto tail = destroyed.front();

				for (auto object : destroyed)
				{
					if ((available - head) < count)
					{
						break;
					}

					if (head != object - 1)
					{
						head = object;
						tail = object;
					}

					else

					{
						head = object;

						if ((head - tail) == count)
						{
							{
								auto begin = std::begin(destroyed) + (tail + 0);
								auto end = std::begin(destroyed) + (head + 1);

								container.insert(std::begin(container), begin, end);
								destroyed.erase(begin, end);

								for (auto object : container)
								{
									inflate_entity<Segments ... >(object);
								}
							}

							{
								auto insertion_point = std::upper_bound(std::begin(activated), std::end(activated), destroyed[tail]);

								auto begin = std::begin(container);
								auto end = std::end(container);

								activated.insert(insertion_point, begin, end);
							}

							return bag<entity<Segments ... >>
							{ 
								std::begin(container), 
								std::end(container)
							};
						}
					}
				}
			}

			container.resize(count, 0);

			for (auto & object : container)
			{
				auto index = static_cast<type::index_t>(activated.size());

				inflate_entity<Segments ... >(index);
				activated.emplace_back(index);
				object = index;
			}

			return bag<entity<Segments ... >>
			{ 
				std::begin(container), 
				std::end(container) 
			};
		}

		template <typename ... Segments>
		inline void entity_pool<entity<Segments ... >>::destroy(entity<Segments ... > const object)
		{
			if (valid(object))
			{
				auto begin = std::begin(activated);
				auto end = std::end(activated);

				auto position = std::find(begin, end, object);

				if (position != end)
				{
					auto insertion_point = std::upper_bound(std::begin(destroyed), std::end(destroyed), object);

					destroyed.insert(insertion_point, object);
					activated.erase(position);
				}
			}
		}

		template <typename ... Segments>
		inline void entity_pool<entity<Segments ... >>::destroy(bag<entity<Segments ... >> const & container)
		{
			{
				auto insertion_point = std::upper_bound(std::begin(destroyed), std::end(destroyed), container.front());

				auto begin = std::begin(container);
				auto end = std::end(container);

				destroyed.insert(insertion_point, begin, end);
			}

			{
				auto begin = std::lower_bound(std::begin(activated), std::end(activated), container.front());
				auto end = std::upper_bound(std::begin(activated), std::end(activated), container.back());

				activated.erase(begin, end);
			}
		}

		template <typename ... Segments>
		inline bool entity_pool<entity<Segments ... >>::contains(entity<Segments ... > const object) const
		{
			if (object < (activated.size() + destroyed.size()))
			{
				return true;
			}

			return false;
		}

		template <typename ... Segments>
		inline bool entity_pool<entity<Segments ... >>::valid(entity<Segments ... > const object) const
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