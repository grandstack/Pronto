#ifndef pronto_synchronizer_inline_header
#define pronto_synchronizer_inline_header

#include "entity_lock.hpp"

namespace pronto
{
	namespace internal
	{
		namespace detail
		{
			template <typename Entity>
			type::bool_t & thread_lock_state()
			{
				thread_local type::bool_t state
				{
					false
				};

				return state;
			}
		}

		template <typename Current>
		inline type::bool_t aquire_entities()
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			auto & thread_state = detail::thread_lock_state<Current>();

			if (thread_state)
			{
				return true;
			}

			if (atomic.exchange(true))
			{
				return false;
			}

			else

			{
				thread_state = true;

				return true;
			}
		}

		template <typename Current, typename Next, typename ... Rest>
		inline type::bool_t  aquire_entities()
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			auto & thread_state = detail::thread_lock_state<Current>();

			if (thread_state)
			{
				if (aquire_entities<Next, Rest ... >())
				{
					return true;
				} return false;
			}

			if (atomic.exchange(true))
			{
				return false;
			}

			else

			{
				thread_state = true;

				if (aquire_entities<Next, Rest ... >())
				{
					return true;
				}

				else

				{
					atomic.store(false, std::memory_order_release);
					thread_state = false;

					return false;
				}
			}
		}

		template <typename Current>
		inline void release_entities()
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			auto & thread_state = detail::thread_lock_state<Current>();

			atomic.store(false, std::memory_order_release);
			thread_state = false;
		}

		template <typename Current, typename Next, typename ... Rest>
		inline void release_entities()
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			auto & thread_state = detail::thread_lock_state<Current>();

			release_entities<Next, Rest ... >();

			atomic.store(false, std::memory_order_release);
			thread_state = false;
		}
	}

	template <typename ... Entities, typename Functor>
	inline auto synchronize(Functor functor) -> typename std::enable_if<std::is_void<decltype(functor())>::value == true, decltype(functor())>::type
	{
		while (!(internal::aquire_entities<Entities ... >()))
		{
			std::this_thread::yield();
		}

		try
		{
			functor();
		}

		catch (...)
		{
			internal::release_entities<Entities ... >();

			throw;
		}

		internal::release_entities<Entities ... >();
	}

	template <typename ... Entities, typename Functor>
	inline auto synchronize(Functor functor) -> typename std::enable_if<std::is_void<decltype(functor())>::value == false, decltype(functor())>::type
	{
		while (!(internal::aquire_entities<Entities ... >()))
		{
			std::this_thread::yield();
		}

		try
		{
			decltype(auto) result = functor();

			internal::release_entities<Entities ... >();

			return result;
		}

		catch (...)
		{
			internal::release_entities<Entities ... >();

			throw;
		}
	}
}

#endif