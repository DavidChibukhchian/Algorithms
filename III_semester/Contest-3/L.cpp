#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

//----------------------------------------------------------------------------------------------------

class Graph
{
private:
	size_t vertex_count;
	std::vector<std::vector<size_t>> graph, residual_graph;
	std::vector<size_t> parent;
	std::vector<bool> visited;

	bool bfs(size_t source, size_t sink);

public:
	Graph(size_t vertex_count);

	void add_edge(size_t vertex1, size_t vertex2, size_t weight);

	size_t find_max_flow(size_t source, size_t sink);
};

//----------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count, edges_count = 0;
	std::cin >> vertex_count >> edges_count;

	Graph graph(vertex_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		size_t vertex1, vertex2, weight;
		std::cin >> vertex1 >> vertex2 >> weight;
		graph.add_edge(vertex1 - 1, vertex2 - 1, weight);
	}

	size_t max_flow = graph.find_max_flow(0, vertex_count - 1);

	std::cout << max_flow << '\n';

	return 0;
}

//----------------------------------------------------------------------------------------------------

Graph::Graph(size_t vertex_count)
{
	Graph::vertex_count = vertex_count;

	parent.resize(vertex_count);

	graph.resize(vertex_count);
	for (size_t i = 0; i < vertex_count; i++)
	{
		graph[i].resize(vertex_count);
	}
}

//----------------------------------------------------------------------------------------------------

void Graph::add_edge(size_t vertex1, size_t vertex2, size_t weight)
{
	graph[vertex1][vertex2] = weight;
}

//----------------------------------------------------------------------------------------------------

size_t Graph::find_max_flow(size_t source, size_t sink)
{
	size_t max_flow = 0;
	residual_graph = graph;

	while (bfs(source, sink))
	{
		size_t path_flow = UINT16_MAX;

		for (size_t vertex = sink; vertex != source; vertex = parent[vertex])
		{
			size_t parent_vertex = parent[vertex];
			path_flow = std::min(path_flow, residual_graph[parent_vertex][vertex]);
		}

		for (size_t vertex = sink; vertex != source; vertex = parent[vertex])
		{
			size_t parent_vertex = parent[vertex];
			residual_graph[parent_vertex][vertex] -= path_flow;
			residual_graph[vertex][parent_vertex] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}

//----------------------------------------------------------------------------------------------------

bool Graph::bfs(size_t source, size_t sink)
{
	std::queue<size_t> queue;
	queue.push(source);

	parent[source] = UINT16_MAX;
	visited.assign(vertex_count, false);
	visited[source] = true;

	while (!queue.empty())
	{
		size_t u = queue.front();
		queue.pop();

		for (size_t v = 0; v < vertex_count; v++)
		{
			if (!visited[v] && (residual_graph[u][v] > 0))
			{
				if (v == sink)
				{
					parent[v] = u;
					return true;
				}

				queue.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return false;
}

//----------------------------------------------------------------------------------------------------