#ifndef pronto_process_header
#define pronto_process_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "utility.hpp"

#include <functional>
#include <atomic>

namespace pronto
{
	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		type::bool_t process(entity<Segments ... > const object, utility::type_carrier<Arguments ... >, Functor && functor);

		template <typename Functor, typename ... Segments, typename ... Arguments>
		type::bool_t process(bag<entity<Segments ... >> const & container, utility::type_carrier<Arguments ... >, Functor && functor);
	}

	template <typename Functor, typename ... Segments>
	type::bool_t process(entity<Segments ... > object, Functor && functor);

	template <typename Functor, typename ... Segments>
	type::bool_t process(bag<entity<Segments ... >> const & container, Functor && functor);
}

#include "process.inline.hpp"

#endif