#ifndef pronto_process_inline_header
#define pronto_process_inline_header

namespace pronto
{
	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline decltype(auto) process(entity<Segments ... > object, utility::type_carrier<Arguments ... >, Functor functor)
		{
			thread_local auto pools = std::tie(segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			{
				return functor(std::get<segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[object] ... );
			}
		}

		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline void process(bag<entity<Segments ... >> const & container, utility::type_carrier<Arguments ... >, Functor functor)
		{
			thread_local auto pools = std::tie(segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			for (auto object : container)
			{
				functor(std::get<segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[object] ... );
			}
		}
	}

	template <typename Functor, typename ... Segments>
	inline decltype(auto) process(entity<Segments ... > object, Functor && functor)
	{
		auto lock = make_spinlock<entity<Segments ... >>();

		auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		return detail::process(object, parameters, std::forward<Functor>(functor));
	}

	template <typename Functor, typename ... Segments>
	inline void process(bag<entity<Segments ... >> const & container, Functor && functor)
	{
		auto lock = make_spinlock<entity<Segments ... >>();

		auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		detail::process(container, parameters, std::forward<Functor>(functor));
	}
}

#endif