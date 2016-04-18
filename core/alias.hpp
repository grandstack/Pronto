#ifndef pronto_alias_header
#define pronto_alias_header

#include <type_traits>
#include <atomic>

namespace pronto
{
	namespace type
	{
		template <typename Type>
		using pointer_t = Type(*);

		// ----------------------------------------->

		using unsigned_t = unsigned;
		using signed_t = signed;
		using bool_t = bool;

		// ----------------------------------------->

		using index_t = unsigned_t;

		// ----------------------------------------->

		namespace atomic
		{
			template <typename Type>
			using pointer_t = std::atomic<Type(*)>;

			using unsigned_t = std::atomic<type::unsigned_t>;
			using signed_t = std::atomic<type::signed_t>;
			using bool_t = std::atomic<type::bool_t>;

			using index_t = std::atomic<type::index_t>;
		}
	}

	namespace value
	{
		constexpr auto invalid = static_cast<type::index_t>(0) - 1;
	}
}

#include "alias.inline.hpp"

#endif