#ifndef pronto_bag_inline_header
#define pronto_bag_inline_header

namespace pronto
{
	template <typename ... Segments>
	inline void bag<entity<Segments ... >>::insert(bag<entity<Segments ... >> const & other)
	{
		auto begin = std::begin(storage);
		auto end = std::end(storage);

		for (auto & object : other)
		{
			storage.insert(std::upper_bound(begin, end, object), object);
		}
	}

	template <typename ... Segments>
	inline void bag<entity<Segments ... >>::insert(entity<Segments ... > object)
	{
		auto begin = std::begin(storage);
		auto end = std::end(storage);

		storage.insert(std::upper_bound(begin, end, object), object);
	}

	template <typename ... Segments>
	inline void bag<entity<Segments ... >>::remove(bag<entity<Segments ... >> const & other)
	{
		auto begin = std::begin(storage);
		auto end = std::end(storage);

		for (auto & object : other)
		{
			storage.erase(std::upper_bound(begin, end, object));
		}
	}

	template <typename ... Segments>
	inline void bag<entity<Segments ... >>::remove(entity<Segments ... > object)
	{
		auto begin = std::begin(storage);
		auto end = std::end(storage);

		storage.erase(std::upper_bound(begin, end, object));
	}

	template <typename ... Segments>
	inline void bag<entity<Segments ... >>::clear()
	{
		storage.clear();
	}

	template <typename ... Segments>
	inline type::bool_t bag<entity<Segments ... >>::contains(entity<Segments ... > object) const
	{
		return std::binary_search(std::begin(storage), std::end(storage), object);
	}

	template <typename ... Segments>
	inline type::index_t bag<entity<Segments ... >>::size() const
	{
		return static_cast<type::index_t>(storage.size());
	}

	template <typename ... Segments>
	inline type::index_t bag<entity<Segments ... >>::min() const
	{
		if (storage.empty())
		{
			throw std::out_of_range
			{
				"calling min on empty bag!"
			};
		}

		return static_cast<type::index_t>(storage.front());
	}

	template <typename ... Segments>
	inline type::index_t bag<entity<Segments ... >>::max() const
	{
		if (storage.empty())
		{
			throw std::out_of_range
			{
				"calling max on empty bag!"
			};
		}

		return static_cast<type::index_t>(storage.back());
	}

	template <typename ... Segments>
	inline void bag<entity<Segments ... >>::reserve(type::index_t size)
	{
		storage.reserve(size);
	}

	template <typename ... Segments>
	inline typename std::vector<entity<Segments ... >>::const_iterator bag<entity<Segments ... >>::begin() const
	{
		return std::begin(storage);
	}

	template <typename ... Segments>
	inline typename std::vector<entity<Segments ... >>::const_iterator bag<entity<Segments ... >>::end() const
	{
		return std::end(storage);
	}
}

#endif