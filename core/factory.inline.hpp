#ifndef pronto_factory_inline_header
#define pronto_factory_inline_header

namespace pronto
{
	template <typename Entity>
	inline range<Entity> create(type::index_t const count)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();

		auto entities = pool.create(count);
		internal::inflate_entity(entities);

		return entities;
	}

	template <typename Entity>
	inline void destroy(range<Entity> & range)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();

		if (range)
		{
			internal::deflate_entity(range);
			pool.destroy(range);
		}
	}
}

#endif