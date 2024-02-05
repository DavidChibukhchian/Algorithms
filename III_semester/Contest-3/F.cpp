#include <iostream>
#include <vector>

//----------------------------------------------------------------------------------------------------------------

class Graph
{
private:
	size_t vertex_count;

public:
	std::vector<std::vector<bool>> matrix;

	Graph(size_t vertex_count);

	std::vector<std::vector<bool>> find_transitive_closure();
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	size_t vertex_count;
	std::cin >> vertex_count;

	Graph graph(vertex_count);

	for (size_t i = 0; i < vertex_count; i++)
	{
		for (size_t j = 0; j < vertex_count; j++)
		{
			size_t vertex;
			std::cin >> vertex;
			if (vertex != 0) graph.matrix[i][j] = true;
		}
	}

	std::vector<std::vector<bool>> transitive_closure = graph.find_transitive_closure();
	for (size_t i = 0; i < vertex_count; i++)
	{
		for (size_t j = 0; j < vertex_count; j++)
		{
			std::cout << transitive_closure[i][j] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Graph::Graph(size_t vertex_count)
{
	Graph::vertex_count = vertex_count;
	matrix.resize(vertex_count);
	for (size_t i = 0; i < vertex_count; i++)
	{
		matrix[i].resize(vertex_count, false);
	}
}

//----------------------------------------------------------------------------------------------------------------

std::vector<std::vector<bool>> Graph::find_transitive_closure()
{
	std::vector<std::vector<bool>> transitive_closure = matrix;

	for (size_t i = 0; i < vertex_count; i++)
	{
		for (size_t j = 0; j < vertex_count; j++)
		{
			for (size_t k = 0; k < vertex_count; k++)
			{
				if (transitive_closure[j][i] && transitive_closure[i][k])
				{
					transitive_closure[j][k] = true;
				}
			}
		}
	}

	return transitive_closure;
}

//----------------------------------------------------------------------------------------------------------------