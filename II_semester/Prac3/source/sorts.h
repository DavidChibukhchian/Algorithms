#ifndef _SORTS_H
#define _SORTS_H

//--------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

//--------------------------------------------------------------------------------------------------------------

void insertion_sort (int* array, size_t size);

void bubble_sort    (int* array, size_t size);

void selection_sort (int* array, size_t size);

void quick_sort     (int* array, size_t size, int (*get_pivot)(int*, int, int));

void merge_sort     (int* array, size_t size);

void LSD_sort  (uint32_t* array, size_t size, uint32_t bit = 0x80000000);

//--------------------------------------------------------------------------------------------------------------

int pivot_Median_Of_Three (int* array, int left, int right);

int pivot_Central         (int* array, int left, int right);

int pivot_Random          (int* array, int left, int right);

//--------------------------------------------------------------------------------------------------------------

#endif // _SORTS_H