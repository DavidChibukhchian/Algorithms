#include <iostream>
#include <vector>

//-------------------------------------------------------------------------------------------------

const size_t SIZE_OF_ALPHABET = 26;

//-------------------------------------------------------------------------------------------------

std::string find_minimal_string(const std::vector<size_t>& prefix_function);

void case_zero(const std::vector<size_t>& prefix_function, std::string& source_string, size_t idx);

//-------------------------------------------------------------------------------------------------

int main()
{
	size_t length = 0;
	std::cin >> length;

	std::vector<size_t> prefix_function(length, 0);
	for (size_t i = 0; i < length; ++i)
	{
		size_t value = 0;
		std::cin >> value;
		prefix_function[i] = value;
	}
	
	std::string source_string = find_minimal_string(prefix_function);

	std::cout << source_string << std::endl;

	return 0;
}

//-------------------------------------------------------------------------------------------------

std::string find_minimal_string(const std::vector<size_t>& prefix_function)
{
	if (prefix_function.empty())
	{
		return "";
	}

	std::string source_string = "a";

	for (size_t i = 1; i < prefix_function.size(); ++i)
	{
		if (prefix_function[i] == 0)
		{
			case_zero(prefix_function, source_string, i);
		}
		else
		{
			source_string += source_string[prefix_function[i] - 1];
		}
	}

	return source_string;
}

//-------------------------------------------------------------------------------------------------

void case_zero(const std::vector<size_t>& prefix_function, std::string& source_string, size_t idx)
{
	std::vector<bool> used(SIZE_OF_ALPHABET, false);

	size_t k = prefix_function[idx - 1];

	while (k > 0)
	{
		used[source_string[k] - 'a'] = true;
		k = prefix_function[k - 1];
	}

	char c = 'b';
	while (used[c - 'a'])
	{
		++c;
	}

	source_string += c;
}

//-------------------------------------------------------------------------------------------------