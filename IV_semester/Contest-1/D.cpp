#include <iostream>
#include <vector>

//-------------------------------------------------------------------------------------------------

const char SEPARATOR = '#';

//-------------------------------------------------------------------------------------------------

size_t find_max_common_part_len(const std::string& word1, const std::string& word2);

std::vector<size_t> calculate_prefix_function(const std::string& str);

//-------------------------------------------------------------------------------------------------

int main()
{
	size_t number_of_words = 0;
	std::cin >> number_of_words;

	std::string result;
	std::cin >> result;
	for (size_t i = 1; i < number_of_words; i++)
	{
		std::string word;
		std::cin >> word;

		size_t max_common_part_len = find_max_common_part_len(result, word);

		result += word.substr(max_common_part_len);
	}

	std::cout << result;

	return 0;
}

//-------------------------------------------------------------------------------------------------

size_t find_max_common_part_len(const std::string& word1, const std::string& word2)
{
	std::string temp;
	if (word1.size() > word2.size())
	{
		temp = word2 + SEPARATOR + word1.substr(word1.size() - word2.size());
	}
	else
	{
		temp = word2 + SEPARATOR + word1;
	}

	std::vector<size_t> prefix_function = calculate_prefix_function(temp);

	return prefix_function[temp.size() - 1];
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
			++k;
		}

		prefix_function[i] = k;
	}

	return prefix_function;
}

//-------------------------------------------------------------------------------------------------
