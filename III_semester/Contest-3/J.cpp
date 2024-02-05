#include <iostream>
#include <vector>
#include <cstdint>

//----------------------------------------------------------------------------------------------------------------

class Graph
{
private:
	size_t vertex_count_1, vertex_count_2;
	std::vector<std::vector<size_t>> graph;

	std::vector<bool> used;

	bool dfs(size_t vertex);

public:
	std::vector<size_t> maximum_matching;

	Graph(size_t vertex_count_1, size_t vertex_count_2);

	void add_edge(size_t vertex1, size_t vertex2);

	size_t find_maximum_matching();
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count_1, vertex_count_2;
	std::cin >> vertex_count_1 >> vertex_count_2;

	Graph graph(vertex_count_1, vertex_count_2);

	for (size_t i = 0; i < vertex_count_1; i++)
	{
		size_t vertex;
		std::cin >> vertex;

		while (vertex != 0)
		{
			graph.add_edge(i, vertex - 1);
			std::cin >> vertex;
		}
	}

	size_t answer = graph.find_maximum_matching();
	std::cout << answer << '\n';
	for (size_t i = 0; i < vertex_count_2; i++)
	{
		if (graph.maximum_matching[i] != UINT16_MAX)
		{
			std::cout << graph.maximum_matching[i] + 1 << ' ' << i + 1 << '\n';
		}
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(size_t vertex_count_1, size_t vertex_count_2)
{
	Graph::vertex_count_1 = vertex_count_1;
	Graph::vertex_count_2 = vertex_count_2;

	graph.resize(vertex_count_1);
	used.resize(vertex_count_1);
}

//----------------------------------------------------------------------------------------------------------------

void Graph::add_edge(size_t vertex1, size_t vertex2)
{
	graph[vertex1].push_back(vertex2);
}

//----------------------------------------------------------------------------------------------------------------

size_t Graph::find_maximum_matching()
{
	size_t edges_count = 0;

	maximum_matching.resize(vertex_count_2, UINT16_MAX);

	for (size_t i = 0; i < vertex_count_1; i++)
	{
		used.assign(vertex_count_1, false);
		if (dfs(i)) edges_count++;
	}

	return edges_count;
}

//----------------------------------------------------------------------------------------------------------------

bool Graph::dfs(size_t vertex)
{
	if (used[vertex]) return false;
	used[vertex] = true;

	for (size_t vertex_to : graph[vertex])
	{
		if ((maximum_matching[vertex_to] == UINT16_MAX) || (dfs(maximum_matching[vertex_to])))
		{
			maximum_matching[vertex_to] = vertex;
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------