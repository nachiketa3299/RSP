#pragma once

#include <cstddef>
#include <tuple>
#include <concepts>

namespace RSP {

template <class T, std::totally_ordered W>
class IGraph {
public:
	using value_t = T;
	using weight_t = W;
	using size_t = std::size_t;
	using adj_t = std::pair<weight_t, size_t>;
	using edge_t = std::tuple<weight_t, size_t, size_t>;

	virtual ~IGraph() = default;

	virtual std::vector<adj_t> const& get_adjacents(size_t const& idx) const = 0;
	virtual value_t const& get_vertex_value_at(size_t const& idx) const = 0;
	virtual size_t vertices_size() const = 0;

	virtual void print() const = 0;
};

template <template <class, class> class G, class T, class W>
concept IGraphDerived = std::derived_from<G<T, W>, IGraph<T, W>>;

}