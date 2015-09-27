#ifndef pronto_segment_pool_header
#define pronto_segment_pool_header

#include "entity.hpp"
#include "bag.hpp"

#include <utility>
#include <memory>
#include <vector>

namespace pronto
{
	template <typename, typename>
	struct segment_pool;

	template <typename Segment, typename ... Segments>
	struct segment_pool <entity<Segments ... >, Segment>
	{
		using aligned_type = std::aligned_storage_t<sizeof(Segment), alignof(Segment)>;
		using deleter_type = std::unique_ptr<Segment>;

		using value_type = Segment;

		void create(entity<Segments ... >);
		void create(bag<entity<Segments ... >> const &);

		void destroy(entity<Segments ... >);
		void destroy(bag<entity<Segments ... >> const &);

		Segment & operator [] (entity<Segments ... >);

		type::index_t size() const;
		
	private:

		std::vector<deleter_type> deleters
		{
			// ...
		};

		std::vector<aligned_type> segments
		{
			// ...
		};
	};
}

#include "segment_pool.inline.hpp"

#endif