#include <iostream>
#include <vector>

//-------------------------------------------------------------------------------------------------

int find_number_of_palindromes(const std::string& str, bool is_odd);

//-------------------------------------------------------------------------------------------------

int main()
{
	std::string str;
	std::cin >> str;

	int  number_of_odd_palindromes = find_number_of_palindromes(str, true);
	int number_of_even_palindromes = find_number_of_palindromes(str, false);

	std::cout << number_of_odd_palindromes + number_of_even_palindromes << std::endl;

	return 0;
}

//-------------------------------------------------------------------------------------------------

int find_number_of_palindromes(const std::string& str, bool is_odd)
{
	int str_len = str.size();
	std::vector<int> d(str_len);

	int  left = 0;
	int right = -1;
	for (int i = 0; i < str_len; i++)
	{
		int k = 0;
		if (is_odd) k = 1;

		if (i <= right)
		{
			if (is_odd)
				k = std::min(d[left + right - i],     right - i + 1);
			else
				k = std::min(d[left + right - i + 1], right - i + 1);
		}

		if (is_odd)
		{
			while ((i + k < str_len) && (str[i + k] == str[i - k]) && (i - k >= 0))
			{
				k++;
			}
		}
		else
		{
			while ((i + k < str_len) && (str[i + k] == str[i - k - 1]) && (i - k - 1 >= 0))
			{
				k++;
			}
		}

		d[i] = k;
		if (i + k - 1 > right)
		{
			left  = i - k;
			if (is_odd) left += 1;
			right = i + k - 1;
		}
	}

	int number_of_palindromes = 0;
	for (size_t i = 0; i < d.size(); i++)
	{
		if (is_odd && (d[i] > 0)) d[i] -= 1;
		number_of_palindromes += d[i];
	}

	return number_of_palindromes;
}

//-------------------------------------------------------------------------------------------------
