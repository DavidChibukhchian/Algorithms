#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

//-------------------------------------------------------------------------------------------------

typedef uint32_t elem_t;

//-------------------------------------------------------------------------------------------------

uint32_t get_min_number_of_operations(const std::vector<elem_t>& elements, uint32_t number_of_elements,
                                                                           uint32_t number_of_ones);

//-------------------------------------------------------------------------------------------------

int main()
{
	uint32_t number_of_elements = 0;
	std::cin >> number_of_elements;

	uint32_t number_of_ones = 0;
	std::vector<elem_t> elements(number_of_elements, 0);
	for (uint32_t i = 0; i < number_of_elements; i++)
	{
		elem_t temp = 0;
		std::cin >> temp;
		if (temp == 1) number_of_ones++;
		elements[i] = temp;
	}

	uint32_t answer = get_min_number_of_operations(elements, number_of_elements, number_of_ones);
	if (answer == UINT32_MAX)
	{
		std::cout << -1 << '\n';
	}
	else
	{
		std::cout << answer << '\n';
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------

uint32_t get_min_number_of_operations(const std::vector<elem_t>& elements, uint32_t number_of_elements,
                                                                           uint32_t number_of_ones)
{
	if (number_of_ones > 0)
	{
		return number_of_elements - number_of_ones;
	}

	uint32_t min_number_of_operations = UINT32_MAX;
	for (uint32_t i = 0; i < number_of_elements; i++)
	{
		elem_t gcd_of_segment = elements[i];
		for (uint32_t j = i + 1; j < number_of_elements; j++)
		{
			gcd_of_segment = std::__gcd(gcd_of_segment, elements[j]);

			if (gcd_of_segment == 1)
			{
				min_number_of_operations = std::min(min_number_of_operations,
				                                    j - i + number_of_elements - 1);
				break;
			}
		}
	}

	return min_number_of_operations;
}

//-------------------------------------------------------------------------------------------------
