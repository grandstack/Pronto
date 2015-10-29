#ifndef pronto_bag_inline_header
#define pronto_bag_inline_header

namespace pronto
{
	template <typename ... Segments>
	template <typename Iterator>
	inline bag<entity<Segments ... >>::bag(Iterator first, Iterator last)
	{
		storage.reserve(std::distance(first, last));
		storage.insert(std::begin(storage), first, last);
	}

	template <typename ... Segments>
	inline type::bool_t bag<entity<Segments ... >>::contains(entity<Segments ... > const object) const
	{
		return std::binary_search(std::begin(storage), std::end(storage), object);
	}

	template <typename ... Segments>
	entity<Segments ... > bag<entity<Segments ... >>::front() const
	{
		if (storage.empty())
		{
			throw std::out_of_range
			{
				"calling front on empty bag!"
			};
		}

		return storage.front();
	}

	template <typename ... Segments>
	entity<Segments ... > bag<entity<Segments ... >>::back() const
	{
		if (storage.empty())
		{
			throw std::out_of_range
			{
				"calling back on empty bag!"
			};
		}

		return storage.back();
	}

	template <typename ... Segments>
	inline type::bool_t bag<entity<Segments ... >>::empty() const
	{
		return static_cast<type::bool_t>(storage.empty());
	}

	template <typename ... Segments>
	inline type::index_t bag<entity<Segments ... >>::size() const
	{
		return static_cast<type::index_t>(storage.size());
	}

	template <typename ... Segments>
	inline void bag<entity<Segments ... >>::reserve(type::index_t const count)
	{
		storage.reserve(count);
	}

	template <typename ... Segments>
	inline void bag<entity<Segments ... >>::clear()
	{
		storage.clear();
	}

	template <typename ... Segments>
	entity<Segments ... > bag<entity<Segments ... >>::operator [] (type::index_t const index) const
	{
		return storage[index];
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