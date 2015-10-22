#ifndef pronto_entity_lock_inline_header
#define pronto_entity_lock_inline_header

namespace pronto
{
	namespace internal
	{
		template <typename ... Segments>
		inline type::atomic::bool_t & entity_lock<entity<Segments ... >>::get_state()
		{
			static type::atomic::bool_t state
			{
				false
			};

			return state;
		}
	}
}

#endif