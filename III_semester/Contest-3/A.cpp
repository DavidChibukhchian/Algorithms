#include <iostream>
#include <vector>
#include <set>

//----------------------------------------------------------------------------------------------------------------

class Graph
{
private:
	size_t vertex_count;
	std::vector<std::vector<std::pair<size_t, size_t>>> graph;

public:
	Graph(size_t vertex_count);

	void add_edge(size_t vertex1, size_t vertex2, size_t weight);

	std::vector<size_t> find_shortest_paths(size_t start_vertex);
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t request_count;
	std::cin >> request_count;

	for (size_t i = 0; i < request_count; i++)
	{
		size_t vertex_count, edges_count, start_vertex;
		std::cin >> vertex_count >> edges_count;

		Graph graph(vertex_count);

		for (size_t j = 0; j < edges_count; j++)
		{
			size_t vertex1, vertex2, weight;
			std::cin >> vertex1 >> vertex2 >> weight;
			graph.add_edge(vertex1, vertex2, weight);
		}
		std::cin >> start_vertex;

		std::vector<size_t> shortest_paths = graph.find_shortest_paths(start_vertex);

		for (size_t j = 0; j < vertex_count; j++)
		{
			std::cout << shortest_paths[j] << ' ';
		}
		std::cout << '\n';
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

void Graph::add_edge(size_t vertex1, size_t vertex2, size_t weight)
{
	graph[vertex1].push_back(std::make_pair(vertex2, weight));
	graph[vertex2].push_back(std::make_pair(vertex1, weight));
}

//----------------------------------------------------------------------------------------------------------------

std::vector<size_t> Graph::find_shortest_paths(size_t start_vertex)
{
	const size_t INF = 2009000999;
	std::vector<size_t> dist(vertex_count, INF);
	dist[start_vertex] = 0;

	std::set<std::pair<size_t, size_t>> unvisited_vertices;
	unvisited_vertices.insert(std::make_pair(dist[start_vertex], start_vertex));

	while(!unvisited_vertices.empty())
	{
		size_t nearest_vertex = unvisited_vertices.begin()->second;
		unvisited_vertices.erase(unvisited_vertices.begin());

		for (auto &[vertex_to, weight] : graph[nearest_vertex])
		{
			if (dist[vertex_to] > dist[nearest_vertex] + weight)
			{
				unvisited_vertices.erase( std::make_pair(dist[vertex_to], vertex_to));
				dist[vertex_to] = dist[nearest_vertex] + weight;
				unvisited_vertices.insert(std::make_pair(dist[vertex_to], vertex_to));
			}
		}
	}

	return dist;
}

//----------------------------------------------------------------------------------------------------------------