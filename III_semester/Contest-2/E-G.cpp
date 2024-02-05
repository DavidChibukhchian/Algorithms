#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------

class Graph
{
	friend class BridgesFinder;

private:
	size_t vertex_count;

	std::vector<std::vector<size_t>> graph;
	std::map<std::pair<size_t, size_t>, size_t> edges;

	std::pair<size_t, size_t> Edge(size_t vertex1, size_t vertex2) const;

public:
	Graph(size_t vertex_count);

	void AddEdge(size_t vertex1, size_t vertex2, size_t number);
};

//----------------------------------------------------------------------------------------------------------------

class BridgesFinder
{
private:
	size_t time;
	std::vector<bool> visited;
	std::vector<size_t> tin, fup, bridges;

	void DFS(const Graph &graph, size_t vertex, size_t vertex_from);

public:
	std::vector<size_t> FindBridges(const Graph &graph);
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count, edges_count = 0;
	std::cin >> vertex_count >> edges_count;

	Graph graph(vertex_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		size_t vertex1, vertex2 = 0;
		std::cin >> vertex1 >> vertex2;
		graph.AddEdge(vertex1 - 1, vertex2 - 1, i + 1);
	}

	BridgesFinder bridges_finder;
	std::vector<size_t> bridges = bridges_finder.FindBridges(graph);

	std::cout << bridges.size() << std::endl;
	for (size_t i = 0; i < bridges.size(); i++)
	{
		std::cout << bridges[i] << " ";
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(size_t vertex_count)
{
	Graph::vertex_count = vertex_count;
	graph.resize(vertex_count);
}

//----------------------------------------------------------------------------------------------------------------

void Graph::AddEdge(size_t vertex1, size_t vertex2, size_t number)
{
	graph[vertex1].push_back(vertex2);
	graph[vertex2].push_back(vertex1);

	edges[Edge(vertex1, vertex2)] = number;
}

//----------------------------------------------------------------------------------------------------------------

std::pair<size_t, size_t> Graph::Edge(size_t vertex1, size_t vertex2) const
{
	if (vertex1 < vertex2)
	{
		std::swap(vertex1, vertex2);
	}

	return std::make_pair(vertex1, vertex2);
}

//----------------------------------------------------------------------------------------------------------------

std::vector<size_t> BridgesFinder::FindBridges(const Graph &graph)
{
	time = 0;

	visited.resize(graph.vertex_count, false);
	tin.resize(graph.vertex_count);
	fup.resize(graph.vertex_count);

	for (size_t i = 0; i < graph.vertex_count; i++)
	{
		if (!visited[i])
		{
			DFS(graph, i);
		}
	}

	std::sort(bridges.begin(), bridges.end());

	return bridges;
}

//----------------------------------------------------------------------------------------------------------------

void BridgesFinder::DFS(const Graph &graph, size_t vertex, size_t vertex_from = UINT32_MAX)
{
	visited[vertex] = true;
	tin[vertex] = time;
	fup[vertex] = time;
	time++;

	for (size_t vertex_to : graph.graph[vertex])
	{
		if (vertex_to == vertex_from) continue;

		if (visited[vertex_to])
		{
			fup[vertex] = std::min(fup[vertex], tin[vertex_to]);
		}
		else
		{
			DFS(graph, vertex_to, vertex);

			fup[vertex] = std::min(fup[vertex], fup[vertex_to]);

			if (fup[vertex_to] > tin[vertex])
			{
				bridges.push_back(graph.edges.at(graph.Edge(vertex, vertex_to)));
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------------