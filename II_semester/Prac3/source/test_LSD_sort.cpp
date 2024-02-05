#include "sorts.h"

//--------------------------------------------------------------------------------------------------------------

const size_t number_of_tests = 5;

const size_t start = 100000;
const size_t end   = 10000000;
const size_t step  = 100000;

//--------------------------------------------------------------------------------------------------------------

int main()
{
	FILE* results_file = fopen("results/LSD_sort.txt", "w");

	uint32_t* array = nullptr;
	
	double start_time   = 0;
	double end_time     = 0;
	double average_time = 0;

	for (size_t size = start; size <= end; size += step)
	{
		array = (uint32_t*)calloc (size, sizeof(uint32_t));

		for (size_t i = 0; i < number_of_tests; i++)
		{
			for (size_t j = 0; j < size; j++)
				array[j] = rand();

			start_time = (double) clock () / CLOCKS_PER_SEC;
			LSD_sort(array, size);
			end_time   = (double) clock () / CLOCKS_PER_SEC;
			average_time += end_time - start_time;
		}

		fprintf(results_file, "%zu %lf\n", size, average_time / number_of_tests);

		fflush(results_file);

		free(array);
	}

	return 0;
}