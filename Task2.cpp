#include <stdio.h>
#include <malloc.h>

int main()
{
    size_t number = 0;
    scanf("%d", &number);

    int* array = (int*)calloc (number, sizeof(int));
    for (size_t i = 0; i < number; i++)
        scanf("%d", &(array[i]));

    int right_sum = (number*(number + 1)) / 2;
    int real_sum = 0;

    for (size_t i = 0; i < number; i++)
        real_sum += array[i];

    printf("Answer: %d", right_sum - real_sum);

    free(array);
    return 0;
}