//
// Created by Михаил Адаменко on 24.05.2023.
//

#include "../headers/binary_search.h"

/// Выдает количество попыток бинарного поиска
/// \param left - левое ограничение
/// \param right - правое ограничение
/// \param correct_number - правильное значение
/// \return Функция получает количество попыток бинарного поиска для получения результата
int binary_search(int left, int right, int correct_number)
{
    int count = 1;
    while (left <= right)
    {
        int middle = (left + right) / 2;
        // Если середина как раз то, что нужно, то выдаем результат
        if (middle == correct_number)
            return count;
        // Если середина меньше, то отбрасываем левую половину
        if (middle < correct_number) {
            left = middle + 1;
            count++;
        }
        // Если середина больше, то отбрасываем правую половину
        else {
            right = middle - 1;
            count++;
        }
    }
    // Если элемента там нет, то выдаем -1
    return -1;
}