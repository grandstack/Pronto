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
				auto entity_index = size();

				inflate_entity<Segments ... >(entity_index);
				activated.emplace_back(entity_index);

				return back;
			}

			auto back = destroyed.back();
			destroyed.pop_back();

			auto entry = std::lower_bound(std::begin(activated), std::end(activated), back);

			inflate_entity<Segments ... >(back);
			activated.insert(entry, back);

			return back;
		}

		template <typename ... Segments>
		inline bag<entity<Segments ... >> entity_pool<entity<Segments ... >>::create(type::index_t const count)
		{
			auto container = std::vector<entity<Segments ... >>
			{
				// ...
			};

			if ((activated.capacity() - activated.size()) < count)
			{
				activated.reserve(((activated.size() + 1) / 2) + count);
			} 
			
			container.reserve(count);

			auto available = destroyed.size();

			if (available > count)
			{
				auto head = destroyed.front();
				auto tail = destroyed.front();

				for (auto object : destroyed)
				{
					if ((available - (head - tail)) < count)
					{
						break;
					}

					if ((head - tail) == count)
					{
						auto lower = std::lower_bound(std::begin(destroyed), std::end(destroyed), tail);
						auto upper = std::upper_bound(std::begin(destroyed), std::end(destroyed), head);

						container.insert(std::begin(container), lower, upper);
						destroyed.erase(lower, upper);

						auto entry = std::upper_bound(std::begin(activated), std::end(activated), tail);

						auto begin = std::begin(container);
						auto end = std::end(container);

						activated.insert(entry, begin, end);
						
						for (auto object : container)
						{
							inflate_entity<Segments ... >(object);
						}

						return bag<entity<Segments ... >>
						{
							std::move(container)
						};
					}

					if (head != object - 1)
					{
						head = object;
						tail = object;
					}

					else

					{
						head = object;
					}
				}
			}

			container.resize(count);

			for (auto & object : container)
			{
				auto index = size();

				inflate_entity<Segments ... >(index);
				activated.emplace_back(index);
				object = index;
			}

			return bag<entity<Segments ... >>
			{ 
				std::move(container) 
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
					auto entry = std::lower_bound(std::begin(destroyed), std::end(destroyed), object);

					destroyed.insert(entry, object);
					activated.erase(position);
				}
			}
		}

		template <typename ... Segments>
		inline void entity_pool<entity<Segments ... >>::destroy(bag<entity<Segments ... >> const & container)
		{
			if (valid(container.front()) && valid(container.back()))
			{
				auto entry = std::upper_bound(std::begin(destroyed), std::end(destroyed), container.front());

				auto begin = std::begin(container);
				auto end = std::end(container);

				destroyed.insert(entry, begin, end);

				auto lower = std::lower_bound(std::begin(activated), std::end(activated), container.front());
				auto upper = std::upper_bound(std::begin(activated), std::end(activated), container.back());

				activated.erase(lower, upper);
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
				auto begin = std::begin(activated);
				auto end = std::end(activated);

				return std::binary_search(begin, end, object);
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