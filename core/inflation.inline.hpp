#ifndef pronto_inflation_inline_header
#define pronto_inflation_inline_header

namespace pronto
{
	namespace internal
	{
		namespace detail
		{
			template <typename Current, typename ... Segments>
			inline void inflate_entity(range<entity<Segments ... >> const & range)
			{
				thread_local auto & pool = segment_context<entity<Segments ... >, Current>::get_pool();
				pool.create(range);
			}

			template <typename Current, typename Next, typename ... Rest, typename ... Segments>
			inline void inflate_entity(range<entity<Segments ... >> const & range)
			{
				detail::inflate_entity<Next, Rest ... >(range);
				detail::inflate_entity<Current>(range);
			}
		}

		template <typename ... Segments>
		inline void inflate_entity(range<entity<Segments ... >> const & range)
		{
			detail::inflate_entity<Segments ... >(range);
		}
	}
}

#endif