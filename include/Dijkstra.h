#pragma once

#include <queue>
#include <vector>
#include <numeric>

#include "IGraph.h"

namespace RSP {

template <class T, class W>
typename IGraph<T, W>::weight_t 
dijkstra_path_length(
	IGraph<T, W> const* graph,
	typename IGraph<T, W>::size_t const& start,
	typename IGraph<T, W>::size_t const& dest
) {
	using adj_t = typename IGraph<T, W>::adj_t;
	using weight_t = typename IGraph<T, W>::weight_t;
	using pq_t = std::priority_queue<adj_t, std::vector<adj_t>, std::greater<adj_t>>;

	static constexpr auto kInf_Weight = std::numeric_limits<weight_t>::max();

	auto to_visit = pq_t();
	auto distances = std::vector<weight_t>(graph->vertices_size(), kInf_Weight);

	distances[start] = weight_t {};

	to_visit.push(adj_t {distances[start], start});

	while (!to_visit.empty()) {

		auto const [cdist, cv] = to_visit.top();

		if (cv == dest) {
			return cdist;
		}

		to_visit.pop();

		for (auto const& [aw, av]: graph->get_adjacents(cv)) {
			auto const candid_distance = cdist + aw;

			if (candid_distance >= distances[av]) {
				continue;
			}

			distances[av] = candid_distance;
			to_visit.push(adj_t {distances[av], av});
		}
	}

	return distances[dest];
}

}