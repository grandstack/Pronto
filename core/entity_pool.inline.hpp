#ifndef pronto_entity_pool_inline_header
#define pronto_entity_pool_inline_header

namespace pronto
{
	namespace internal
	{
		template <typename ... Segments>
		inline range<entity<Segments ... >> entity_pool<entity<Segments ... >>::create(type::index_t const count)
		{
			if (!destroyed.empty())
			{
				auto recycled = destroyed.front();

				for (auto & object : destroyed)
				{
					if (recycled.length() >= count)
					{
						auto remaining = utility::take_last(recycled, recycled.length() - count);
						auto result = utility::take_first(recycled, count);

						destroyed.erase(std::remove_if(std::begin(destroyed), std::end(destroyed), [&] (auto & entry)
						{
							return utility::intersects(recycled, result);
						}), std::end(destroyed));

						activated.insert(std::upper_bound(std::begin(activated), std::end(activated), result), result);

						if (remaining.empty())
						{
							return result;
						}

						destroyed.insert(std::upper_bound(std::begin(destroyed), std::end(destroyed), remaining), remaining);

						return result;
					}

					if ((recycled.back() + 1) != object.front())
					{
						recycled = object;

						continue;
					}

					recycled = utility::join(recycled, object);
				}
			}

			auto one = activated.empty() ? 0 : activated.back().back() + 1;
			auto two = destroyed.empty() ? 0 : destroyed.back().back() + 1;

			activated.emplace_back(std::max(one, two), count);

			return activated.back();
		}

		template <typename ... Segments>
		inline void entity_pool<entity<Segments ... >>::destroy(range<entity<Segments ... >> & range)
		{
			activated.erase(std::remove_if(std::begin(activated), std::end(activated), [&](auto const & entry)
			{
				if (utility::intersects(range, entry))
				{
					destroyed.insert(std::upper_bound(std::begin(destroyed), std::end(destroyed), entry), entry);

					return true;
				} return false;
			}), std::end(activated));

			range = { 0, 0 };
		}
	}
}

#endif