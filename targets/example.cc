#include <string>
#include <iostream>
#include <filesystem>

#include "GraphBuilder.h"
#include "Graph_AdjacencyList.h"

int main() {
	std::string const filedir = "../data/graph_data.yaml";

	auto graph_builder = RSP::GraphBuilder<std::string, float>(filedir);
	auto graphs = graph_builder.BuildGraphs<RSP::Graph_AdjacencyList>();

	for (auto const* igraph: graphs) {
		std::cout << ">= Graph:\n";
		igraph->print();
	}

	return 0;
}