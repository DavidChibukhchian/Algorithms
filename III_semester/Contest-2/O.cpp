#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------

class DisjointSetUnion
{
private:
	std::vector<size_t> parent, size;

public:
	DisjointSetUnion(size_t set_count);

	size_t FindSet(size_t set);

	void UnionSets(size_t set1, size_t set2);
};

//----------------------------------------------------------------------------------------------------------------

class Graph
{
private:
	size_t vertex_count, edges_count;
	std::vector<std::pair<size_t, std::pair<size_t, size_t>>> graph;

public:
	Graph(size_t vertex_count, size_t edges_count);

	void AddEdge(size_t vertex1, size_t vertex2, size_t weight);

	std::vector<std::vector<std::pair<size_t, size_t>>> FindMaxST();
};

//----------------------------------------------------------------------------------------------------------------

class SpanningTree
{
private:
	size_t vertex_count, log_vertex_count, timer;

	std::vector<size_t> tin, tout;
	std::vector<std::vector<size_t>> up;

	bool Upper(size_t vertex1, size_t vertex2);

	void DFS(size_t vertex, size_t vertex_from, size_t height);

	size_t FindLCA(size_t vertex1, size_t vertex2);

	size_t FindWidestPathToLCA(size_t vertex, size_t LCA);

public:
	std::vector<std::vector<std::pair<size_t, size_t>>> tree;
	std::vector<size_t> parent;

	SpanningTree(size_t vertex_count);

	void Preprocess();

	size_t FindWidestPath(size_t vertex1, size_t vertex2);
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count, edges_count, request_count = 0;
	std::cin >> vertex_count >> edges_count >> request_count;

	Graph graph(vertex_count, edges_count);
	SpanningTree spanning_tree(vertex_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		size_t vertex1, vertex2, weight = 0;
		std::cin >> vertex1 >> vertex2 >> weight;
		graph.AddEdge(vertex1 - 1, vertex2 - 1, weight);
	}

	spanning_tree.tree = graph.FindMaxST();
	spanning_tree.Preprocess();

