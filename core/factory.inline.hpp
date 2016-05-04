#ifndef pronto_factory_inline_header
#define pronto_factory_inline_header

namespace pronto
{
	template <typename Type>
	inline range<Type> create(type::index_t const count)
	{
		auto & pool = internal::entity_context<Type>::get_pool();

		auto entities = pool.create(count);
		internal::inflate_entity(entities);

		return entities;
	}

	template <typename Type>
	inline void destroy(range<Type> & range)
	{
		auto & pool = internal::entity_context<Type>::get_pool();

		if (range)
		{
			internal::deflate_entity(range);
			pool.destroy(range);
		}
	}
}

#endif