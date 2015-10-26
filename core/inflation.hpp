#ifndef pronto_inflation_header
#define pronto_inflation_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "bag.hpp"

namespace pronto
{
	namespace internal
	{
		namespace detail
		{
			template <typename Current, typename Next, typename ... Rest, typename ... Pack>
			void inflate_entity(entity<Pack ... > const object);

			template <typename Current, typename ... Pack>
			void inflate_entity(entity<Pack ... > const object);

			template <typename Current, typename Next, typename ... Rest, typename ... Pack>
			void inflate_entity(bag<entity<Pack ... >> const & container);

			template <typename Current, typename ... Pack>
			void inflate_entity(bag<entity<Pack ... >> const & container);
		}

		template <typename ... Pack>
		void inflate_entity(entity<Pack ... > const object);

		template <typename ... Pack>
		void inflate_entity(bag<entity<Pack ... >> const & container);
	}
}

#include "inflation.inline.hpp"

#endif