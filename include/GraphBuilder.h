#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <yaml-cpp/yaml.h>

#include "IGraph.h"

namespace RSP {

template <class T, std::totally_ordered W>
class GraphBuilder {
public:
	using value_t = typename IGraph<T, W>::value_t;
	using weight_t = typename IGraph<T, W>::weight_t;
	using size_t = typename IGraph<T, W>::size_t;
	using edge_t = typename IGraph<T, W>::edge_t; // (w, v_i, v_j)

	using graph_t = std::pair<std::vector<value_t>, std::vector<edge_t>>; // G = (V, E)

	GraphBuilder(std::string const& file_dir) {
		auto const top_yml_graphs = YAML::LoadFile(file_dir);

		graphs_.resize(top_yml_graphs.size());

		for (auto i = 0; i < top_yml_graphs.size(); ++i) {
			auto& [vertices, edges] = graphs_[i];

			// Process raw vertices
			// assumes there is no overlapping vertex values
			// ex) there is no vertices set like ["a", "a", "c"]

			auto const& raw_vertices = top_yml_graphs[i]["vertices"];
			vertices.resize(raw_vertices.size());

			for (auto j = 0; j < raw_vertices.size(); ++j) {
				vertices[j] = raw_vertices[j].template as<value_t>();
			}

			auto get_idx = [&vertices] (auto const& vval) {
				auto sit = vertices.cbegin();
				auto eit = vertices.cend();
				return static_cast<size_t>(std::find(sit, eit, vval) - sit);
			};

			// Process raw edges

			auto const& raw_edges = top_yml_graphs[i]["edges"];
			edges.resize(raw_edges.size());

			for (auto j = 0; j < raw_edges.size(); ++j) {
				auto const tail_v = raw_edges[j][0].template as<value_t>();
				auto const head_v = raw_edges[j][1].template as<value_t>();

				auto& [weight, tail_i, head_i] = edges[j];

				tail_i  = get_idx(tail_v);
				head_i  = get_idx(head_v);

				weight = raw_edges[j][2].template as<weight_t>();
			}
		}
	}


	template <template <class, class> class G> requires IGraphDerived<G, value_t, weight_t>
	std::vector<IGraph<value_t, weight_t>*> BuildGraphs() const {
		auto ret = std::vector<IGraph<value_t, weight_t>*>(graphs_.size(), nullptr);

		for (auto i = 0; i < graphs_.size(); ++i) {
			auto const& [vertices, edges] = graphs_[i];
			ret[i] = new G<value_t, weight_t>(vertices, edges);
		}

		return ret;
	}

	size_t size() const {
		return graphs_.size();
	}

	graph_t const&  operator[](size_t i) const {
		return graphs_[i];
	}

private:
	std::vector<graph_t> graphs_;
};

}