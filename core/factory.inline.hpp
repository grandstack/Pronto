#ifndef pronto_factory_inline_header
#define pronto_factory_inline_header

namespace pronto
{
	template <typename Entity>
	inline Entity create()
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();

		return pool.create();
	}

	template <typename Entity>
	inline bag<Entity> create(type::index_t const count)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();

		return pool.create(count);
	}

	template <typename Entity>
	inline void destroy(Entity const object)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();

		pool.destroy(object);
	}

	template <typename Entity>
	inline void destroy(bag<Entity> const & container)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();

		pool.destroy(container);
	}

	template <typename Entity>
	inline bool validate(Entity const object)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();

		return pool.valid(object);
	}

	template <typename Entity>
	inline bool validate(bag<Entity> const & container)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();

		for (auto object : container)
		{
			if (pool.valid(object))
			{
				continue;
			}

			else

			{
				return false;
			}
		}

		return true;
	}
}

#endif