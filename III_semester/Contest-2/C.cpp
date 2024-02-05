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

void DFS(std::vector<std::vector<int>> &graph, int vertex, std::vector<vertex_status> &visited, bool &has_cycle,
         std::vector<int> &order);

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
	std::vector<int> order;

	bool has_cycle  = false;

	for (int v = 0; v < vertex_count; v++)
	{
		if (visited[v] == vertex_status::white)
		{
			DFS(graph, v, visited, has_cycle, order);
			if (has_cycle) break;
		}
	}


	if (has_cycle)
	{
		std::cout << -1 << std::endl;
	}
	else
	{
		std::reverse(order.begin(), order.end());
		for (int i = 0; i < order.size(); i++)
		{
			std::cout << order[i] + 1 << " ";
		}
	}


	return 0;
}

//----------------------------------------------------------------------------------------------------------------

void DFS(std::vector<std::vector<int>> &graph, int vertex, std::vector<vertex_status> &visited, bool &has_cycle,
         std::vector<int> &order)
{
	visited[vertex] = vertex_status::grey;

	for (int to : graph[vertex])
	{
		if (visited[to] == vertex_status::white)
		{
			DFS(graph, to, visited, has_cycle, order);
			if (has_cycle) return;
		}
		else if (visited[to] == vertex_status::grey)
		{
			has_cycle = true;
			return;
		}
	}

	order.push_back(vertex);
	visited[vertex] = vertex_status::black;
}

//----------------------------------------------------------------------------------------------------------------