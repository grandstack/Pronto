#ifndef pronto_range_utility_header
#define pronto_range_utility_header

namespace pronto
{
	template <typename ... Segments>
	range<entity<Segments ... >> join(range<entity<Segments ... >> const & one, range<entity<Segments ... >> const & two) noexcept;

	template <typename ... Segments>
	range<entity<Segments ... >> take_first(range<entity<Segments ... >> const & object, type::index_t const count = 1) noexcept;

	template <typename ... Segments>
	range<entity<Segments ... >> take_last(range<entity<Segments ... >> const & object, type::index_t const count = 1) noexcept;

	// ----------------------------------------->

	template <typename ... Segments>
	type::bool_t intersects(range<entity<Segments ... >> const & one, range<entity<Segments ... >> const & two) noexcept;
}

#include "range_utility.inline.hpp"

#endif