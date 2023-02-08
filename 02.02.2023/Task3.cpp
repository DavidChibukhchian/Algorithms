#include <stdio.h>

int main()
{
    size_t square = 0;
    scanf("%d", &square);

    size_t left  = 1;
    size_t right = square;
    size_t middle = 0;

    while (left <= right)
    {
        middle = (left + right) / 2;

        if (middle * middle < square)
        {
            if (left == middle)
            {
                printf("Answer: %d", middle);
                return 0;
            }
            left = middle;
        }
        else if (middle * middle > square)
        {
            right = middle;
        }
        else
        {
            printf("Answer: %d", middle);
            return 0;
        }
    }

    printf("Error\n");
    return -1;
}