#include "tests.h"

//-------------------------------------------------------------------------------------------------------------------

static const size_t number_of_tests = 9;

//-------------------------------------------------------------------------------------------------------------------

FILE* open_file(void)
{
    FILE* results_file = nullptr;

    #ifdef STACK_ARRAY
        results_file = fopen("Stack_array_results.txt", "w");
    #endif

    #ifdef STACK_LIST
        results_file = fopen("Stack_list_results.txt", "w");
    #endif

    if (results_file == nullptr)
        return nullptr;

    return results_file;
}

//-------------------------------------------------------------------------------------------------------------------

void test_1(FILE* results_file)
{
    double time_of_iteration = 0;
    double average_time = 0;
    int elem = 0;

    srand(time(nullptr));

    fprintf(results_file, "-------------TEST-1-------------\n");
    
    for (size_t j = 1; j <= number_of_tests; j++)
    {
        #ifdef STACK_ARRAY
            Stack* stack = stack_ctr(1000000, sizeof(int));
        #endif

        #ifdef STACK_LIST
            Stack* stack = stack_ctr(sizeof(int));
        #endif

        clock_t start = clock();

        for (size_t i = 0; i < 1000000; i++)
        {
            elem = rand();
            push(stack, &elem);
        }

        size_t size = stack->size;
        srand(time(nullptr));

        while(stack->size > 100000)
        {
            for (size_t i = 0; i < (size / 2); i++)
            {
                pop(stack);
            }

            for (size_t i = 0; i < (size / 4); i++)
            {
                elem = rand();
                push(stack, &elem);
            }

            size = stack->size;
        } 
        
        clock_t end = clock();

        time_of_iteration = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(results_file, "  test %d:        %.3lf seconds\n", j, time_of_iteration);
        average_time += time_of_iteration;

        stack_dtr(stack);
    }

    average_time /= number_of_tests;

    fprintf(results_file, "--------------------------------\n");
    fprintf(results_file, "  Average time:  %.3lf seconds\n", average_time);
    fprintf(results_file, "--------------------------------\n");
}

//-------------------------------------------------------------------------------------------------------------------

void test_2(FILE* results_file)
{
    double time_of_iteration = 0;
    double average_time = 0;
    int elem = 0;

    srand(time(nullptr));

    fprintf(results_file, "\n\n-------------TEST-2-------------\n");
    
    for (size_t j = 1; j <= number_of_tests; j++)
    {
        #ifdef STACK_ARRAY
            Stack* stack = stack_ctr(1000000, sizeof(int));
        #endif

        #ifdef STACK_LIST
            Stack* stack = stack_ctr(sizeof(int));
        #endif

        clock_t start = clock();

        for (size_t i = 0; i < 1000000; i++)
        {
            elem = rand();
            push(stack, &elem);
        }

        for (size_t i = 0; i < 100; i++)
        {
            srand(time(nullptr));

            for (size_t j = 0; j < 10000; j++)
            {
                pop(stack);
            }
            for (size_t j = 0; j < 10000; j++)
            {
                elem = rand();
                push(stack, &elem);
            }
        }

        size_t size = stack->size;
        srand(time(nullptr));

        while(stack->size > 100000)
        {
            for (size_t i = 0; i < (size / 2); i++)
            {
                pop(stack);
            }

            for (size_t i = 0; i < (size / 4); i++)
            {
                elem = rand();
                push(stack, &elem);
            }

            size = stack->size;
        }

        for (size_t i = 0; i < 100; i++)
        {
            srand(time(nullptr));

            for (size_t j = 0; j < 10000; j++)
            {
                pop(stack);
            }
            for (size_t j = 0; j < 10000; j++)
            {
                elem = rand();
                push(stack, &elem);
            }
        }

        clock_t end = clock();

        time_of_iteration = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(results_file, "  test %d:        %.3lf seconds\n", j, time_of_iteration);
        average_time += time_of_iteration;

        stack_dtr(stack);
    }

    average_time /= number_of_tests;

    fprintf(results_file, "--------------------------------\n");
    fprintf(results_file, "  Average time:  %.3lf seconds\n", average_time);
    fprintf(results_file, "--------------------------------\n");
}

//-------------------------------------------------------------------------------------------------------------------

void test_3(FILE* results_file)
{
    double time_of_iteration = 0;
    double average_time = 0;
    int elem = 0;
    int instruction = 0;

    fprintf(results_file, "\n\n-------------TEST-3-------------\n");
    
    for (size_t j = 1; j <= number_of_tests; j++)
    {
        srand(time(nullptr));

        #ifdef STACK_ARRAY
            Stack* stack = stack_ctr(1000000, sizeof(int));
        #endif

        #ifdef STACK_LIST
            Stack* stack = stack_ctr(sizeof(int));
        #endif

        for (size_t i = 0; i < 400000; i++)
        {
            elem = rand();
            push(stack, &elem);
        }

        clock_t start = clock();

        for (size_t i = 0; i < 1000000; i++)
        {
            instruction = (rand() % 2) + 1;

            if (instruction == 1)
            {
                elem = rand();
                push(stack, &elem);
            }
            else
            {
                pop(stack);
            }
        }

        clock_t end = clock();

        time_of_iteration = (double)(end - start) / CLOCKS_PER_SEC;

        fprintf(results_file, "  test %d:        %.3lf seconds\n", j, time_of_iteration);
        average_time += time_of_iteration;

        stack_dtr(stack);
    }

    average_time /= number_of_tests;

    fprintf(results_file, "--------------------------------\n");
    fprintf(results_file, "  Average time:  %.3lf seconds\n", average_time);
    fprintf(results_file, "--------------------------------\n");
}

//-------------------------------------------------------------------------------------------------------------------
