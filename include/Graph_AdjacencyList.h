#pragma once

#include <vector>
#include <format>

#include "IGraph.h"

namespace RSP {

template <class T, class W>
class Graph_AdjacencyList : public IGraph<T, W> {
public:
	using value_t = typename IGraph<T, W>::value_t;
	using weight_t = typename IGraph<T, W>::weight_t;
	using size_t = typename IGraph<T, W>::size_t;
	using adj_t = typename IGraph<T, W>::adj_t;
	using edge_t = typename IGraph<T, W>::edge_t;

public:
	Graph_AdjacencyList(std::vector<value_t> const& vertices, std::vector<edge_t> const& edges)
		: vertices_(vertices) 
		, adj_list_(vertices.size())
	{
		for (auto const& edge: edges) {
			add_edge(edge);
		}
	}

private:
	void add_edge(edge_t const& edge) {
		auto const& [weight, tail, head] = edge;
		adj_list_[tail].push_back(adj_t {weight, head});
	}

public: // IGraph Impl
	std::vector<adj_t> get_adjacents(size_t const& vidx) const override {
		return adj_list_[vidx];
	}

	value_t const& get_vertex_value_at(size_t const& idx) const override {
		return vertices_[idx];
	}

	void print() const override {
		std::cout << "- adj_list:\n";

		for (auto i = 0; i < adj_list_.size(); ++i) {
			std::cout << std::format("({:0>2}, {}): ", i, vertices_[i]);

			for (auto j = 0; j < adj_list_[i].size(); ++j) {
				auto const& [weight, to] = adj_list_[i][j];
				std::cout << std::format("[{:>5}, ({:0>2}, {})]", weight, to, vertices_[to]);

				if (j != adj_list_[i].size() - 1)
					std::cout << ", ";
			}
			std::cout << "\n";
		}

		std::cout << "\n";
	}

private:	
	std::vector<value_t> vertices_;
	std::vector<std::vector<adj_t>> adj_list_;
};

} // namespace 