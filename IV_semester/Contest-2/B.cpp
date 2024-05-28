#include <iostream>
#include <vector>

//--------------------------------------------------------------------------------------------------------------

size_t get_sum_of_min_dividers_of_composite_numbers(size_t number);

std::vector<size_t> get_min_dividers(size_t number);

//--------------------------------------------------------------------------------------------------------------

int main()
{
	size_t N = 0;
	std::cin >> N;

	size_t sum = get_sum_of_min_dividers_of_composite_numbers(N);

	std::cout << sum << std::endl;
}

//--------------------------------------------------------------------------------------------------------------

size_t get_sum_of_min_dividers_of_composite_numbers(size_t number)
{
	std::vector<size_t> min_dividers = get_min_dividers(number);

	size_t res = 0;

	for (size_t i = 3; i <= number; i++)
	{
		if (min_dividers[i] != i)
		{
			res += min_dividers[i];
		}
	}

	return res;
}

//--------------------------------------------------------------------------------------------------------------

std::vector<size_t> get_min_dividers(size_t number)
{
	std::vector<size_t> min_dividers(number + 1, 0);
	std::vector<size_t> prime_numbers;

	for (size_t i = 2; i <= number; i++)
	{
		if (min_dividers[i] == 0)
		{
			min_dividers[i] = i;
			prime_numbers.push_back(i);
		}

		for (size_t j = 0; j < prime_numbers.size(); j++)
		{
			if ((prime_numbers[j] * i > number) || (prime_numbers[j] > min_dividers[i]))
			{
				break;
			}

			min_dividers[prime_numbers[j] * i] = prime_numbers[j];
		}
	}

	return min_dividers;
}

//--------------------------------------------------------------------------------------------------------------