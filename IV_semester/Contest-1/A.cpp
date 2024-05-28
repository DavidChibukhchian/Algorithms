#include <iostream>
#include <vector>

//-------------------------------------------------------------------------------------------------

std::vector<size_t> find_all_occurrences(const std::string& pattern, const std::string& text);

std::vector<size_t> calculate_prefix_function(const std::string& string);

//-------------------------------------------------------------------------------------------------

int main()
{
	std::string text, pattern;
	std::cin >> text >> pattern;

	std::vector<size_t> positions = find_all_occurrences(pattern, text);

	for (size_t i = 0; i < positions.size(); i++)
	{
		std::cout << positions[i] << std::endl;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------

std::vector<size_t> find_all_occurrences(const std::string& pattern, const std::string& text)
{
	std::vector<size_t> prefix_function = calculate_prefix_function(pattern);

	size_t k = 0;
	std::vector<size_t> positions;
	for (size_t i = 0; i < text.size(); i++)
	{
		while ((k > 0) && (text[i] != pattern[k]))
		{
			k = prefix_function[k - 1];
		}

		if (text[i] == pattern[k])
		{
			k++;
		}

		if (k == pattern.size())
		{
			positions.push_back(i - k + 1);
		}
	}

	return positions;
}

//-------------------------------------------------------------------------------------------------

std::vector<size_t> calculate_prefix_function(const std::string& str)
{
	size_t str_len = str.size();
	std::vector<size_t> prefix_function(str_len, 0);

	for (size_t i = 1; i < str_len; i++)
	{
		size_t k = prefix_function[i - 1];

		while ((k > 0) && (str[i] != str[k]))
		{
			k = prefix_function[k - 1];
		}

		if (str[i] == str[k])
		{
			k++;
		}

		prefix_function[i] = k;
	}

	return prefix_function;
}

//-------------------------------------------------------------------------------------------------
