#include "../headers/functions.h"
#include <iostream>

std::string print_hello_worlds()
{
    std::string your_name;
    std::cout << "Введите свое имя: ";
    std::cin >> your_name;
    return "Добро пожаловать в прекрасный мир С++, " + your_name;
}