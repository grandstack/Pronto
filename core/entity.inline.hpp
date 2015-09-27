#ifndef pronto_entity_inline_header
#define pronto_entity_inline_header

namespace pronto
{
	template <typename ... Segments>
	inline entity<Segments ... >::entity(type::index_t index)
	{
		entity<Segments ... >::index = index;
	}

	template <typename ... Segments>
	inline entity<Segments ... >::operator type::index_t () const
	{
		return index;
	}
}

#endif
