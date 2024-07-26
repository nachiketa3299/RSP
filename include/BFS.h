#pragma once

#include <queue>
#include <vector>
#include <algorithm>

#include "IGraph.h"


// 갑 > 을 > 병
// ABCDE 서
// FGH 동
// B - D  !C
// E - F !FGH
// H - 갑

// 8 개 갑은 최대 5개 소지 2/ 1
// 갑 = H !EF (ABCDG)  H BD !CEF (AG)
// 을 = 
// 병 = 

namespace RSP {

template <class T, class W>
std::vector<typename IGraph<T, W>::size_t>
backtrace_path(
	IGraph<T, W> const* graph,
	std::vector<typename IGraph<T, W>::size_t> const& back_path,
	typename IGraph<T, W>::size_t const& start,
	typename IGraph<T, W>::size_t const& dest
) {
	auto ret = std::vector<typename IGraph<T, W>::size_t>();

	auto c = dest;

	while (c != back_path[c]) {
		ret.push_back(c);
		c = back_path[c];
	}

	ret.push_back(dest);

	std::reverse(ret.begin(), ret.end());
	return ret;
}

// **W 가**
// - totally_ordered 해야 하고
// - increment 가능해야하고
// - primitive type
	// - integer 타입인 경우, unsigned 여야 하며, zero 값과 infinity 가 있어야 함
	// - float 인 경우  ... unsigned 개념이 없으므로 역시 0.0f 값과 infinity 가 있어야 함.
// - custom type인 경우?

template <class T, class W>
typename IGraph<T, W>::weight_t 
bfs_path_length(
	IGraph<T, W> const* graph, 
	typename IGraph<T, W>::size_t const& start, 
	typename IGraph<T, W>::size_t const& dest
) {

	auto to_visit = std::queue<typename IGraph<T, W>::size_t>();
	auto discovered = std::vector<bool>(graph->vertices_size(), false);
	auto distances = std::vector<typename IGraph<T, W>::weight_t>(graph->vertices_size(), std::numeric_limits<W>::max());

	to_visit.push(start);
	discovered[start] = true;
	distances[start] = W {}; // This should be zero (and maybe zero)

	while (!to_visit.empty()) {
		auto const cv = to_visit.front();

		if (cv == dest) {
			return distances[dest];
		}

		to_visit.pop();
		for (auto const& [_, av_head]: graph->get_adjacents(cv)) {
			if (discovered[av_head]) {
				continue;
			}

			discovered[av_head] = true;
			to_visit.push(av_head);
			distances[av_head] = distances[cv] + 1;
		}
	}

	return distances[dest];
}

template <class T, class W>
std::vector<typename IGraph<T, W>::size_t>
bfs_path(
	IGraph<T, W> const* graph,
	typename IGraph<T, W>::size_t const& start,
	typename IGraph<T, W>::size_t const& dest
) {
	auto to_visit = std::queue<typename IGraph<T, W>::size_t>();
	auto discovered = std::vector<bool>(graph->vertices_size(), false);

	auto path_parent = std::vector<typename IGraph<T, W>::size_t>(graph->vertices_size());
	path_parent[start] = start;

	while (!to_visit.empty()) {
		auto const cv = to_visit.front();
		if (cv == dest) {
			return backtrace_path<T, W>(graph, path_parent, start, dest);
		}

		to_visit.pop();
		for (auto const& [_, av_head]: graph->get_adjacents(cv)) {
			if (discovered[av_head]) {
				continue;
			}

			discovered[av_head] = true;
			to_visit.push(av_head);

			path_parent[av_head] = cv;
		}
	}

	return {};
}


}