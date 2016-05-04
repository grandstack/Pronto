#ifndef pronto_range_utility_inline_header
#define pronto_range_utility_inline_header

namespace pronto
{
	namespace utility
	{
		template <typename ... Segments>
		inline range<entity<Segments ... >> join(range<entity<Segments ... >> const & one, range<entity<Segments ... >> const & two) noexcept
		{
			return { std::min(one.offset(), two.offset()), (std::max(one.back(), two.back()) + 1) - std::min(one.offset(), two.offset()) };
		}

		template <typename ... Segments>
		inline range<entity<Segments ... >> take_first(range<entity<Segments ... >> const & object, type::index_t const count) noexcept
		{
			return { object.offset(), count % (object.length() + 1) };
		}

		template <typename ... Segments>
		inline range<entity<Segments ... >> take_last(range<entity<Segments ... >> const & object, type::index_t const count) noexcept
		{
			return { object.back() - ((count % (object.length() + 1)) - 1), count % (object.length() + 1) };
		}

		// ----------------------------------------->

		template <typename ... Segments>
		inline type::bool_t intersects(range<entity<Segments ... >> const & one, range<entity<Segments ... >> const & two) noexcept
		{
			return (one.front() <= two.back()) && (two.front() <= one.back());
		}
	}
}

#endif