#ifndef pronto_spinlock_header
#define pronto_spinlock_header

#include "utility.hpp"
#include "entity.hpp"

#include <atomic>
#include <tuple>

namespace pronto
{
	template <typename>
	struct spinlock;

	template <typename ... Segments>
	struct spinlock<entity<Segments ... >>
	{
		spinlock();
		~spinlock();

		spinlock(spinlock &) = delete;
		spinlock(spinlock &&);

		spinlock & operator = (spinlock &) = delete;
		spinlock & operator = (spinlock &&);

	private:

		static type::basic::bool_t & get_thread_lock_state();
		static type::atomic::bool_t & get_atomic();

		type::basic::bool_t valid = true;
	};

	// ----------------------------------------->

	template <typename Entity>
	spinlock<Entity> make_spinlock();
}

#include "spinlock.inline.hpp"

#endif