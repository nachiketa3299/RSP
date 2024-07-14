#pragma once

#include <concepts>
#include <cstddef>
#include <tuple>

namespace RSP {

template <std::totally_ordered W>
struct IGraph {
	using size_t = std::size_t;
	using weight_t = W;
	using adj_t = std::pair<weight_t, size_t>;
	using edge_t = std::tuple<weight_t, size_t, size_t>;

	virtual ~IGraph() = default;

	virtual std::vector<adj_t> get_adjacents(size_t const& idx) const = 0;
	virtual void add_edge(edge_t const& edge) = 0;
};

}