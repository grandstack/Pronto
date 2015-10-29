#ifndef pronto_synchronizer_header
#define pronto_synchronizer_header

#include "entity_lock.hpp"

#include <thread>

namespace pronto
{
	namespace internal
	{
		namespace detail
		{
			template <typename Entity>
			type::bool_t & thread_lock_state();
		}

		template <typename Current, typename Functor>
		type::bool_t synchronize(Functor && functor) noexcept(noexcept(functor()));

		template <typename Current, typename Next, typename ... Rest, typename Functor>
		type::bool_t synchronize(Functor && functor) noexcept(noexcept(functor()));

		template <typename Current, typename Functor, typename Result>
		type::bool_t synchronize(Functor && functor, Result && result) noexcept(noexcept(functor()));

		template <typename Current, typename Next, typename ... Rest, typename Functor, typename Result>
		type::bool_t synchronize(Functor && functor, Result && result) noexcept(noexcept(functor()));
	}

	template <typename ... Entities, typename Functor>
	auto synchronize(Functor && functor) noexcept(noexcept(functor()))
		-> typename std::enable_if<std::is_void<decltype(functor())>::value == true, decltype(functor())>::type;

	template <typename ... Entities, typename Functor>
	auto synchronize(Functor && functor) noexcept(noexcept(functor()))
		-> typename std::enable_if<std::is_void<decltype(functor())>::value == false, decltype(functor())>::type;
}

#include "synchronizer.inline.hpp"

#endif