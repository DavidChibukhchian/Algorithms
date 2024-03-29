# **Практическая работа №2**

## **Описание**
В данной работе представлена реализация стека на динамическом массиве и на односвязном списке. Целью исследования является сравнение скорости работы этих двух стеков.

В ходе работы были проведены три различных теста, результаты которых можно посмотреть в файлах `Stack_array_results` и `Stack_list_results`.

## **Примечания**
В файле tests.h [в директиве define](https://github.com/DavidChibukhchian/Algorithms/blob/main/Prac2/source/tests.h#L6) необходимо указать вид стека, для которого будут выполняться тесты.
Сделано это для того, чтобы избежать копирования при написании тестов, а также чтобы не использовать разный нейминг для одних и тех же функций разных стеков.

By the way, в третьем тесте в стек изначально [кладётся](https://github.com/DavidChibukhchian/Algorithms/blob/main/Prac2/source/tests.cpp#L212) 400 тыс. элементов, т.к. при большем количестве программа зависает.

В папке [singly_linked_list](https://github.com/DavidChibukhchian/Algorithms/tree/main/Prac2/source/singly_linked_list) вы найдёте реализацию односвязного списка, которая также требуется по заданию.

Проект собирается командами `make array` и `make list`.

## **Вывод**
Стек на динамическом массиве работает в несколько раз быстрее стека на односвязном списке.

Объясняется это тем, что в случае использования односвязного списка при каждом вызове функции `push` происходит динамическое выделение памяти, тогда как в случае использования динамического массива память выделяется намного реже.