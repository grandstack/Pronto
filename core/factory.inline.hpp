#ifndef pronto_factory_inline_header
#define pronto_factory_inline_header

namespace pronto
{
	template <typename Type>
	inline range<Type> create(type::index_t const count)
	{
		thread_local auto & pool = internal::entity_context<Type>::get_pool();

		auto new_range = pool.create(count);
		internal::inflate_entity(new_range);

		return new_range;
	}

	template <typename Type>
	inline void destroy(range<Type> & range)
	{
		thread_local auto & pool = internal::entity_context<Type>::get_pool();

		pool.destroy(range);
	}
}

#endif