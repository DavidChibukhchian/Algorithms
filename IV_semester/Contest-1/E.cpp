#include <iostream>
#include <vector>
#include <algorithm>

//-------------------------------------------------------------------------------------------------

const char SEPARATOR = '#';

//-------------------------------------------------------------------------------------------------

std::vector<std::string> find_prefix_expansion(const std::string& original_word,
                                               const std::string& invented_word);

std::vector<size_t> calculate_Z_function(const std::string& string);

//-------------------------------------------------------------------------------------------------

int main()
{
	std::string original_word, invented_word;
	std::cin >> original_word >> invented_word;

	std::vector<std::string> prefix_expansion = find_prefix_expansion(original_word, invented_word);

	if (prefix_expansion.empty())
	{
		std::cout << "Yes\n";
	}
	else
	{
		std::cout << "No\n";
		for (size_t i = 0; i < prefix_expansion.size(); i++)
		{
			std::cout << prefix_expansion[i] + ' ';
		}
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------

std::vector<std::string> find_prefix_expansion(const std::string& original_word,
                                               const std::string& invented_word)
{
	std::vector<std::string> prefix_expansion;

	const std::string double_word = original_word + SEPARATOR + invented_word;
	const std::vector<size_t> Z_function = calculate_Z_function(double_word);

	size_t i = double_word.size() - 1;
	while (double_word[i] != SEPARATOR)
	{
		size_t count = 1;
		while (Z_function[i] < count)
		{
			count++;
			i--;

			if (double_word[i] == SEPARATOR)
			{
				prefix_expansion.clear();
				return prefix_expansion;
			}
		}

		prefix_expansion.push_back(double_word.substr(i, count));
		i--;
	}

	std::reverse(prefix_expansion.begin(), prefix_expansion.end());

	return prefix_expansion;
}

//-------------------------------------------------------------------------------------------------

std::vector<size_t> calculate_Z_function(const std::string& string)
{
	const size_t str_len = string.size();

	std::vector<size_t> Z_function(str_len, 0);

	size_t l = 0;
	size_t r = 0;
	for (size_t i = 1; i < str_len; i++)
	{
		if (i <= r)
		{
			Z_function[i] = std::min(r - i + 1, Z_function[i - l]);
		}

		while ((i + Z_function[i] < str_len) && (string[Z_function[i]] == string[i + Z_function[i]]))
		{
			Z_function[i] += 1;
		}

		if (i + Z_function[i] - 1 > r)
		{
			l = i;
			r = i + Z_function[i] - 1;
		}
	}

	return Z_function;
}

//-------------------------------------------------------------------------------------------------
