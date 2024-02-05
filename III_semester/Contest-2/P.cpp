#include <iostream>
#include <vector>

//----------------------------------------------------------------------------------------------------------------

const size_t ROOT_HEIGHT = 1;

//----------------------------------------------------------------------------------------------------------------

class Tree
{
	size_t vertex_count;
	std::vector<std::vector<int>> tree;

	std::vector<size_t> vertex_height;
	std::vector<int> lca_tree, first, DFS_list;
	std::vector<bool> visited;

	void DFS(int vertex, size_t height);

	void build_tree(int i, int left, int right);

	int find_LCA(int i, int s_left, int s_right, int left, int right);

public:
	Tree(size_t v_count);

	void add_edge(int vertex1, int vertex2);

	void preprocess(int root);

	size_t find_min_time(int vertex1, int vertex2);
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count = 0;
	std::cin >> vertex_count;

	Tree tree(vertex_count);

	for (size_t i = 0; i < vertex_count - 1; i++)
	{
		int vertex1, vertex2 = 0;
		std::cin >> vertex1 >> vertex2;
		tree.add_edge(vertex1 - 1, vertex2 - 1);
	}

	tree.preprocess(0);

	size_t request_count = 0;
	std::cin >> request_count;
	for (size_t i = 0; i < request_count; i++)
	{
		int vertex1, vertex2 = 0;
		std::cin >> vertex1 >> vertex2;

		size_t answer = tree.find_min_time(vertex1 - 1, vertex2 - 1);
		std::cout << answer << "\n";
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Tree::Tree(size_t v_count)
{
	vertex_count = v_count;
	tree.resize(v_count);
}

//----------------------------------------------------------------------------------------------------------------

void Tree::add_edge(int vertex1, int vertex2)
{
	tree[vertex1].push_back(vertex2);
	tree[vertex2].push_back(vertex1);
}

//----------------------------------------------------------------------------------------------------------------

void Tree::DFS(int vertex, size_t height)
{
	visited[vertex] = true;
	vertex_height[vertex] = height;
	DFS_list.push_back(vertex);

	for (int vertex_to = 0; vertex_to < tree[vertex].size(); vertex_to++)
	{
		if (!visited[tree[vertex][vertex_to]])
		{
			DFS(tree[vertex][vertex_to], height + 1);
			DFS_list.push_back(vertex);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------

void Tree::build_tree(int i, int left, int right)
{
	if (left == right)
	{
		lca_tree[i] = DFS_list[left];
	}
	else
	{
		int middle = (left + right) / 2;
		build_tree(2 * i, left, middle);
		build_tree(2 * i + 1, middle + 1, right);

		if (vertex_height[lca_tree[2 * i]] < vertex_height[lca_tree[2 * i + 1]])
			lca_tree[i] = lca_tree[2 * i];
		else
			lca_tree[i] = lca_tree[2 * i + 1];
	}
}

//----------------------------------------------------------------------------------------------------------------

int Tree::find_LCA(int i, int s_left, int s_right, int left, int right)
{
	if ((s_left == left) && (s_right == right))
		return lca_tree[i];

	int s_middle = (s_left + s_right) / 2;

	if (right <= s_middle)
		return find_LCA(2 * i, s_left, s_middle, left, right);

	if (s_middle < left)
		return find_LCA(2 * i + 1, s_middle + 1, s_right, left, right);


	int vertex1 = find_LCA(2 * i, s_left, s_middle, left, s_middle);
	int vertex2 = find_LCA(2 * i + 1, s_middle + 1, s_right,  s_middle + 1, right);

	if (vertex_height[vertex1] < vertex_height[vertex2])
		return vertex1;
	else
		return vertex2;
}

//----------------------------------------------------------------------------------------------------------------

void Tree::preprocess(int root)
{
	vertex_height.resize(vertex_count);
	DFS_list.reserve(2 * vertex_count);
	visited.assign(vertex_count, false);

	DFS(root, ROOT_HEIGHT);

	int list_size = (int) DFS_list.size();
	lca_tree.assign(DFS_list.size() * 4 + 1, -1);
	first.assign(vertex_count, -1);

	build_tree(1, 0, list_size - 1);

	for (int i = 0; i < list_size; i++)
	{
		int vertex = DFS_list[i];
		if (first[vertex] == -1)
			first[vertex] = i;
	}
}

//----------------------------------------------------------------------------------------------------------------

size_t Tree::find_min_time(int vertex1, int vertex2)
{
	int left  = first[vertex1];
	int right = first[vertex2];

	if (left > right)
		std::swap(left, right);

	int LCA = find_LCA(1, 0, (int)(DFS_list.size()) - 1, left, right);

	return vertex_height[vertex1] + vertex_height[vertex2] - 2 * vertex_height[LCA];
}

//----------------------------------------------------------------------------------------------------------------