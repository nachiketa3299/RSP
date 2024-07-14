#include <string>
#include <iostream>
#include <filesystem>

// #include "GraphAdj.h"
#include "GraphBuilder.h"

using namespace RSP;

int main() {
	std::string const filedir = "../data/graph_data.yaml";
	auto gb = GraphBuilder<std::string, float>(filedir);
	auto g = gb.instantiate_by_adjacency_graph();

	return 0;
}