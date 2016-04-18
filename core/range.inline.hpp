#ifndef pronto_range_inline_header
#define pronto_range_inline_header

namespace pronto
{
	namespace detail
	{
		template <typename ... Segments>
		inline range_iterator<entity<Segments ... >>::range_iterator(type::index_t const index) noexcept
		{
			range_iterator<entity<Segments ... >>::index = index;
		}

		template <typename ... Segments>
		inline entity<Segments ... > range_iterator<entity<Segments ... >>::operator * () const noexcept
		{
			return { index };
		}

		template <typename ... Segments>
		inline range_iterator<entity<Segments ... >> & range_iterator<entity<Segments ... >>::operator ++ () noexcept
		{
			index += 1;

			return { *(this) };
		}

		template <typename ... Segments>
		inline range_iterator<entity<Segments ... >> & range_iterator<entity<Segments ... >>::operator -- () noexcept
		{
			index -= 1;

			return { *(this) };
		}

		template <typename ... Segments>
		inline range_iterator<entity<Segments ... >> & range_iterator<entity<Segments ... >>::operator += (type::index_t const value) noexcept
		{
			range_iterator<entity<Segments ... >>::index += value;

			return { *(this) };
		}

		template <typename ... Segments>
		inline range_iterator<entity<Segments ... >> & range_iterator<entity<Segments ... >>::operator -= (type::index_t const value) noexcept
		{
			range_iterator<entity<Segments ... >>::index -= value;

			return { *(this) };
		}

		template <typename ... Segments>
		inline type::bool_t range_iterator<entity<Segments ... >>::operator < (range_iterator<entity<Segments ... >> const & other) const noexcept
		{
			return index < other.index;
		}

		template <typename ... Segments>
		inline type::bool_t range_iterator<entity<Segments ... >>::operator > (range_iterator<entity<Segments ... >> const & other) const noexcept
		{
			return index > other.index;
		}

		template <typename ... Segments>
		inline type::bool_t range_iterator<entity<Segments ... >>::operator == (range_iterator<entity<Segments ... >> const & other) const noexcept
		{
			return index == other.index;
		}

		template <typename ... Segments>
		inline type::bool_t range_iterator<entity<Segments ... >>::operator != (range_iterator<entity<Segments ... >> const & other) const noexcept
		{
			return index != other.index;
		}
	}

	template <typename ... Segments>
	inline range<entity<Segments ... >>::range(type::index_t const offset, type::index_t const length) noexcept
	:
		offset_value { offset },
		length_value { length }
	{
		// ...
	}

	template <typename ... Segments>
	inline detail::range_iterator<entity<Segments ... >> range<entity<Segments ... >>::begin() const noexcept
	{
		return { offset() };
	}

	template <typename ... Segments>
	inline detail::range_iterator<entity<Segments ... >> range<entity<Segments ... >>::end() const noexcept
	{
		return { offset() + length() };
	}

	template <typename ... Segments>
	inline type::index_t range<entity<Segments ... >>::operator [] (type::index_t const index) const noexcept
	{
		return (index % ((back() - front()) + 1)) + front();
	}

	template <typename ... Segments>
	inline type::bool_t range<entity<Segments ... >>::operator < (range<entity<Segments ... >> const & other) const noexcept
	{
		return back() < other.front();
	}

	template <typename ... Segments>
	inline type::bool_t range<entity<Segments ... >>::operator > (range<entity<Segments ... >> const & other) const noexcept
	{
		return front() > other.back();
	}

	template <typename ... Segments>
	inline type::bool_t range<entity<Segments ... >>::operator <= (range<entity<Segments ... >> const & other) const noexcept
	{
		return back() <= other.front();
	}

	template <typename ... Segments>
	inline type::bool_t range<entity<Segments ... >>::operator >= (range<entity<Segments ... >> const & other) const noexcept
	{
		return front() >= other.back();
	}

	template <typename ... Segments>
	inline type::bool_t range<entity<Segments ... >>::operator == (range<entity<Segments ... >> const & other) const noexcept
	{
		return (front() == other.front()) && (other.back() == back());
	}

	template <typename ... Segments>
	inline type::bool_t range<entity<Segments ... >>::operator != (range<entity<Segments ... >> const & other) const noexcept
	{
		return (front() != other.front()) && (other.back() != back());
	}

	template <typename ... Segments>
	inline type::bool_t range<entity<Segments ... >>::empty() const noexcept
	{
		return length() < 1;
	}

	template <typename ... Segments>
	inline type::index_t range<entity<Segments ... >>::front() const noexcept
	{
		return offset();
	}

	template <typename ... Segments>
	inline type::index_t range<entity<Segments ... >>::back() const noexcept
	{
		return length() > 0 ? (offset() + length()) - 1 : 0;
	}

	template <typename ... Segments>
	inline type::index_t range<entity<Segments ... >>::offset() const noexcept
	{
		return offset_value;
	}

	template <typename ... Segments>
	inline type::index_t range<entity<Segments ... >>::length() const noexcept
	{
		return length_value;
	}
}

#endif
