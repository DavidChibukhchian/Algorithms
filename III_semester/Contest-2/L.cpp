#include <iostream>
#include <vector>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------

class Disjoint_Set_Union
{
	std::vector<size_t> parent, size;

public:
	Disjoint_Set_Union(size_t max_size);

	size_t find_set(size_t elem);

	void union_set(size_t elem1, size_t elem2);
};

//----------------------------------------------------------------------------------------------------------------

class Graph
{
	size_t vertex_count, edges_count;
	std::vector<std::pair<size_t, std::pair<size_t, size_t>>> graph;

public:
	Graph(size_t vertex_count, size_t edges_count);

	void add_edge(size_t vertex1, size_t vertex2, size_t weight);

	size_t find_MST();
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count, edges_count = 0;
	std::cin >> vertex_count >> edges_count;

	Graph graph(vertex_count, edges_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		size_t vertex1, vertex2, weight = 0;
		std::cin >> vertex1 >> vertex2 >> weight;
		graph.add_edge(vertex1 - 1, vertex2 - 1, weight);
	}

	size_t answer = graph.find_MST();
	std::cout << answer << std::endl;

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Disjoint_Set_Union::Disjoint_Set_Union(size_t max_size)
{
	parent.resize(max_size);
	size.resize(max_size);

	for (size_t i = 0; i < max_size; i++)
	{
		parent[i] = i;
		size[i] = 1;
	}
}

//----------------------------------------------------------------------------------------------------------------

size_t Disjoint_Set_Union::find_set(size_t elem)
{
	if (elem == parent[elem])
		return elem;

	parent[elem] = find_set(parent[elem]);

	return parent[elem];
}

//----------------------------------------------------------------------------------------------------------------

void Disjoint_Set_Union::union_set(size_t elem1, size_t elem2)
{
	elem1 = find_set(elem1);
	elem2 = find_set(elem2);

	if (elem1 != elem2)
	{
		if (size[elem1] < size[elem2])
			std::swap(elem1, elem2);

		parent[elem2] = elem1;
		size[elem1] += size[elem2];
	}
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(size_t v_count, size_t e_count)
{
	vertex_count = v_count;
	edges_count  = e_count;
}

//----------------------------------------------------------------------------------------------------------------

void Graph::add_edge(size_t vertex1, size_t vertex2, size_t weight)
{
	graph.push_back(std::make_pair(weight, std::make_pair(vertex1, vertex2)));
}

//----------------------------------------------------------------------------------------------------------------

size_t Graph::find_MST()
{
	size_t MST = 0;

	std::sort(graph.begin(), graph.end());

	Disjoint_Set_Union DSU(vertex_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		size_t weight  = graph[i].first;
		size_t vertex1 = graph[i].second.first;
		size_t vertex2 = graph[i].second.second;

		if (DSU.find_set(vertex1) != DSU.find_set(vertex2))
		{
			MST += weight;
			DSU.union_set(vertex1, vertex2);
		}
	}

	return MST;
}

//----------------------------------------------------------------------------------------------------------------