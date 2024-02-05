#include "tests.h"

int main()
{
    FILE* results_file = open_file();
    if (results_file == nullptr)
        return -1;

    
    test_1(results_file);

    test_2(results_file);

    test_3(results_file);
    

    fclose(results_file);

    return 0;
}
