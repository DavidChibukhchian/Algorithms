#include <iostream>
#include <vector>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------

enum class vertex_status
{
	white,
	grey,
	black
};

//----------------------------------------------------------------------------------------------------------------

void DFS(std::vector<std::vector<int>> &graph, int vertex, std::vector<vertex_status> &visited,
         std::vector<int> &from, bool &has_cycle, int &last_vertex);

void restore_cycle(std::vector<int> &cycle, std::vector<int> &from, int last_vertex);

//----------------------------------------------------------------------------------------------------------------

int main()
{
	int vertex_count, edges_count = 0;
	std::cin >> vertex_count >> edges_count;

	std::vector<std::vector<int>> graph(vertex_count);

	int v1, v2;
	for (int i = 0; i < edges_count; i++)
	{
		std::cin >> v1 >> v2;
		v1--; v2--;
		graph[v1].push_back(v2);
	}


	std::vector<vertex_status> visited(vertex_count, vertex_status::white);
	std::vector<int> from(vertex_count, -1);

	bool has_cycle  = false;
	int last_vertex = 0;

	for (int v = 0; v < vertex_count; v++)
	{
		if (visited[v] == vertex_status::white)
		{
			DFS(graph, v, visited, from, has_cycle, last_vertex);
			if (has_cycle) break;
		}
	}

	
	if (has_cycle)
	{
		std::cout << "YES" << std::endl;

		std::vector<int> cycle;
		restore_cycle(cycle, from, last_vertex);

		for (int i = 0; i < cycle.size(); i++)
		{
			std::cout << cycle[i] + 1 << " ";
		}
	}
	else
	{
		std::cout << "NO" << std::endl;
	}


	return 0;
}

//----------------------------------------------------------------------------------------------------------------

void DFS(std::vector<std::vector<int>> &graph, int vertex, std::vector<vertex_status> &visited,
         std::vector<int> &from, bool &has_cycle, int &last_vertex)
{
	visited[vertex] = vertex_status::grey;

	for (int to : graph[vertex])
	{
		if (visited[to] == vertex_status::white)
		{
			from[to] = vertex;
			DFS(graph, to, visited, from, has_cycle, last_vertex);

			if (has_cycle) return;
		}
		else if (visited[to] == vertex_status::grey)
		{
			from[to] = vertex;
			last_vertex = to;
			has_cycle = true;
			return;
		}
	}

	visited[vertex] = vertex_status::black;
}

//----------------------------------------------------------------------------------------------------------------

void restore_cycle(std::vector<int> &cycle, std::vector<int> &from, int last_vertex)
{
	int temp = last_vertex;

	while (from[temp] != last_vertex)
	{
		cycle.push_back(from[temp]);
		temp = from[temp];
	}

	cycle.push_back(last_vertex);

	std::reverse(cycle.begin(), cycle.end());
}

//----------------------------------------------------------------------------------------------------------------