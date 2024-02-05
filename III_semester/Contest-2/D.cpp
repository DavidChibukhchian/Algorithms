#include <iostream>
#include <vector>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------

const size_t     VISITED = 1;
const size_t NOT_VISITED = 0;

//----------------------------------------------------------------------------------------------------------------

class Graph
{
	friend std::istream &operator>>(std::istream &input, Graph &graph);
	friend class FinderSCC;

private:
	size_t edges_count;
	std::vector<std::vector<size_t>> graph, graph_reversed;

public:
	Graph(size_t vertex_count, size_t edges_count);

	void AddEdge(size_t vertex1, size_t vertex2);
};

//----------------------------------------------------------------------------------------------------------------

std::istream &operator>>(std::istream &input, Graph &graph);

//----------------------------------------------------------------------------------------------------------------

class FinderSCC
{
private:
	std::vector<size_t> visited, order, vertex_colors;

	void DFS(const std::vector<std::vector<size_t>> &graph, size_t vertex, bool coloring = false, size_t curr_color = NOT_VISITED);

public:
	std::vector<size_t> FindSCC(const Graph &graph);

	size_t SCC_count;
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count, edges_count = 0;
	std::cin >> vertex_count >> edges_count;

	Graph graph(vertex_count, edges_count);
	std::cin >> graph;

	FinderSCC finder_scc;
	std::vector<size_t> SCC = finder_scc.FindSCC(graph);

	std::cout << finder_scc.SCC_count << std::endl;
	for (size_t i = 0; i < SCC.size(); i++)
	{
		std::cout << SCC[i] << " ";
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(size_t vertex_count, size_t edges_count)
{
	Graph::edges_count = edges_count;

	graph.resize(vertex_count);
	graph_reversed.resize(vertex_count);
}

//----------------------------------------------------------------------------------------------------------------

void Graph::AddEdge(size_t vertex1, size_t vertex2)
{
	graph[vertex1].push_back(vertex2);
	graph_reversed[vertex2].push_back(vertex1);
}

//----------------------------------------------------------------------------------------------------------------

std::vector<size_t> FinderSCC::FindSCC(const Graph &graph)
{
	visited.assign(graph.graph.size(), NOT_VISITED);
	vertex_colors.assign(graph.graph.size(), NOT_VISITED);

	for (size_t vertex = 0; vertex < graph.graph.size(); vertex++)
	{
		if (visited[vertex] == NOT_VISITED)
		{
			DFS(graph.graph_reversed, vertex);
		}
	}
	std::reverse(order.begin(), order.end());


	visited.assign(graph.graph.size(), NOT_VISITED);

	size_t number_of_SCC = 0;
	for (size_t vertex : order)
	{
		if (visited[vertex] == NOT_VISITED)
		{
			number_of_SCC++;
			DFS(graph.graph, vertex, true, number_of_SCC);
		}
	}
	SCC_count = number_of_SCC;


	for (size_t i = 0; i < vertex_colors.size(); i++)
	{
		vertex_colors[i] = number_of_SCC - vertex_colors[i] + 1;
	}


	return vertex_colors;
}

//----------------------------------------------------------------------------------------------------------------

void FinderSCC::DFS(const std::vector<std::vector<size_t>> &graph, size_t vertex, bool coloring, size_t curr_color)
{
	visited[vertex] = VISITED;

	for (size_t vertex_to : graph[vertex])
	{
		if (visited[vertex_to] == NOT_VISITED)
		{
			DFS(graph, vertex_to, coloring, curr_color);
		}
	}

	if (coloring)
		vertex_colors[vertex] = curr_color;
	else
		order.push_back(vertex);
}

//----------------------------------------------------------------------------------------------------------------

std::istream &operator>>(std::istream &input, Graph &graph)
{
	for (size_t i = 0; i < graph.edges_count; i++)
	{
		size_t vertex1, vertex2 = 0;
		input >> vertex1 >> vertex2;
		graph.AddEdge(vertex1 - 1, vertex2 - 1);
	}

	return input;
}

//----------------------------------------------------------------------------------------------------------------