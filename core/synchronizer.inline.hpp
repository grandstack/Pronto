#ifndef pronto_synchronizer_inline_header
#define pronto_synchronizer_inline_header

#include "entity_lock.hpp"

namespace pronto
{
	namespace internal
	{
		template <typename Current>
		inline bool aquire_entities()
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			if (atomic.exchange(true))
			{
				return false;
			}

			return true;
		}

		template <typename Current, typename Next, typename ... Rest>
		inline bool aquire_entities()
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			if (atomic.exchange(true))
			{
				return false;
			}

			else

			{
				if (aquire_entities<Next, Rest ... >())
				{
					return true;
				}

				else

				{
					atomic.store(false);

					return false;
				}
			}
		}

		template <typename Current>
		inline void release_entities()
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			atomic.store(false);
		}

		template <typename Current, typename Next, typename ... Rest>
		inline void release_entities()
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			release_entities<Next, Rest ... >();
			atomic.store(false);
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

		internal::release_entities<Entities ... >();
	}
}

#endif