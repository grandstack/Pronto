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

		bag(std::vector<entity<Segments ... >> && vector);

		bag(bag<entity<Segments ... >> const & other) = delete;
		bag(bag<entity<Segments ... >> && other) = default;

		bag<entity<Segments ... >> & operator = (bag<entity<Segments ... >> const & other) = delete;
		bag<entity<Segments ... >> & operator = (bag<entity<Segments ... >> && other) = default;

		type::bool_t contains(entity<Segments ... > const object) const;

		type::bool_t empty() const;
		type::index_t size() const;

		entity<Segments ... > front() const;
		entity<Segments ... > back() const;

		void reserve(type::index_t const count);

		void clear();

		entity<Segments ... > operator [] (type::index_t const index) const;

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