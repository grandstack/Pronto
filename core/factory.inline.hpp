#ifndef pronto_factory_inline_header
#define pronto_factory_inline_header

namespace pronto
{
	template <typename Entity>
	inline Entity create()
	{
		thread_local auto & pool = entity_context<Entity>::get_pool();
		auto lock = make_spinlock<Entity>();

		return pool.create();
	}

	template <typename Entity>
	inline bag<Entity> create(type::index_t size)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();
		auto lock = internal::make_spinlock<Entity>();

		return pool.create(size);
	}

	template <typename Entity>
	inline void destroy(bag<Entity> const & container)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();
		auto lock = internal::make_spinlock<Entity>();

		pool.destroy(container);
	}

	template <typename Entity>
	inline bool validate(Entity object)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();
		auto lock = internal::make_spinlock<Entity>();

		return pool.valid(object);
	}

	template <typename Entity>
	inline bool validate(bag<Entity> const & container)
	{
		thread_local auto & pool = internal::entity_context<Entity>::get_pool();
		auto lock = internal::make_spinlock<Entity>();

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