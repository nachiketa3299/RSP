#pragma once

#include <yaml-cpp/yaml.h>
#include <vector>
#include <iostream>
#include <string>

#include "IGraph.h"
#include "GraphAdj.h"

namespace RSP {

template <class T, class W>
class GraphBuilder {
	static constexpr char k_graph[] = "graph";
	static constexpr char k_edges[] = "edges";
	static constexpr char k_from[] = "from";
	static constexpr char k_vertices[] = "vertices";
	static constexpr char k_to[] = "to";
	static constexpr char k_weight[] = "weight";

public:
	GraphBuilder() = default;
	GraphBuilder(std::string const& filedir) {
		auto const yml_file = YAML::LoadFile(filedir);

		if (yml_file[k_vertices]) {
			for (auto const& vertex: yml_file[k_vertices]) {
				vertices_.push_back(vertex.template as<T>());
			}
		}

		if (yml_file[k_edges]) {
			for (auto const& edge: yml_file[k_edges]) {
				auto const from = edge[k_from].template as<std::size_t>();
				auto const to = edge[k_to].template as<std::size_t>();
				auto const weight = edge[k_weight].template as<W>();

				edges_.push_back({weight, from, to});
			}
		}

		// for (auto const& v: vertices_) {
		// 	std::cout << v << ", ";
		// }
		// std::cout << '\n';

		// for (auto const& [w, f, t]: edges_) {
		// 	std::cout << "(" << w << ", " << f << ", " << t << "), ";
		// }
		// std::cout << '\n';
	}

public:
	GraphAdj<T, W> instantiate_by_adjacency_graph() const {
		return GraphAdj<T, W>(vertices_, edges_);
	};

private:

	std::vector<T> vertices_;
	std::vector<std::tuple<W, std::size_t, std::size_t>> edges_;
};

}