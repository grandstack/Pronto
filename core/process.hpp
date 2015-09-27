#ifndef pronto_process_header
#define pronto_process_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "utility.hpp"

#include <functional>
#include <thread>
#include <atomic>

namespace pronto
{
	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		decltype(auto) process(entity<Segments ... >, utility::type_carrier<Arguments ... >, Functor);

		template <typename Functor, typename ... Segments, typename ... Arguments>
		void process(bag<entity<Segments ... >> const &, utility::type_carrier<Arguments ... >, Functor);
	}

	template <typename Functor, typename ... Segments>
	decltype(auto) process(entity<Segments ... >, Functor &&);

	template <typename Functor, typename ... Segments>
	void process(bag<entity<Segments ... >> const &, Functor &&);
}

#include "process.inline.hpp"

#endif