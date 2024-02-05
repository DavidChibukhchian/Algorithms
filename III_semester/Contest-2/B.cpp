#include <iostream>
#include <vector>

//----------------------------------------------------------------------------------------------------------------

enum class vertex_status
{
	white,
	black
};

//----------------------------------------------------------------------------------------------------------------

void DFS(std::vector<std::vector<int>> &graph, int vertex,
         std::vector<vertex_status> &visited, std::vector<int> &teams);

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
		graph[v2].push_back(v1);
	}


	std::vector<vertex_status> visited(vertex_count, vertex_status::white);
	std::vector<std::vector<int>> teams(vertex_count);

	int team = 0;
	for (int v = 0; v < vertex_count; v++)
	{
		if (visited[v] == vertex_status::white)
		{
			DFS(graph, v, visited, teams[team]);
			team++;
		}
	}


	std::cout << team << std::endl;
	for (int i = 0; i < team; i++)
	{
		std::cout << teams[i].size() << std::endl;

		for (int j = 0; j < teams[i].size(); j++)
		{
			std::cout << teams[i][j] + 1 << " ";
		}
		std::cout << "\n";
	}


	return 0;
}

//----------------------------------------------------------------------------------------------------------------

void DFS(std::vector<std::vector<int>> &graph, int vertex,
         std::vector<vertex_status> &visited, std::vector<int> &teams)
{
	visited[vertex] = vertex_status::black;
	teams.push_back(vertex);

	for (int to : graph[vertex])
	{
		if (visited[to] == vertex_status::white)
		{
			DFS(graph, to, visited, teams);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------