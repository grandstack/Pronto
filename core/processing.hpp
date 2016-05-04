#ifndef pronto_process_header
#define pronto_process_header

#include "segment_context.hpp"
#include "entity_context.hpp"
#include "utility.hpp"

namespace pronto
{
	namespace utility
	{
		namespace detail
		{
			template <typename Current, typename ... Source_segments, typename ... Target_segments>
			void move(entity<Source_segments ... > const source, entity<Target_segments ... > const target);

			template <typename Current, typename Next, typename ... Rest, typename ... Source_segments, typename ... Target_segments>
			void move(entity<Source_segments ... > const source, entity<Target_segments ... > const target);

			template <typename ... Source_segments, typename ... Target_segments, typename ... Common_segments>
			void move(entity<Source_segments ... > const source, entity<Target_segments ... > const target, utility::type_carrier<Common_segments ... >);
		}

		template <typename ... Source_segments, typename ... Target_segments>
		void move(entity<Source_segments ... > const source, entity<Target_segments ... > const target);

		// ----------------------------------------->

		namespace detail
		{
			template <typename Current, typename ... Source_segments, typename ... Target_segments>
			void copy(entity<Source_segments ... > const source, entity<Target_segments ... > const target);

			template <typename Current, typename Next, typename ... Rest, typename ... Source_segments, typename ... Target_segments>
			void copy(entity<Source_segments ... > const source, entity<Target_segments ... > const target);

			template <typename ... Source_segments, typename ... Target_segments, typename ... Common_segments>
			void copy(entity<Source_segments ... > const source, entity<Target_segments ... > const target, utility::type_carrier<Common_segments ... >);
		}

		template <typename ... Source_segments, typename ... Target_segments>
		void copy(entity<Source_segments ... > const source, entity<Target_segments ... > const target);
	}

	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		void process(range<entity<Segments ... >> const & range, utility::type_carrier<Arguments ... >, Functor && functor);

		template <typename Functor, typename ... Segments, typename ... Arguments>
		void process(entity<Segments ... > const & range, utility::type_carrier<Arguments ... >, Functor && functor);
	}

	template <typename Functor, typename ... Segments>
	void process(range<entity<Segments ... >> const & range, Functor && functor);

	template <typename Functor, typename ... Segments>
	void process(entity<Segments ... > const & range, Functor && functor);

	namespace detail
	{
		template <typename Functor, typename ... Segments, typename ... Arguments>
		range<entity<Segments ... >> take_if(range<entity<Segments ... >> & range, utility::type_carrier<Arguments ... >, Functor && predicate);
	}

	template <typename Functor, typename ... Segments>
	range<entity<Segments ... >> take_if(range<entity<Segments ... >> & range, Functor && predicate);
}

#include "processing.inline.hpp"

#endif