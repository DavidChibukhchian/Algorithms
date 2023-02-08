#include <stdio.h>
#include <malloc.h>

int main()
{
    size_t number = 0;
    size_t max_number_of_zeros = 0;
    scanf("%d %d", &number, &max_number_of_zeros);

    int* array = (int*)calloc (number,     sizeof(int)); // массив из нулей и единиц
    int* pref  = (int*)calloc (number + 1, sizeof(int)); // в i-й ячейке этого массива будет длина наименьшей преф. суммы с i нулями

    size_t pref_counter = 1;
    pref[0] = 0;  // мин. длина преф. суммы без нулей всегда равна нулю

    for (size_t i = 0; i < number; i++) // первый цикл - инициализируем массив и сразу делаем предпросчёт
    {
        scanf("%d", &(array[i]));

        if (array[i] == 0)
        {
            pref[pref_counter] = i + 1;  // на i-м элементе длина преф. суммы равна i + 1
            pref_counter++;
        }
    }

    size_t res = 0;
    size_t current_length = 0;
    size_t current_number_of_zeros = 0;
    int idx = 0;

    for (size_t i = 0; i < number; i++) // второй цикл - динамически вычисляем ответ
    {
        current_length++;

        if (array[i] == 0)
            current_number_of_zeros++;

        idx = current_number_of_zeros - max_number_of_zeros;
        if (idx < 0)
            idx = 0;

        if ((current_length - pref[idx]) > res)
            res = current_length - pref[idx];
    }

    printf("Answer: %d", res);

    free(array);
    free(pref);
    return 0;
}