#include <queue>
#include <vector>

#include "IGraph.h"

namespace RSP {

template <class T, class W>
typename IGraph<T, W>::weight_t BFS_path_length(IGraph<T, W> const* graph, typename IGraph<T, W>::size_t const& start, typename IGraph<T, W>::size_t const& dest, typename IGraph<T, W>::weight_t zero_dist, typename IGraph<T, W>::weight_t inf_dist) {
	auto to_visit = std::queue<typename IGraph<T, W>::size_t>();
	auto visited = std::vector<bool>(graph->vertices_size(), false);
	auto distances = std::vector<typename IGraph<T, W>::weight_t>(graph->vertices_size(), inf_dist);

	to_visit.push(start);
	visited[start] = true;
	distances[start] = zero_dist;

	while (!to_visit.empty()) {
		auto const cv = to_visit.front();

		if (cv == dest) {
			return distances[dest];
		}

		to_visit.pop();

		for (auto const& av: graph->get_adjacents(cv)) {
			auto const& [_, av_head] = av;

			if (visited[av_head]) {
				continue;
			}

			visited[av_head] = true;
			to_visit.push(av_head);
			distances[av_head] = distances[cv] + 1;
		}
	}

	return distances[dest];
}

}