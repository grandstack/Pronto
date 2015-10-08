#ifndef pronto_entity_context_inline_header
#define pronto_entity_context_inline_header

namespace pronto
{
	namespace internal
	{
		template <typename ... Segments>
		inline entity_pool<entity<Segments ... >> & entity_context<entity<Segments ... >>::get_pool()
		{
			static entity_pool<entity<Segments ... >> pool
			{
				// ...
			};

			return pool;
		}
	}
}

#endif