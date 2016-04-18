#ifndef pronto_process_header
#define pronto_process_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "utility.hpp"

namespace pronto
{
	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		void process(range<entity<Segments ... >> const & range, utility::type_carrier<Arguments ... >, Functor && functor);

		template <typename Functor, typename ... Segments, typename ... Arguments>
		void process(std::vector<entity<Segments ... >> const & vector, utility::type_carrier<Arguments ... >, Functor && functor);
	}

	template <typename Functor, typename ... Segments>
	void process(range<entity<Segments ... >> const & range, Functor && functor);

	template <typename Functor, typename ... Segments>
	void process(std::vector<entity<Segments ... >> const & vector, Functor && functor);
}

#include "process.inline.hpp"

#endif