#pragma once

#include <vector>

#include "IGraph.h"

namespace RSP {

template <class T, class W>
class GraphAdj : public IGraph<W> {
public:
	using size_t = typename IGraph<W>::size_t;
	using weight_t = typename IGraph<W>::weight_t;
	using edge_t = typename IGraph<W>::edge_t;
	using adj_t = typename IGraph<W>::adj_t;

	using value_t = T;

public:
	GraphAdj() = default;
	GraphAdj(std::vector<value_t> const& vertices, std::vector<edge_t> const& edges)
		: vertices_(vertices) 
		, adj_list_(vertices.size())
	{
		for (auto const& edge: edges) {
			add_edge(edge);
		}

		std::cout << " Oh Y ea h ! ";
	}

public:
	std::vector<adj_t> get_adjacents(size_t const& vidx) const override {
		return adj_list_[vidx];
	}

	void add_edge(edge_t const& edge) override {
		auto const& [weight, from, to] = edge;
		adj_list_[from].push_back(adj_t {weight, to});
	}

private:	
	std::vector<value_t> vertices_;
	std::vector<std::vector<adj_t>> adj_list_;
};

} // namespace 