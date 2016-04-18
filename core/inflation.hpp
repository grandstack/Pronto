#ifndef pronto_inflation_header
#define pronto_inflation_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "range.hpp"

namespace pronto
{
	namespace internal
	{
		namespace detail
		{
			template <typename Current, typename ... Segments>
			void inflate_entity(range<entity<Segments ... >> const & range);

			template <typename Current, typename Next, typename ... Rest, typename ... Segments>
			void inflate_entity(range<entity<Segments ... >> const & range);
		}

		template <typename ... Segments>
		void inflate_entity(range<entity<Segments ... >> const & range);
	}
}

#include "inflation.inline.hpp"

#endif