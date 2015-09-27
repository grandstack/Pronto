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

		bag(bag<entity<Segments ... >> &) = default;
		bag(bag<entity<Segments ... >> &&) = default;

		void reserve(type::index_t);

		void insert(bag<entity<Segments ... >> const &);
		void insert(entity<Segments ... >);

		void remove(bag<entity<Segments ... >> const &);
		void remove(entity<Segments ... >);

		void clear();

		type::basic::bool_t contains(entity<Segments ... >) const;

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