#pragma once

#include <vector>
#include <format>

namespace RSP {

template <class T, class W>
class Graph : public IGraph<T, W> {
public:
	using value_t = typename IGraph<T, W>::value_t;
	using weight_t = typename IGraph<T, W>::weight_t;
	using size_t = typename IGraph<T, W>::size_t;
	using adj_t = typename IGraph<T, W>::adj_t;
	using edge_t = typename IGraph<T, W>::edge_t;

public:
	Graph(std::vector<value_t> const& vertices, std::vector<edge_t> const& edges) 
		: vertices_(vertices)
		, edges_(edges)
	{}

public: // IGraph Impl
	std::vector<adj_t> const& get_adjacents(size_t const& vidx) const override { /* TODO */ return {}; }

	value_t const& get_vertex_value_at(size_t const& idx) const override {
		return vertices_[idx];
	}

	size_t vertices_size() const override {
		return vertices_.size();
	}

	size_t edges_size() const override {
		return edges_.size();
	}

	std::vector<value_t> const& vertices() const override {
		return vertices_;
	}

	std::vector<edge_t> const& edges() const override {
		return edges_;
	}

	void print() const override { 
		std::cout << "- Vertices:\n";
		for (auto i = 0; i < vertices_size(); ++i) {
			std::cout << std::format("\t({:0>2}, {})\n", i, vertices_[i]);
		}
		std::cout << "- Edges:\n";
		for (auto i = 0; i < edges_size(); ++i) {
			auto const& [w, f, t] = edges_[i];
			std::cout << std::format("\t[w: {:>5}, f: {:0>2}, t: {:0>2}]\n", w, f, t);
		}
	}

protected:
	std::vector<value_t> vertices_;
	std::vector<edge_t> edges_;
};

}