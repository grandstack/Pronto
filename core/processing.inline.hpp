#ifndef pronto_process_inline_header
#define pronto_process_inline_header

namespace pronto
{
	namespace utility
	{
		namespace detail
		{
			template <typename Current, typename ... Source_segments, typename ... Target_segments>
			inline void move(entity<Source_segments ... > const source, entity<Target_segments ... > const target)
			{
				auto & source_pool = internal::segment_context<entity<Source_segments ... >, Current>::get_pool();
				auto & target_pool = internal::segment_context<entity<Target_segments ... >, Current>::get_pool();

				target_pool[target] = std::move(source_pool[source]);
			}

			template <typename Current, typename Next, typename ... Rest, typename ... Source_segments, typename ... Target_segments>
			inline void move(entity<Source_segments ... > const source, entity<Target_segments ... > const target)
			{
				move<Next, Rest ... >(source, target);
				move<Current>(source, target);
			}

			template <typename ... Source_segments, typename ... Target_segments, typename ... Common_segments>
			inline void move(entity<Source_segments ... > const source, entity<Target_segments ... > const target, utility::type_carrier<Common_segments ... >)
			{
				if (utility::type_carrier<Common_segments ... >::size() > 0)
				{
					detail::move<Common_segments ... >(source, target);
				}
			}
		}

		template <typename ... Source_segments, typename ... Target_segments>
		inline void move(entity<Source_segments ... > const source, entity<Target_segments ... > const target)
		{
			using common_types = utility::carrier_common_t<utility::type_carrier<Source_segments ... >, utility::type_carrier<Target_segments ... >>;

			constexpr auto common = common_types
			{
				// ...
			};

			detail::move(source, target, common);
		}

		// ----------------------------------------->

		namespace detail
		{
			template <typename Current, typename ... Source_segments, typename ... Target_segments>
			inline void copy(entity<Source_segments ... > const source, entity<Target_segments ... > const target)
			{
				auto & source_pool = internal::segment_context<entity<Source_segments ... >, Current>::get_pool();
				auto & target_pool = internal::segment_context<entity<Target_segments ... >, Current>::get_pool();

				target_pool[target] = source_pool[source];
			}

			template <typename Current, typename Next, typename ... Rest, typename ... Source_segments, typename ... Target_segments>
			inline void copy(entity<Source_segments ... > const source, entity<Target_segments ... > const target)
			{
				copy<Next, Rest ... >(source, target);
				copy<Current>(source, target);
			}

			template <typename ... Source_segments, typename ... Target_segments, typename ... Common_segments>
			inline void copy(entity<Source_segments ... > const source, entity<Target_segments ... > const target, utility::type_carrier<Common_segments ... >)
			{
				if (utility::type_carrier<Common_segments ... >::size() > 0)
				{
					detail::copy<Common_segments ... >(source, target);
				}
			}
		}

		template <typename ... Source_segments, typename ... Target_segments>
		inline void copy(entity<Source_segments ... > const source, entity<Target_segments ... > const target)
		{
			using common_types = utility::carrier_common_t<utility::type_carrier<Source_segments ... >, utility::type_carrier<Target_segments ... >>;

			constexpr auto common = common_types
			{
				// ...
			};

			detail::copy(source, target, common);
		}
	}

	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline void process(range<entity<Segments ... >> const & range, utility::type_carrier<Arguments ... >, Functor && functor)
		{
			auto pools = std::tie(internal::segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			for (auto index : range)
			{
				functor(std::get<internal::segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[index] ... );
			}
		}

		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline void process(entity<Segments ... > const & object, utility::type_carrier<Arguments ... >, Functor && functor)
		{
			auto pools = std::tie(internal::segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			functor(std::get<internal::segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[object] ... );
		}
	}

	template <typename Functor, typename ... Segments>
	inline void process(range<entity<Segments ... >> const & range, Functor && functor)
	{
		static_assert(utility::carrier_contains<utility::type_carrier<entity<Segments ... >, Segments ... >, utility::parameters_t<Functor>>::value, "This entity does not contain one or more of these segments!");

		constexpr auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		detail::process(range, parameters, std::forward<Functor>(functor));
	}

	template <typename Functor, typename ... Segments>
	inline void process(entity<Segments ... > const & object, Functor && functor)
	{
		static_assert(utility::carrier_contains<utility::type_carrier<entity<Segments ... >, Segments ... >, utility::parameters_t<Functor>>::value, "This entity does not contain one or more of these segments!");

		constexpr auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		detail::process(object, parameters, std::forward<Functor>(functor));
	}

	// ----------------------------------------->

	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		inline range<entity<Segments ... >> take_if(range<entity<Segments ... >> & range, utility::type_carrier<Arguments ... >, Functor && predicate)
		{
			auto pools = std::tie(internal::segment_context<entity<Segments ... >, Arguments>::get_pool() ... );

			thread_local std::vector<entity<Segments ... >> taken
			{
				// ...
			};

			if (range)
			{
				for (auto object : range)
				{
					if (predicate(std::get<internal::segment_pool<entity<Segments ... >, Arguments>(&)>(pools)[object] ... ))
					{
						taken.push_back(object);
					}
				}

				auto result = pronto::create<entity<Segments ... >>(static_cast<type::index_t>(taken.size()));

				auto index = 0;
				for (auto object : taken)
				{
					utility::move(object, result[index++]);
				} taken.clear();

				return result;
			}

			return { 0, 0 };
		}
	}

	template <typename Functor, typename ... Segments>
	inline range<entity<Segments ... >> take_if(range<entity<Segments ... >> & range, Functor && predicate)
	{
		static_assert(utility::carrier_contains<utility::type_carrier<entity<Segments ... >, Segments ... >, utility::parameters_t<Functor>>::value, "This entity does not contain one or more of these segments!");

		constexpr auto parameters = utility::parameters_t<Functor>
		{
			// ...
		};

		return detail::take_if(range, parameters, std::forward<Functor>(predicate));
	}
}

#endif