#ifndef pronto_process_inline_header
#define pronto_process_inline_header

namespace pronto
{
	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline type::bool_t process(entity<Segments ... > object, utility::type_carrier<Arguments ... >, Functor functor)
		{
			thread_local auto pools = std::tie(internal::segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			functor(std::get<internal::segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[object] ... );

			return true;
		}

		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline type::bool_t process(bag<entity<Segments ... >> const & container, utility::type_carrier<Arguments ... >, Functor functor)
		{
			thread_local auto pools = std::tie(internal::segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			for (auto object : container)
			{
				functor(std::get<internal::segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[object] ... );
			}

			return true;
		}
	}

	template <typename Functor, typename ... Segments>
	inline type::bool_t process(entity<Segments ... > object, Functor && functor)
	{
		static_assert(utility::carrier_contains<utility::type_carrier<entity<Segments ... >, Segments ... >, utility::parameters_t<Functor>>::value, "This entity does not contain one or more of these segments!");

		auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		return detail::process(object, parameters, std::forward<Functor>(functor));
	}

	template <typename Functor, typename ... Segments>
	inline type::bool_t process(bag<entity<Segments ... >> const & container, Functor && functor)
	{
		static_assert(utility::carrier_contains<utility::type_carrier<entity<Segments ... >, Segments ... >, utility::parameters_t<Functor>>::value, "This entity does not contain one or more of these segments!");

		auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		return detail::process(container, parameters, std::forward<Functor>(functor));
	}
}

#endif