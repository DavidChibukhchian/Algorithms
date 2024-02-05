#include "sorts.h"

//--------------------------------------------------------------------------------------------------------------

const size_t number_of_tests = 5;

const char* filename1 = "results/insertion_sort.txt";
const char* filename2 = "results/bubble_sort.txt";
const char* filename3 = "results/selection_sort.txt";

void sort_function1(int* array, size_t size)
{ insertion_sort(array, size); }

void sort_function2(int* array, size_t size)
{ bubble_sort(array, size); }

void sort_function3(int* array, size_t size)
{ selection_sort(array, size); }

const size_t start = 1000;
const size_t end   = 50000;
const size_t step  = 500;

//--------------------------------------------------------------------------------------------------------------

int main()
{
	FILE* results_file1 = fopen(filename1, "w");
	FILE* results_file2 = fopen(filename2, "w");
	FILE* results_file3 = fopen(filename3, "w");

	int* array1 = nullptr;
	int* array2 = nullptr;
	int* array3 = nullptr;
	
	double start_time   = 0;
	double end_time     = 0;

	double average_time1 = 0;
	double average_time2 = 0;
	double average_time3 = 0;

	for (size_t size = start; size <= end; size += step)
	{
		array1 = (int*)calloc (size, sizeof(int));
		array2 = (int*)calloc (size, sizeof(int));
		array3 = (int*)calloc (size, sizeof(int));

		for (size_t i = 0; i < number_of_tests; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				array1[j] = rand();
				array2[j] = array1[j];
				array3[j] = array1[j];
			}

			start_time = (double) clock () / CLOCKS_PER_SEC;
			sort_function1(array1, size);
			end_time   = (double) clock () / CLOCKS_PER_SEC;
			average_time1 += end_time - start_time;

			start_time = (double) clock () / CLOCKS_PER_SEC;
			sort_function2(array2, size);
			end_time   = (double) clock () / CLOCKS_PER_SEC;
			average_time2 += end_time - start_time;

			start_time = (double) clock () / CLOCKS_PER_SEC;
			sort_function3(array3, size);
			end_time   = (double) clock () / CLOCKS_PER_SEC;
			average_time3 += end_time - start_time;
		}

		fprintf(results_file1, "%zu %lf\n", size, average_time1 / number_of_tests);
		fprintf(results_file2, "%zu %lf\n", size, average_time2 / number_of_tests);
		fprintf(results_file3, "%zu %lf\n", size, average_time3 / number_of_tests);

		fflush(results_file1);
		fflush(results_file2);
		fflush(results_file3);

		free(array1);
		free(array2);
		free(array3);
	}

	return 0;
}