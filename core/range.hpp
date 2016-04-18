#ifndef pronto_range_header
#define pronto_range_header

#include "entity.hpp"

namespace pronto
{
	namespace detail
	{
		template <typename>
		struct range_iterator;

		template <typename ... Segments>
		struct range_iterator<entity<Segments ... >>
		{
			range_iterator(type::index_t const value) noexcept;

			entity<Segments ... > operator * () const noexcept;

			range_iterator<entity<Segments ... >> & operator ++ () noexcept;
			range_iterator<entity<Segments ... >> & operator -- () noexcept;

			range_iterator<entity<Segments ... >> & operator += (type::index_t const value) noexcept;
			range_iterator<entity<Segments ... >> & operator -= (type::index_t const value) noexcept;

			type::bool_t operator < (range_iterator<entity<Segments ... >> const & other) const noexcept;
			type::bool_t operator > (range_iterator<entity<Segments ... >> const & other) const noexcept;

			type::bool_t operator == (range_iterator<entity<Segments ... >> const & other) const noexcept;
			type::bool_t operator != (range_iterator<entity<Segments ... >> const & other) const noexcept;

		private:

			type::index_t index = 0;
		};
	}

	template <typename>
	struct range;

	template <typename ... Segments>
	struct range<entity<Segments ... >>
	{
		range(type::index_t const offset, type::index_t const length) noexcept;

		range(range<entity<Segments ... >> const & other) = default;
		range(range<entity<Segments ... >> && other) = default;

		range<entity<Segments ... >> & operator = (range<entity<Segments ... >> const & other) = default;
		range<entity<Segments ... >> & operator = (range<entity<Segments ... >> && other) = default;

		detail::range_iterator<entity<Segments ... >> begin() const noexcept;
		detail::range_iterator<entity<Segments ... >> end() const noexcept;

		type::index_t operator [] (type::index_t const index) const noexcept;

		type::bool_t operator < (range<entity<Segments ... >> const & other) const noexcept;
		type::bool_t operator > (range<entity<Segments ... >> const & other) const noexcept;

		type::bool_t operator <= (range<entity<Segments ... >> const & other) const noexcept;
		type::bool_t operator >= (range<entity<Segments ... >> const & other) const noexcept;

		type::bool_t operator == (range<entity<Segments ... >> const & other) const noexcept;
		type::bool_t operator != (range<entity<Segments ... >> const & other) const noexcept;

		type::bool_t empty() const noexcept;

		type::index_t front() const noexcept;
		type::index_t back() const noexcept;

		type::index_t offset() const noexcept;
		type::index_t length() const noexcept;

	private:

		type::index_t offset_value = 0;
		type::index_t length_value = 0;
	};
}

#include "range.inline.hpp"
#include "range_utility.hpp"

#endif