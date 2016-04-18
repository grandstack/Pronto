#ifndef pronto_utility_header
#define pronto_utility_header

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

		template <unsigned ... Indices>
		struct index_carrier
		{
			using type = index_carrier<Indices ... >;
		};

		namespace detail
		{
			template <typename, typename>
			struct type_carrier_contains;

			template <typename Type, typename Current>
			struct type_carrier_contains<type_carrier<Current>, Type>
			{
				enum : bool { value = std::is_same<Current, Type>::value };
			};

			template <typename Type, typename Current, typename Next, typename ... Rest>
			struct type_carrier_contains<type_carrier<Current, Next, Rest ... >, Type>
			{
				enum : bool { value = type_carrier_contains<type_carrier<Current>, Type>::value || type_carrier_contains<type_carrier<Next, Rest ... >, Type>::value };
			};

			template <typename, unsigned>
			struct index_carrier_contains;

			template <unsigned Index, unsigned Current>
			struct index_carrier_contains<index_carrier<Current>, Index>
			{
				enum : bool { value = Current == Index };
			};

			template <unsigned Index, unsigned Current, unsigned Next, unsigned ... Rest>
			struct index_carrier_contains<index_carrier<Current, Next, Rest ... >, Index>
			{
				enum : bool { value = index_carrier_contains<index_carrier<Current>, Index>::value || index_carrier_contains<index_carrier<Next, Rest ... >, Index>::value };
			};
		}

		template <typename, typename>
		struct carrier_contains;

		template <typename ... Types, typename Current>
		struct carrier_contains<type_carrier<Types ... >, type_carrier<Current>>
		{
			enum : bool { value = detail::type_carrier_contains<type_carrier<Types ... >, Current>::value };
		};

		template <typename ... Types, typename Current, typename Next, typename ... Rest>
		struct carrier_contains<type_carrier<Types ... >, type_carrier<Current, Next, Rest ... >>
		{
			enum : bool { value = detail::type_carrier_contains<type_carrier<Types ... >, Current>::value && carrier_contains<type_carrier<Types ... >, type_carrier<Next, Rest ... >>::value };
		};

		template <unsigned ... Indices, unsigned Current>
		struct carrier_contains<index_carrier<Indices ... >, index_carrier<Current>>
		{
			enum : bool { value = detail::index_carrier_contains<index_carrier<Indices ... >, Current>::value };
		};

		template <unsigned ... Indices, unsigned Current, unsigned Next, unsigned ... Rest>
		struct carrier_contains<index_carrier<Indices ... >, index_carrier<Current, Next, Rest ... >>
		{
			enum : bool { value = detail::index_carrier_contains<index_carrier<Indices ... >, Current>::value && carrier_contains<index_carrier<Indices ... >, index_carrier<Next, Rest ... >>::value };
		};

		// ----------------------------------------->

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
	}
}

#include "utility.inline.hpp"

#endif