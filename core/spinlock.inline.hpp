#ifndef pronto_spinlock_inline_header
#define pronto_spinlock_inline_header

namespace pronto
{
	namespace internal
	{
		template <typename ... Segments>
		inline spinlock<entity<Segments ... >>::spinlock()
		{
			auto & locked = get_thread_lock_state();
			auto & atomic = get_atomic();

			if (locked != true)
			{
				while (atomic.exchange(true)) continue;

				locked = true;
				valid = true;
			}
		}

		template <typename ... Segments>
		inline spinlock<entity<Segments ... >>::~spinlock()
		{
			if (valid != false)
			{
				auto & locked = get_thread_lock_state();
				auto & atomic = get_atomic();

				atomic.store(false);
				locked = false;
			}
		}

		template <typename ... Segments>
		inline spinlock<entity<Segments ... >>::spinlock(spinlock<entity<Segments ... >> && other)
		{
			other.valid = false;
		}

		template <typename ... Segments>
		inline spinlock<entity<Segments ... >> & spinlock<entity<Segments ... >>::operator = (spinlock<entity<Segments ... >> && other)
		{
			other.valid = false;
		}

		template <typename ... Segments>
		inline type::bool_t & spinlock<entity<Segments ... >>::get_thread_lock_state()
		{
			thread_local bool locked
			{
				false
			};

			return locked;
		}

		template <typename ... Segments>
		inline type::atomic::bool_t & spinlock<entity<Segments ... >>::get_atomic()
		{
			static type::atomic::bool_t atomic
			{
				false
			};

			return atomic;
		}

		template <typename Entity>
		spinlock<Entity> make_spinlock()
		{
			return spinlock<Entity>
			{
				// ...
			};
		}
	}
}

#endif