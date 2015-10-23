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

		template <typename Current>
		type::bool_t aquire_entities();

		template <typename Current, typename Next, typename ... Rest>
		type::bool_t aquire_entities();

		template <typename Current>
		void release_entities();

		template <typename Current, typename Next, typename ... Rest>
		void release_entities();
	}

	template <typename ... Entities, typename Functor>
	inline auto synchronize(Functor functor) -> typename std::enable_if<std::is_void<decltype(functor())>::value == true, decltype(functor())>::type;

	template <typename ... Entities, typename Functor>
	inline auto synchronize(Functor functor) -> typename std::enable_if<std::is_void<decltype(functor())>::value == false, decltype(functor())>::type;
}

#include "synchronizer.inline.hpp"

#endif