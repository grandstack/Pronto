#ifndef pronto_inflation_inline_header
#define pronto_inflation_inline_header

namespace pronto
{
	namespace internal
	{
		namespace detail
		{
			template <typename Current, typename Next, typename ... Rest, typename ... Segments>
			inline void inflate_entity(entity<Segments ... > object)
			{
				detail::inflate_entity<Next, Rest ... >(object);
				detail::inflate_entity<Current>(object);
			}

			template <typename Current, typename ... Segments>
			inline void inflate_entity(entity<Segments ... > object)
			{
				thread_local auto & pool = segment_context<entity<Segments ... >, Current>::get_pool();
				pool.create(object);
			}

			template <typename Current, typename Next, typename ... Rest, typename ... Segments>
			inline void inflate_entity(bag<entity<Segments ... >> const & container)
			{
				detail::inflate_entity<Next, Rest ... >(container);
				detail::inflate_entity<Current>(container);
			}

			template <typename Current, typename ... Segments>
			inline void inflate_entity(bag<entity<Segments ... >> const & container)
			{
				thread_local auto & pool = segment_context<entity<Segments ... >, Current>::get_pool();
				pool.create(container);
			}
		}

		template <typename ... Segments>
		inline void inflate_entity(entity<Segments ... > object)
		{
			thread_local auto & pool = segment_context<entity<Segments ... >, entity<Segments ... >>::get_pool();

			detail::inflate_entity<Segments ... >(object);

			pool.create(object, object);
		}

		template <typename ... Segments>
		inline void inflate_entity(bag<entity<Segments ... >> const & container)
		{
			thread_local auto & pool = segment_context<entity<Segments ... >, entity<Segments ... >>::get_pool();

			detail::inflate_entity<Segments ... >(container);

			for (auto object : container)
			{
				pool.create(object, object);
			}
		}
	}
}

#endif