	for (size_t i = 0; i < request_count; i++)
	{
		size_t vertex1, vertex2 = 0;
		std::cin >> vertex1 >> vertex2;

		size_t answer = spanning_tree.FindWidestPath(vertex1 - 1, vertex2 - 1);
		std::cout << answer << "\n";
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

DisjointSetUnion::DisjointSetUnion(size_t set_count)
{
	parent.resize(set_count);
	size.resize(set_count);

	for (size_t i = 0; i < set_count; i++)
	{
		parent[i] = i;
		size[i] = 1;
	}
}

//----------------------------------------------------------------------------------------------------------------

size_t DisjointSetUnion::FindSet(size_t set)
{
	if (set == parent[set])
		return set;

	parent[set] = FindSet(parent[set]);

	return parent[set];
}

//----------------------------------------------------------------------------------------------------------------

void DisjointSetUnion::UnionSets(size_t set1, size_t set2)
{
	set1 = FindSet(set1);
	set2 = FindSet(set2);

	if (set1 != set2)
	{
		if (size[set1] < size[set2])
			std::swap(set1, set2);

		parent[set2] = set1;
		size[set1] += size[set2];
	}
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(size_t vertex_count, size_t edges_count)
{
	Graph::vertex_count = vertex_count;
	Graph::edges_count  = edges_count;
}

//----------------------------------------------------------------------------------------------------------------

void Graph::AddEdge(size_t vertex1, size_t vertex2, size_t weight)
{
	graph.push_back(std::make_pair(weight, std::make_pair(vertex1, vertex2)));
}

//----------------------------------------------------------------------------------------------------------------

std::vector<std::vector<std::pair<size_t, size_t>>> Graph::FindMaxST()
{
	std::sort(graph.begin(), graph.end());
	std::reverse(graph.begin(), graph.end());

	DisjointSetUnion DSU(vertex_count);

	std::vector<std::vector<std::pair<size_t, size_t>>> MaxST;
	MaxST.resize(vertex_count);

	for (size_t i = 0; i < edges_count; i++)
	{
		size_t weight  = graph[i].first;
		size_t vertex1 = graph[i].second.first;
		size_t vertex2 = graph[i].second.second;

		if (DSU.FindSet(vertex1) != DSU.FindSet(vertex2))
		{
			DSU.UnionSets(vertex1, vertex2);
			MaxST[vertex1].push_back(std::make_pair(vertex2, weight));
			MaxST[vertex2].push_back(std::make_pair(vertex1, weight));
		}
	}

	return MaxST;
}

//----------------------------------------------------------------------------------------------------------------

SpanningTree::SpanningTree(size_t vertex_count)
{
	SpanningTree::vertex_count = vertex_count;

	tin.resize(vertex_count);
	tout.resize(vertex_count);
	up.resize(vertex_count);
	parent.assign(vertex_count, 0);

	timer = 0;
	log_vertex_count = 1;
	while ((1 << log_vertex_count) <= vertex_count)
	{
		log_vertex_count++;
	}
}

//----------------------------------------------------------------------------------------------------------------

void SpanningTree::Preprocess()
{
	for (size_t i = 0; i < vertex_count; i++)
	{
		up[i].resize(log_vertex_count + 1);
	}

	DFS(0, 0, 0);
}

//----------------------------------------------------------------------------------------------------------------

size_t SpanningTree::FindWidestPath(size_t vertex1, size_t vertex2)
{
	size_t LCA = FindLCA(vertex1, vertex2);

	size_t path1 = FindWidestPathToLCA(vertex1, LCA);
	size_t path2 = FindWidestPathToLCA(vertex2, LCA);

	return std::min(path1, path2);
}

//----------------------------------------------------------------------------------------------------------------

bool SpanningTree::Upper(size_t vertex1, size_t vertex2)
{
	return ((tin[vertex1] <= tin[vertex2]) && (tout[vertex1] >= tout[vertex2]));
}

//----------------------------------------------------------------------------------------------------------------

void SpanningTree::DFS(size_t vertex, size_t vertex_from, size_t height)
{
	tin[vertex] = timer++;
	up[vertex][0] = vertex_from;

	for (size_t i = 1; i <= log_vertex_count; i++)
	{
		up[vertex][i] = up[up[vertex][i - 1]][i - 1];
	}

	for (size_t i = 0; i < tree[vertex].size(); i++)
	{
		size_t vertex_to = tree[vertex][i].first;

		if (vertex_to != vertex_from)
		{
			parent[vertex_to] = vertex;
			DFS(vertex_to, vertex, height + 1);
		}
	}

	tout[vertex] = timer++;
}

//----------------------------------------------------------------------------------------------------------------

size_t SpanningTree::FindLCA(size_t vertex1, size_t vertex2)
{
	if (Upper(vertex1, vertex2))
		return vertex1;
	if (Upper(vertex2, vertex1))
		return vertex2;

	for (size_t i = log_vertex_count + 1; i > 0; i--)
	{
		if (!Upper(up[vertex1][i - 1], vertex2))
			vertex1 = up[vertex1][i - 1];
	}

	return up[vertex1][0];
}

//----------------------------------------------------------------------------------------------------------------

size_t SpanningTree::FindWidestPathToLCA(size_t vertex, size_t LCA)
{
	size_t curr_vertex = vertex;
	size_t widest_path = UINT16_MAX;

	while (curr_vertex != LCA)
	{
		size_t parent_vertex = parent[curr_vertex];

		for (size_t i = 0; i < tree[curr_vertex].size(); i++)
		{
			if (tree[curr_vertex][i].first == parent_vertex)
			{
				if (widest_path > tree[curr_vertex][i].second)
				{
					widest_path = tree[curr_vertex][i].second;
				}
				curr_vertex = parent_vertex;
			}
		}
	}

	return widest_path;
}

//----------------------------------------------------------------------------------------------------------------