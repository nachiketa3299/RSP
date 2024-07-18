#include <string>
#include <iostream>
#include <filesystem>
#include <numeric>

#include "GraphBuilder.h"
#include "Graph_AdjacencyList.h"
#include "BFS.h"

int main() {
	std::string const filedir = "../data/graph_data.yaml";

	auto graph_builder = RSP::GraphBuilder<std::string, float>(filedir);
	auto graphs = graph_builder.BuildGraphs<RSP::Graph_AdjacencyList>();

	for (auto const* igraph: graphs) {
		std::cout << ">= Graph:\n";
		igraph->print();
	}

	auto const path_length = RSP::BFS_path_length(graphs[0], 0, 3, 0.0f, std::numeric_limits<float>::max());
	std::cout << path_length;

	return 0;
}