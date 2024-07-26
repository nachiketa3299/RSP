# RSP <sup><i>Shortest Path Algorithms by RZN</i></sup>

## Dependency
- [jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)
- For using `<format>`, 
	- Above C++20 required
	- Not all compilers implements `<format>`

## Data Structures

- `GraphBuilder` converts yaml graph data in `data/` to graph data.
- `IGraph` is ADT of graph, use this interface to handle graphs without knowing specific implementation.
- Currently only `Graph_AdjacencyList` implemented. (TODO)

## Shortest Path Algorithms

- Breadth First Search
- Dijkstra
- Bellman-Ford
- Floyd-Warshall
- A\*

# Todos

- [X] Implement graph using adjacency list
- [ ] Implement graph using adjacency matrix 
- [ ] Divide implementation for:
	- *Single Pair*
	- *Single Source*
	- *Single Destination*
	- *All Pairs*
- [ ] Implement not only for path length, but returning path itself