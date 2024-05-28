#include <iostream>
#include <cstdint>

//-------------------------------------------------------------------------------------------------

const uint64_t MOD = 1e9 + 7;

//-------------------------------------------------------------------------------------------------

uint64_t get_powered_number(uint64_t number, uint64_t power);

uint64_t get_inverse(uint64_t number);

uint64_t get_factorial(uint64_t number);

uint64_t get_Stirling_number(uint64_t number_of_elements, uint64_t number_of_subsets);

uint64_t get_weight_of_all_partitions(uint64_t number_of_elements, uint64_t number_of_subsets, uint64_t weight_of_all_elements);

//-------------------------------------------------------------------------------------------------

int main()
{
	uint64_t number_of_elements = 0;
	uint64_t number_of_subsets  = 0;
	std::cin >> number_of_elements >> number_of_subsets;

	uint64_t weight_of_all_elements = 0;
	for (uint64_t i = 0; i < number_of_elements; i++)
	{
		uint64_t weight = 0;
		std::cin >> weight;
		weight_of_all_elements += weight;
		weight_of_all_elements %= MOD;
	}

	uint64_t weight_of_all_partitions = get_weight_of_all_partitions(number_of_elements, number_of_subsets, weight_of_all_elements);
	std::cout << weight_of_all_partitions << std::endl;

	return 0;
}

//-------------------------------------------------------------------------------------------------

uint64_t get_powered_number(uint64_t number, uint64_t power)
{
	if (power == 0)
		return 1;

	if (power % 2 == 1)
		return (number % MOD) * (get_powered_number(number, power - 1) % MOD) % MOD;

	uint64_t half = get_powered_number(number, power / 2) % MOD;

	return half * half % MOD;
}

//-------------------------------------------------------------------------------------------------

uint64_t get_inverse(uint64_t number)
{
	return get_powered_number(number, MOD - 2);
}

//-------------------------------------------------------------------------------------------------

uint64_t get_factorial(uint64_t number)
{
	uint64_t factorial = 1;

	for (uint64_t k = 1; k <= number; k++)
	{
		factorial = factorial * (k % MOD) % MOD;
	}

	return factorial;
}

//-------------------------------------------------------------------------------------------------

uint64_t get_Stirling_number(uint64_t number_of_elements, uint64_t number_of_subsets)
{
	uint64_t Stirling_number = 0;
	uint64_t k_choose_j = 1;

	for (uint64_t j = 0; j <= number_of_subsets; j++)
	{
		uint64_t diff = k_choose_j * get_powered_number(number_of_subsets - j, number_of_elements) % MOD;
		if (j % 2 == 0)
		{
			Stirling_number += diff;
		}
		else
		{
			Stirling_number += MOD;
			Stirling_number -= diff;
		}
		Stirling_number %= MOD;

		k_choose_j = k_choose_j * ((number_of_subsets - j) % MOD) % MOD;
		k_choose_j = k_choose_j * get_inverse(j + 1) % MOD;
	}

	Stirling_number = Stirling_number * get_inverse(get_factorial(number_of_subsets)) % MOD;

	return Stirling_number;
}

//-------------------------------------------------------------------------------------------------

uint64_t get_weight_of_all_partitions(uint64_t number_of_elements, uint64_t number_of_subsets, uint64_t weight_of_all_elements)
{
	uint64_t Stirling_part = 0;
	Stirling_part  = get_Stirling_number(number_of_elements,     number_of_subsets);
	Stirling_part += get_Stirling_number(number_of_elements - 1, number_of_subsets) * ((number_of_elements - 1) % MOD) % MOD;

	return weight_of_all_elements * Stirling_part % MOD;
}

//-------------------------------------------------------------------------------------------------
