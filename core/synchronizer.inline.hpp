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

		template <typename Current, typename Functor>
		type::bool_t synchronize(Functor && functor) noexcept(noexcept(functor()))
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			auto & thread_state = detail::thread_lock_state<Current>();

			if (thread_state)
			{
				functor();

				return true;
			}

			if (atomic.exchange(true))
			{
				return false;
			}

			else

			{
				thread_state = true;

				try
				{
					functor();

					thread_state = false;
					atomic.store(false, std::memory_order_release);

					return true;
				}

				catch (...)
				{
					thread_state = false;
					atomic.store(false, std::memory_order_release);

					throw;
				}
			}
		}

		template <typename Current, typename Next, typename ... Rest, typename Functor>
		type::bool_t synchronize(Functor && functor) noexcept(noexcept(functor()))
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			auto & thread_state = detail::thread_lock_state<Current>();

			if (thread_state)
			{
				if (synchronize<Next, Rest ... >(std::forward<Functor>(functor)))
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

				try
				{
					if (synchronize<Next, Rest ... >(std::forward<Functor>(functor)))
					{
						thread_state = false;
						atomic.store(false, std::memory_order_release);

						return true;
					}

					else

					{
						thread_state = false;
						atomic.store(false, std::memory_order_release);

						return false;
					}
				}

				catch (...)
				{
					thread_state = false;
					atomic.store(false, std::memory_order_release);

					throw;
				}
			}
		}

		template <typename Current, typename Functor, typename Result>
		type::bool_t synchronize(Functor && functor, Result && result) noexcept(noexcept(functor()))
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			auto & thread_state = detail::thread_lock_state<Current>();

			if (thread_state)
			{
				result = functor();

				return true;
			}

			if (atomic.exchange(true))
			{
				return false;
			}

			else

			{
				thread_state = true;

				try
				{
					result = functor();

					thread_state = false;
					atomic.store(false, std::memory_order_release);

					return true;
				}

				catch (...)
				{
					thread_state = false;
					atomic.store(false, std::memory_order_release);

					throw;
				}
			}
		}

		template <typename Current, typename Next, typename ... Rest, typename Functor, typename Result>
		type::bool_t synchronize(Functor && functor, Result && result) noexcept(noexcept(functor()))
		{
			thread_local auto & atomic = entity_lock<Current>::get_state();

			auto & thread_state = detail::thread_lock_state<Current>();

			if (thread_state)
			{
				if (synchronize<Next, Rest ... >(std::forward<Functor>(functor), std::forward<Result>(result)))
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

				try
				{
					if (synchronize<Next, Rest ... >(std::forward<Functor>(functor), std::forward<Result>(result)))
					{
						thread_state = false;
						atomic.store(false, std::memory_order_release);

						return true;
					}

					else

					{
						thread_state = false;
						atomic.store(false, std::memory_order_release);

						return false;
					}
				}

				catch (...)
				{
					thread_state = false;
					atomic.store(false, std::memory_order_release);

					throw;
				}
			}
		}
	}

	template <typename ... Entities, typename Functor>
	inline auto synchronize(Functor && functor) noexcept(noexcept(functor()))
		-> typename std::enable_if<std::is_void<decltype(functor())>::value == true, decltype(functor())>::type
	{
		while (!(internal::synchronize<Entities ... >(std::forward<Functor>(functor))))
		{
			std::this_thread::yield();
		}
	}

	template <typename ... Entities, typename Functor>
	inline auto synchronize(Functor && functor) noexcept(noexcept(functor()))
		-> typename std::enable_if<std::is_void<decltype(functor())>::value == false, decltype(functor())>::type
	{
		decltype(functor()) result;

		while (!(internal::synchronize<Entities ... >(std::forward<Functor>(functor), result)))
		{
			std::this_thread::yield();
		}

		return result;
	}
}

#endif