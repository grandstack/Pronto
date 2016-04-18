#ifndef pronto_process_inline_header
#define pronto_process_inline_header

namespace pronto
{
	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline void process(range<entity<Segments ... >> const & range, utility::type_carrier<Arguments ... >, Functor && functor)
		{
			thread_local auto pools = std::tie(internal::segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			for (auto index : range)
			{
				functor(std::get<internal::segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[index] ... );
			}
		}

		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline void process(std::vector<entity<Segments ... >> const & vector, utility::type_carrier<Arguments ... >, Functor && functor)
		{
			thread_local auto pools = std::tie(internal::segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			for (auto index : vector)
			{
				functor(std::get<internal::segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[index] ... );
			}

			return true;
		}
	}

	template <typename Functor, typename ... Segments>
	inline void process(range<entity<Segments ... >> const & range, Functor && functor)
	{
		static_assert(utility::carrier_contains<utility::type_carrier<entity<Segments ... >, Segments ... >, utility::parameters_t<Functor>>::value, "This entity does not contain one or more of these segments!");

		auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		return detail::process(range, parameters, std::forward<Functor>(functor));
	}

	template <typename Functor, typename ... Segments>
	inline void process(std::vector<entity<Segments ... >> const & vector, Functor && functor)
	{
		static_assert(utility::carrier_contains<utility::type_carrier<entity<Segments ... >, Segments ... >, utility::parameters_t<Functor>>::value, "This entity does not contain one or more of these segments!");

		auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		return detail::process(vector, parameters, std::forward<Functor>(functor));
	}
}

#endif