#ifndef pronto_bag_header
#define pronto_bag_header

#include "entity.hpp"

#include <algorithm>
#include <vector>

namespace pronto
{
	template <typename>
	struct bag;

	template <typename ... Segments>
	struct bag<entity<Segments ... >>
	{
		bag() = default;

		bag(bag<entity<Segments ... >> const & other) = default;
		bag(bag<entity<Segments ... >> && other) = default;

		void reserve(type::index_t);

		void insert(bag<entity<Segments ... >> const & container);
		void insert(entity<Segments ... > const object);

		void clear();

		void remove(bag<entity<Segments ... >> const & container);
		void remove(entity<Segments ... > const object);

		type::bool_t contains(entity<Segments ... > const object) const;

		type::index_t size() const;

		type::index_t min() const;
		type::index_t max() const;

		typename std::vector<entity<Segments ... >>::const_iterator begin() const;
		typename std::vector<entity<Segments ... >>::const_iterator end() const;

	private:

		std::vector<entity<Segments ... >> storage
		{
			// ...
		};
	};
}

#include "bag.inline.hpp"

#endif