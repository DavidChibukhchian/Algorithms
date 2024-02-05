#include <iostream>
#include <vector>

//----------------------------------------------------------------------------------------------------------------

class Graph
{
private:
	struct Edge
	{
		size_t vertex1, vertex2;
		int weight;
	};
	std::vector<Edge> graph;
	size_t vertex_count;

public:
	Graph(size_t vertex_count);

	void add_edge(size_t vertex1, size_t vertex2, int weight);

	std::vector<int> find_shortest_paths();
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count, edges_count;
	std::cin >> vertex_count >> edges_count;

	Graph graph(vertex_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		size_t vertex1, vertex2;
		int weight;
		std::cin >> vertex1 >> vertex2 >> weight;
		graph.add_edge(vertex1 - 1, vertex2 - 1, weight);
	}

	std::vector<int> shortest_paths = graph.find_shortest_paths();

	for (size_t i = 0; i < vertex_count; i++)
	{
		std::cout << shortest_paths[i] << ' ';
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(size_t vertex_count)
{
	Graph::vertex_count = vertex_count;
}

//----------------------------------------------------------------------------------------------------------------

void Graph::add_edge(size_t vertex1, size_t vertex2, int weight)
{
	graph.push_back({vertex1, vertex2, weight});
}

//----------------------------------------------------------------------------------------------------------------

std::vector<int> Graph::find_shortest_paths()
{
	const int INF = 30000;
	std::vector<int> dist(vertex_count, INF);
	dist[0] = 0;

	for (size_t i = 0; i < vertex_count; i++)
	{
		for (auto &[vertex_to, vertex_from, weight] : graph)
		{
			if ((dist[vertex_to] != INF) && (dist[vertex_from] > dist[vertex_to] + weight))
			{
				dist[vertex_from] = dist[vertex_to] + weight;
			}
		}
	}

	return dist;
}

//----------------------------------------------------------------------------------------------------------------