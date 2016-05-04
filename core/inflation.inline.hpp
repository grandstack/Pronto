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
				auto & pool = segment_context<entity<Segments ... >, Current>::get_pool();

				pool.create(range);
			}

			template <typename Current, typename Next, typename ... Rest, typename ... Segments>
			inline void inflate_entity(range<entity<Segments ... >> const & range)
			{
				inflate_entity<Next, Rest ... >(range);
				inflate_entity<Current>(range);
			}
		}

		template <typename ... Segments>
		inline void inflate_entity(range<entity<Segments ... >> const & range)
		{
			if (range)
			{
				detail::inflate_entity<Segments ... >(range);
			}
		}

		namespace detail
		{
			template <typename Current, typename ... Segments>
			inline void deflate_entity(range<entity<Segments ... >> const & range)
			{
				auto & pool = segment_context<entity<Segments ... >, Current>::get_pool();

				pool.destroy(range);
			}

			template <typename Current, typename Next, typename ... Rest, typename ... Segments>
			inline void deflate_entity(range<entity<Segments ... >> const & range)
			{
				deflate_entity<Next, Rest ... >(range);
				deflate_entity<Current>(range);
			}
		}

		template <typename ... Segments>
		inline void deflate_entity(range<entity<Segments ... >> const & range)
		{
			if (range)
			{
				detail::deflate_entity<Segments ... >(range);
			}
		}
	}
}

#endif