#include <stdio.h>
#include <malloc.h>

int main()
{
    size_t number = 0;
    scanf("%d", &number);

    int* array = (int*)calloc (number, sizeof(int));
    for (size_t i = 0; i < number; i++)
        scanf("%d", &(array[i]));

    for (size_t i = 0; i < number; i++)
    {
        if (array[i] == 0)
        {
            for (size_t j = i; j < number; j++)
            {
                if (array[j] != 0)
                {
                    array[i] = array[j];
                    array[j] = 0;
                    break;
                }
            }
        }
    }

    printf("Answer: ");
    for (size_t i = 0; i < number; i++)
        printf("%d ", array[i]);

    free(array);
    return 0;
}