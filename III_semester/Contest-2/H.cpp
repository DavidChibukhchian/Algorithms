#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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
	std::vector<size_t> bridges;

	std::pair<int, int> edge(int vertex1, int vertex2);

	void DFS(int vertex, int p = -1);

public:
	Graph(int vertex_count);

	void add_edge(int vertex1, int vertex2, size_t number);

	std::vector<size_t> find_bridges();

	std::map<std::pair<int, int>, size_t> edges;

	std::map<size_t, std::pair<int, int>> edges_new;

	std::vector<std::set<int>> graph_new;
};

void DFS_new(std::vector<std::set<int>> &graph_new, int vertex, std::vector<int> &visited_new, int number_of_teams);

//----------------------------------------------------------------------------------------------------------------

int main()
{
	int vertex_count, edges_count = 0;
	std::cin >> vertex_count >> edges_count;

	Graph graph(vertex_count);

	for (size_t i = 1; i <= edges_count; i++)
	{
		int vertex1, vertex2 = 0;
		std::cin >> vertex1 >> vertex2;
		graph.add_edge(vertex1 - 1, vertex2 - 1, i);
	}


	// Находим и удаляем мосты

	std::vector<size_t> bridges = graph.find_bridges();

	for (size_t i = 0; i < bridges.size(); i++)
	{
		int vertex1 = graph.edges_new[bridges[i]].first;
		int vertex2 = graph.edges_new[bridges[i]].second;

		graph.graph_new[vertex1].erase(vertex2);
		graph.graph_new[vertex2].erase(vertex1);
	}


	// Раскрашиваем вершины по компонентам связности

	int number_of_teams = 1;
	std::vector<int> visited_new(vertex_count, NOT_VISITED);

	for (int v = 0; v < vertex_count; v++)
	{
		if (visited_new[v] == NOT_VISITED)
		{
			DFS_new(graph.graph_new, v, visited_new, number_of_teams);
			number_of_teams++;
		}
	}
	number_of_teams--;


	// Для каждой компоненты связности находим соседей (по мостам)

	std::vector<std::vector<int>> components(number_of_teams);

	for (size_t i = 0; i < bridges.size(); i++)
	{
		int vertex1 = graph.edges_new[bridges[i]].first;
		int vertex2 = graph.edges_new[bridges[i]].second;

		components[visited_new[vertex1] - 1].push_back(visited_new[vertex2] - 1);
		components[visited_new[vertex2] - 1].push_back(visited_new[vertex1] - 1);
	}


	// Считаем количество компонент связности, у которых один сосед

	int answer = 0;
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i].size() == 1)
		{
			answer++;
		}
	}



	if (answer % 2 == 0)
	{
		answer = answer / 2;
	}
	else
	{
		answer = answer / 2;
		answer++;
	}

	std::cout << answer << std::endl;

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

void DFS_new(std::vector<std::set<int>> &graph_new, int vertex, std::vector<int> &visited_new, int number_of_teams)
{
	visited_new[vertex] = number_of_teams;

	for (int to : graph_new[vertex])
	{
		if (visited_new[to] == NOT_VISITED)
		{
			DFS_new(graph_new, to, visited_new, number_of_teams);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(int v_count)
{
	vertex_count = v_count;
	time = 0;

	graph.resize(v_count);
	graph_new.resize(v_count);

	visited.resize(v_count);
	tin.resize(v_count);
	fup.resize(v_count);
}

//----------------------------------------------------------------------------------------------------------------

std::pair<int, int> Graph::edge(int vertex1, int vertex2)
{
	if (vertex1 < vertex2)
		return std::make_pair(vertex1, vertex2);
	else
		return std::make_pair(vertex2, vertex1);
}

//----------------------------------------------------------------------------------------------------------------

void Graph::DFS(int vertex, int p)
{
	visited[vertex] = VISITED;

	tin[vertex] = time;
	fup[vertex] = time;
	time++;

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

			if (fup[vertex_to] > tin[vertex])
			{
				bridges.push_back(edges[edge(vertex, vertex_to)]);
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------------

void Graph::add_edge(int vertex1, int vertex2, size_t number)
{
	graph[vertex1].push_back(vertex2);
	graph[vertex2].push_back(vertex1);

	graph_new[vertex1].insert(vertex2);
	graph_new[vertex2].insert(vertex1);

	edges[edge(vertex1, vertex2)] = number;
	edges_new[number] = edge(vertex1, vertex2);
}

//----------------------------------------------------------------------------------------------------------------

std::vector<size_t> Graph::find_bridges()
{
	for (int i = 0; i < vertex_count; i++)
	{
		if (visited[i] == NOT_VISITED)
		{
			DFS(i);
		}
	}

	std::sort(bridges.begin(), bridges.end());

	return bridges;
}

//----------------------------------------------------------------------------------------------------------------