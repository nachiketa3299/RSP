#include <string>
#include <iostream>
#include <filesystem>
#include <numeric>
#include <format>

#include "GraphBuilder.h"
#include "Graph.h"
#include "Graph_AdjacencyList.h"

#include "BFS.h"
#include "Dijkstra.h"

int main() {
	std::string const filedir = "../data/graph_data.yaml";

	auto graph_builder = RSP::GraphBuilder<std::string, float>(filedir);
	auto graphs = graph_builder.BuildGraphs<RSP::Graph_AdjacencyList>();

	for (auto const* igraph: graphs) {
		std::cout << "Graph:\n";
		igraph->print();
	}

	auto start = 0;
	auto dest = 6;

	auto const path_length = RSP::bfs_path_length(graphs[0], start, dest);
	std::cout << "Path length by BFS: "; 
	std::cout << RSP::bfs_path_length(graphs[0], start, dest) << std::endl;
	std::cout << "Path length by Dijkstra: "; 
	std::cout << RSP::dijkstra_path_length(graphs[0], start, dest) << std::endl;

	auto const path = RSP::bfs_path(graphs[0], start, dest);

	for (auto const& v: path) {
		std::cout << std::format("{} -> ", v);
	}

	auto graph_bases = graph_builder.BuildGraphs<RSP::Graph>();
	for (auto const* igraph: graph_bases) {
		std::cout << "GraphBases:\n";
		igraph->print();
	}

	return 0;
}