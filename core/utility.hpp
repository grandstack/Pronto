#ifndef pronto_utility_header
#define pronto_utility_header

#include "segment_pool.hpp"
#include "spinlock.hpp"
#include "entity.hpp"

#include <tuple>

namespace pronto
{
	namespace utility
	{
		template <typename ... Pack>
		struct type_carrier
		{
			using carrier_type = type_carrier<Pack ... >;
		};

		namespace detail
		{
			template <typename>
			struct parameters;

			template <typename Return, typename Type, typename ... Arguments>
			struct parameters<Return(Type::*)(Arguments ...)>
			{
				using type = type_carrier<std::decay_t<Arguments> ... >;
			};

			template <typename Return, typename Type, typename ... Arguments>
			struct parameters<Return(Type::*)(Arguments ...) const>
			{
				using type = type_carrier<std::decay_t<Arguments> ... >;
			};
		}

		template <typename Type>
		using parameters_t = typename detail::parameters<decltype(&Type::operator ())>::type;

		// ----------------------------------------->

		template <unsigned ... Indices>
		struct index_carrier
		{
			using type = index_carrier<Indices ... >;
		};

		namespace detail
		{
			template <unsigned Length, unsigned ... Indices>
			struct descending_indices
			{
				using type = typename descending_indices<Length - 1, Indices ..., Length - 1>::type;
			};

			template <unsigned ... Indices>
			struct descending_indices<0, Indices ... >
			{
				using type = index_carrier<Indices ... >;
			};

			template <unsigned Length, unsigned ... Indices>
			struct ascending_indices
			{
				using type = typename ascending_indices<Length - 1, Length - 1, Indices ... >::type;
			};

			template <unsigned ... Indices>
			struct ascending_indices<0, Indices ... >
			{
				using type = index_carrier<Indices ... >;
			};
		}

		template <unsigned Length>
		using descending_indices_t = typename detail::descending_indices<Length>::type;

		template <unsigned Length>
		using ascending_indices_t = typename detail::ascending_indices<Length>::type;

		// ----------------------------------------->

		namespace detail
		{
			template <typename Current, typename Next, typename ... Rest, typename ... Pack>
			void inflate_entity(entity<Pack ... >);

			template <typename Current, typename ... Pack>
			void inflate_entity(entity<Pack ... >);

			template <typename Current, typename Next, typename ... Rest, typename ... Pack>
			void inflate_entity(bag<entity<Pack ... >> const &);

			template <typename Current, typename ... Pack>
			void inflate_entity(bag<entity<Pack ... >> const &);

			// ----------->

			template <typename Current, typename Next, typename ... Rest, typename ... Pack>
			void deflate_entity(entity<Pack ... >);

			template <typename Current, typename ... Pack>
			void deflate_entity(entity<Pack ... >);

			template <typename Current, typename Next, typename ... Rest, typename ... Pack>
			void deflate_entity(bag<entity<Pack ... >> const &);

			template <typename Current, typename ... Pack>
			void deflate_entity(bag<entity<Pack ... >> const &);
		}

		template <typename ... Pack>
		void inflate_entity(entity<Pack ... >);

		template <typename ... Pack>
		void inflate_entity(bag<entity<Pack ... >> const &);

		// ----------->

		template <typename ... Pack>
		void deflate_entity(entity<Pack ... >);

		template <typename ... Pack>
		void deflate_entity(bag<entity<Pack ... >> const &);
	}
}

#include "utility.inline.hpp"

#endif