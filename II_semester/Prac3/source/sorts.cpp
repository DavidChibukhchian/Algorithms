#include "sorts.h"

//--------------------------------------------------------------------------------------------------------------

static void swap(int* elem_1, int* elem_2)
{
	int buf = *elem_1;
	*elem_1 = *elem_2;
	*elem_2 = buf;
}

//--------------------------------------------------------------------------------------------------------------

int pivot_Median_Of_Three(int* array, int left, int right)
{
	int pivot = array[(left + right) / 2];
	
	if (pivot >= array[left])
	{
		if (array[left] >= array[right])
			pivot = array[left];

		else if (array[right] < pivot)
			pivot = array[right];
	}
	else
	{
		if (array[left] <= array[right])
			pivot = array[left];
		
		else if (array[right] > pivot)
			pivot = array[right];
	}

	return pivot;
}

//--------------------------------------------------------------------------------------------------------------

int pivot_Central(int* array, int left, int right)
{
	return array[(left + right) / 2];
}

//--------------------------------------------------------------------------------------------------------------

int pivot_Random(int* array, int left, int right)
{
	srand(time(nullptr));

	int random_idx = left + rand() % (right - left + 1);

	return array[random_idx];
}

//--------------------------------------------------------------------------------------------------------------

void insertion_sort(int* array, size_t size)
{
	for (size_t i = 1; i < size; i++)
	{
		for(size_t j = i; (j >=  1) && (array[j] < array[j-1]); j--)
		{
			swap(&array[j], &array[j-1]);
		}
	}
}

//--------------------------------------------------------------------------------------------------------------

void bubble_sort(int* array, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - i - 1; j++)
		{
			if (array[j] > array[j+1])
			{
				swap(&array[j], &array[j+1]);
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------

void selection_sort(int* array, size_t size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		size_t min_idx = i;

		for (size_t j = i + 1; j < size; j++)
		{
			if (array[j] < array[min_idx])
				min_idx = j;
		}

		swap(&array[min_idx], &array[i]);
	}
}

//--------------------------------------------------------------------------------------------------------------

void quick_sort(int* array, size_t size, int (*get_pivot)(int*, int, int))
{
	int left  = 0;
	int right = size - 1;

	size_t pivot = get_pivot(array, left, right);

	while (left <= right)
	{
		while (array[left] < pivot)
			left++;

		while (array[right] > pivot)
			right--;

		if (left <= right)
		{
			swap(&array[left], &array[right]);
			left++;
			right--;
		}
	}

	if (right > 0)
		quick_sort(array, right + 1, get_pivot);

	if (left < size)
		quick_sort(&array[left], size - left, get_pivot);
}

//--------------------------------------------------------------------------------------------------------------

void merge(int* array, int p, int q, int r)
{
	int n1 = q - p + 1;

	int* L = (int*)calloc (n1, sizeof(int));
	if (L == nullptr) return;

	for (int i = 0; i < n1; i++)
		L[i] = array[p + i];


	int n2 = r - q;

	int* M = (int*)calloc (n2, sizeof(int));
	if (M == nullptr) return;

	for (int j = 0; j < n2; j++)
		M[j] = array[q + 1 + j];


	int i = 0;
	int j = 0;
	int k = p;

	while (i < n1 && j < n2)
	{
		if (L[i] <= M[j])
		{
			array[k] = L[i];
			i++;
		}
		else
		{
			array[k] = M[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		array[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		array[k] = M[j];
		j++;
		k++;
	}

	free(L);
	free(M);
}

//--------------------------------------------------------------------------------------------------------------

void merge_sort_(int* array, int left, int right)
{
	if (left >= right)
		return;
	
	int mid = (left + right - 1) / 2;

	merge_sort_(array, left, mid);
	merge_sort_(array, mid + 1, right);

	merge(array, left, mid, right);
}

//--------------------------------------------------------------------------------------------------------------

void merge_sort(int* array, size_t size)
{
	merge_sort_(array, 0, size - 1);
}

//--------------------------------------------------------------------------------------------------------------

void LSD_sort(uint32_t* array, size_t size, uint32_t bit)
{
	if (!bit)
		return;

	if (size < 2)
		return;

	size_t last  = 0;
	uint32_t buf = 0;

	for (size_t i = 0; i < size; i++)
	{
		if ((array[i] & bit) == 0)
		{
			buf = array[i];
			array[i] = array[last];
			array[last] = buf;

			last++;
		}
	}

	LSD_sort(array,        last,        bit >> 1);
	LSD_sort(array + last, size - last, bit >> 1);
}

//--------------------------------------------------------------------------------------------------------------