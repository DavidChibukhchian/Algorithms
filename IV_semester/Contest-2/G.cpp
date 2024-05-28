#include <iostream>
#include <vector>
#include <cstdint>

//-------------------------------------------------------------------------------------------------

const uint64_t MOD = 1e9 + 7;

//-------------------------------------------------------------------------------------------------

uint64_t get_sum_of_xor_of_all_pairs(const std::vector<uint64_t>& elements, size_t number_of_elements);

//-------------------------------------------------------------------------------------------------

int main()
{
	size_t number_of_elements = 0;
	std::cin >> number_of_elements;

	std::vector<uint64_t> elements(number_of_elements, 0);
	for (size_t i = 0; i < number_of_elements; i++)
	{
		uint64_t temp = 0;
		std::cin >> temp;
		elements[i] = temp;
	}

	uint64_t sum_of_xor_of_all_pairs = get_sum_of_xor_of_all_pairs(elements, number_of_elements);

	std::cout << sum_of_xor_of_all_pairs << std::endl;

	return 0;
}

//-------------------------------------------------------------------------------------------------

uint64_t get_sum_of_xor_of_all_pairs(const std::vector<uint64_t>& elements, size_t number_of_elements)
{
	uint64_t sum = 0;

	for (uint64_t bit = 0; bit < 32; bit++)
	{
		uint64_t   ones = 0;
		uint64_t zeroes = 0;
		uint64_t pos = 1 << bit;

		for (size_t i = 0; i < number_of_elements; i++)
		{
			if ((elements[i] & pos) == 0)
				zeroes++;
			else
				ones++;
		}

		uint64_t all_combinations = ((ones % MOD) * (zeroes % MOD)) % MOD;

		sum += (all_combinations * (pos % MOD)) % MOD;
		sum %= MOD;
	}

	return sum;
}

//-------------------------------------------------------------------------------------------------
