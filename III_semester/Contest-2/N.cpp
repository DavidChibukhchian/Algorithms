#include <iostream>
#include <vector>
#include <algorithm>

//----------------------------------------------------------------------------------------------------------------

class Disjoint_Set_Union
{
	std::vector<size_t> parent, rank, set_size;

public:
	Disjoint_Set_Union(size_t set_count);

	void add_set(size_t pos, size_t size);

	size_t find_set(size_t set);

	void union_sets(size_t set1, size_t set2);

	size_t max_size;
};

//----------------------------------------------------------------------------------------------------------------

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	size_t tables_count, request_count = 0;
	std::cin >> tables_count >> request_count;

	Disjoint_Set_Union DSU(tables_count);

	for (size_t i = 0; i < tables_count; i++)
	{
		size_t table_size = 0;
		std::cin >> table_size;
		DSU.add_set(i, table_size);
	}

	for (size_t i = 0; i < request_count; i++)
	{
		size_t table1, table2 = 0;
		std::cin >> table1 >> table2;

		DSU.union_sets(table1 - 1, table2 - 1);
		std::cout << DSU.max_size << "\n";
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------

Disjoint_Set_Union::Disjoint_Set_Union(size_t set_count)
{
	set_size.reserve(set_count);
	parent.reserve(set_count);
	rank.reserve(set_count);
	max_size = 0;
}

//----------------------------------------------------------------------------------------------------------------

void Disjoint_Set_Union::add_set(size_t pos, size_t size)
{
	set_size.push_back(size);
	parent.push_back(pos);
	rank.push_back(0);

	if (size > max_size)
		max_size = size;
}

//----------------------------------------------------------------------------------------------------------------

size_t Disjoint_Set_Union::find_set(size_t set)
{
	if (set == parent[set])
		return set;

	parent[set] = find_set(parent[set]);

	return parent[set];
}

//----------------------------------------------------------------------------------------------------------------

void Disjoint_Set_Union::union_sets(size_t set1, size_t set2)
{
	set1 = find_set(set1);
	set2 = find_set(set2);

	if (set1 != set2)
	{
		if (rank[set1] < rank[set2])
			std::swap(set1, set2);

		parent[set2] = set1;

		if (rank[set1] == rank[set2])
			++rank[set1];

		set_size[set1] += set_size[set2];

		if (set_size[set1] > max_size)
			max_size = set_size[set1];
	}
}

//----------------------------------------------------------------------------------------------------------------