#include <iostream>
#include <vector>

//-------------------------------------------------------------------------------------------------

const size_t SIZE_OF_ALPHABET = 26;

//-------------------------------------------------------------------------------------------------

std::vector<size_t> Z_function_to_prefix_function(const std::vector<size_t>& Z_function);

std::string find_minimal_string(const std::vector<size_t>& prefix_function);

void case_zero(const std::vector<size_t>& prefix_function, std::string& source_string, size_t idx);

//-------------------------------------------------------------------------------------------------

int main()
{
	size_t length = 0;
	std::cin >> length;

	std::vector<size_t> Z_function(length, 0);
	for (size_t i = 0; i < length; ++i)
	{
		size_t value = 0;
		std::cin >> value;
		Z_function[i] = value;
	}

	std::vector<size_t> prefix_function = Z_function_to_prefix_function(Z_function);

	std::string source_string = find_minimal_string(prefix_function);

	std::cout << source_string << std::endl;

	return 0;
}

//-------------------------------------------------------------------------------------------------

std::vector<size_t> Z_function_to_prefix_function(const std::vector<size_t>& Z_function)
{
	std::vector<size_t> prefix_function(Z_function.size(), 0);

	for(size_t i = 1; i < Z_function.size(); ++i)
	{
		if (Z_function[i])
		{
			for (size_t j = Z_function[i]; (j > 0) && (!(prefix_function[i + j - 1])); --j)
			{
				prefix_function[i + j - 1] = j;
			}
		}
	}

	return prefix_function;
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