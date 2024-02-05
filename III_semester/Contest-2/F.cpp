#include <iostream>
#include <vector>
#include <set>

//----------------------------------------------------------------------------------------------------------------

const int     VISITED = 1;
const int NOT_VISITED = 0;

//----------------------------------------------------------------------------------------------------------------

class Graph
{
	int vertex_count, time;

	std::vector<std::vector<int>> graph;
	std::vector<int> visited, tin, fup;
	std::set<int> cut_vertices;

	void DFS(int vertex, int p);

public:
	Graph(int vertex_count);

	void add_edge(int vertex1, int vertex2);

	std::set<int> find_cut_vertices();
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	int vertex_count, edges_count = 0;
	std::cin >> vertex_count >> edges_count;

	Graph graph(vertex_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		int vertex1, vertex2 = 0;
		std::cin >> vertex1 >> vertex2;
		graph.add_edge(vertex1 - 1, vertex2 - 1);
	}

	std::set<int> cut_vertices = graph.find_cut_vertices();

	std::cout << cut_vertices.size() << std::endl;
	for (int cut_vertex : cut_vertices)
	{
		std::cout << cut_vertex << std::endl;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(int v_count)
{
	vertex_count = v_count;
	time = 0;

	graph.resize(v_count);
	visited.resize(v_count);
	tin.resize(v_count);
	fup.resize(v_count);
}

//----------------------------------------------------------------------------------------------------------------

void Graph::DFS(int vertex, int p)
{
	visited[vertex] = VISITED;

	tin[vertex] = time;
	fup[vertex] = time;
	time++;

	int k = 0;

	for (int vertex_to : graph[vertex])
	{
		if (vertex_to == p) continue;

		if (visited[vertex_to] == VISITED)
		{
			fup[vertex] = std::min(fup[vertex], tin[vertex_to]);
		}
		else
		{
			DFS(vertex_to, vertex);

			fup[vertex] = std::min(fup[vertex], fup[vertex_to]);

			if ((fup[vertex_to] >= tin[vertex]) && (p != -1))
			{
				cut_vertices.insert(vertex + 1);
			}

			k++;
		}
	}

	if ((p == -1) && (k > 1))
	{
		cut_vertices.insert(vertex + 1);
	}
}

//----------------------------------------------------------------------------------------------------------------

void Graph::add_edge(int vertex1, int vertex2)
{
	graph[vertex1].push_back(vertex2);
	graph[vertex2].push_back(vertex1);
}

//----------------------------------------------------------------------------------------------------------------

std::set<int> Graph::find_cut_vertices()
{
	for (int i = 0; i < vertex_count; i++)
	{
		if (visited[i] == NOT_VISITED)
		{
			DFS(i, -1);
		}
	}

	return cut_vertices;
}

//----------------------------------------------------------------------------------------------------------------