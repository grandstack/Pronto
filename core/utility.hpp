#ifndef pronto_utility_header
#define pronto_utility_header

#include "alias.hpp"

#include <tuple>

namespace pronto
{
	namespace utility
	{
		template <typename ... Types>
		struct type_carrier
		{
			using carrier_type = type_carrier<Types ... >;

			static constexpr type::index_t size()
			{
				return static_cast<type::index_t>(sizeof ... (Types));
			}
		};

		template <unsigned ... Indices>
		struct index_carrier
		{
			using carrier_type = index_carrier<Indices ... >;

			static constexpr type::index_t size()
			{
				return static_cast<type::index_t>(sizeof ... (Indices));
			}
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
			template <bool, typename, typename>
			struct carrier_conditional;

			template <typename ... Types_one, typename ... Types_two>
			struct carrier_conditional<true, type_carrier<Types_one ... >, type_carrier<Types_two ... >>
			{
				using type = type_carrier<Types_one ... >;
			};

			template <typename ... Types_one, typename ... Types_two>
			struct carrier_conditional<false, type_carrier<Types_one ... >, type_carrier<Types_two ... >>
			{
				using type = type_carrier<Types_two ... >;
			};

			template <unsigned ... Indices_one, unsigned ... Indices_two>
			struct carrier_conditional<true, index_carrier<Indices_one ... >, index_carrier<Indices_two ... >>
			{
				using type = index_carrier<Indices_one ... >;
			};

			template <unsigned ... Indices_one, unsigned ... Indices_two>
			struct carrier_conditional<false, index_carrier<Indices_one ... >, index_carrier<Indices_two ... >>
			{
				using type = index_carrier<Indices_two ... >;
			};
		}

		template <bool Conditional, typename Type_one, typename Type_two>
		using carrier_conditional_t = typename detail::carrier_conditional<Conditional, Type_one, Type_two>::type;

		// ----------------------------------------->

		namespace detail
		{
			template <typename, typename, typename = void>
			struct carrier_common;

			template <typename ... Types_one, typename ... Types_two>
			struct carrier_common<type_carrier<Types_one ... >, type_carrier<Types_two ... >>
			{
				using type = typename detail::carrier_common<type_carrier<Types_one ... >, type_carrier<Types_two ... >, type_carrier<>>::type;
			};

			template <typename ... Types_one, typename ... Types_two, typename Current>
			struct carrier_common<type_carrier<Types_one ... >, type_carrier<Current>, type_carrier<Types_two ... >>
			{
				using type = carrier_conditional_t<carrier_contains<type_carrier<Types_one ... >, type_carrier<Current>>::value, type_carrier<Current, Types_two ... >, type_carrier<Types_two ... >>; 
			};

			template <typename ... Types_one, typename ... Types_two, typename Current, typename Next, typename ... Rest>
			struct carrier_common<type_carrier<Types_one ... >, type_carrier<Current, Next, Rest ... >, type_carrier<Types_two ... >>
			{
				using type = typename carrier_common<type_carrier<Types_one ... >, type_carrier<Next, Rest ... >, carrier_conditional_t<carrier_contains<type_carrier<Types_one ... >, type_carrier<Current>>::value, type_carrier<Current, Types_two ... >, type_carrier<Types_two ... >>>::type;
			};

			template <unsigned ... Indices_one, unsigned ... Indices_two>
			struct carrier_common<index_carrier<Indices_one ... >, index_carrier<Indices_two ... >>
			{
				using type = typename detail::carrier_common<index_carrier<Indices_one ... >, index_carrier<Indices_two ... >, index_carrier<>>::type;
			};

			template <unsigned ... Indices_one, unsigned ... Indices_two, unsigned Current>
			struct carrier_common<index_carrier<Indices_one ... >, index_carrier<Current>, index_carrier<Indices_two ... >>
			{
				using type = carrier_conditional_t<carrier_contains<index_carrier<Indices_one ... >, index_carrier<Current>>::value, index_carrier<Current, Indices_two ... >, index_carrier<Indices_two ... >>; 
			};

			template <unsigned ... Indices_one, unsigned ... Indices_two, unsigned Current, unsigned Next, unsigned ... Rest>
			struct carrier_common<index_carrier<Indices_one ... >, index_carrier<Current, Next, Rest ... >, index_carrier<Indices_two ... >>
			{
				using type = typename carrier_common<index_carrier<Indices_one ... >, index_carrier<Next, Rest ... >, carrier_conditional_t<carrier_contains<index_carrier<Indices_one ... >, index_carrier<Current>>::value, index_carrier<Current, Indices_two ... >, index_carrier<Indices_two ... >>>::type;
			};
		}

		template <typename Carrier_one, typename Carrier_two>
		using carrier_common_t = typename detail::carrier_common<Carrier_one, Carrier_two>::type;

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