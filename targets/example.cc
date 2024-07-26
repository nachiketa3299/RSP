#include <string>
#include <iostream>
#include <filesystem>

#include "DataFilePath.h"

#include "GraphBuilder.h"
#include "Graph.h"
#include "Graph_AdjacencyList.h"

#include "BFS.h"
#include "Dijkstra.h"

int main() {
	// Check Files
	std::string const file_path = std::string(DATA_FILE_PATH) + std::string("graph_data.yaml");

	std::cout << "Graph Data File Path: " << file_path << std::endl;

	if (!std::filesystem::exists(file_path)) {
		std::cerr << "File  does not exist: " << file_path << std::endl;
		return EXIT_FAILURE;
	}

	auto graph_builder = RSP::GraphBuilder<std::string, float>(file_path);
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