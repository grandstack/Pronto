#ifndef pronto_alias_header
#define pronto_alias_header

#include <type_traits>
#include <atomic>

namespace pronto
{
	namespace type
	{
		using index_t = unsigned;

		namespace basic
		{
			template <typename Type>
			using pointer_t = Type(*);

			using unsigned_t = unsigned;
			using signed_t = signed;

			using bool_t = bool;
		}

		namespace atomic
		{
			template <typename Type>
			using pointer_t = std::atomic<Type(*)>;

			using unsigned_t = std::atomic<basic::unsigned_t>;
			using signed_t = std::atomic<basic::signed_t>;

			using bool_t = std::atomic<basic::bool_t>;
		}
	}
}

#include "alias.inline.hpp"

#endif