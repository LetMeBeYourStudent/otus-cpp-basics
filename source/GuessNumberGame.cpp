//
// Created by Михаил Адаменко on 24.05.2023.
//

#include "../headers/GuessNumberGame.h"
#include <iostream>
#include "../headers/binary_search.h"

namespace homework_1_guess_number {

    GuessNumberGame::GuessNumberGame(){

    }

    int GuessNumberGame::print_menu()
    {
        int choice = 0;
        
        while (choice > 4 || choice <=0)
        {
            std::cout << "Main menu:\n";
            std::cout << "1. Start simple game. Numbers from 0 to 100.\n";
            std::cout << "2. Start strange game. Numbers from random range with max number parameter.\n";
            std::cout << "3. High score table.\n";
            std::cout << "4. Exit game." << std::endl;

            std::cout << "Enter your choice: ";
            std::cin >> choice;
            if (choice > 4 || choice <=0)
            {
                std::cout << "Unavailable choice!" << std::endl;
            }
        }
        return choice;
    }

    bool GuessNumberGame::play_with_computer_menu()
    {
        std::string result;
        std::cout << "Do you want to play with computer? (enter 'y' for YES or any char for NO): ";
        std::cin >> result;
        if (result[0] == 'y')
        {
            return true;
        }
        return false;
    }

    void GuessNumberGame::choose_name()
    {
    }

    int GuessNumberGame::start_game(int left, int right)
    {
        int player_tries = 0;
        // Задаем зерно
        srand((unsigned) time(nullptr));

        // Получаем искомое значение
        int guess_number = left + rand() % (right - left);

        // Получаем настройку, играть ли с компьютером
        with_computer_ = play_with_computer_menu();

        int computer_tries = 0;

        if (with_computer_)
        {
            computer_tries = binary_search(left, right, guess_number);
            std::cout << "Ha-ha! I'm COMPUTER!\n";
            std::cout << "I found right number with " << computer_tries;
            std::cout << " tries! I'm the BEST!" << std::endl;
        }

        int player_choice;
        do {
            std::cout << "Enter number from " << left << " to " << right << ": ";
            std::cin >> player_choice;
            if (player_choice > guess_number)
            {
                std::cout << "Secret number lesser then your number." << std::endl;
                player_tries++;
            }
            else
            {
                std::cout << "Secret number grater then your number." << std::endl;
                player_tries++;
            }
        } while (player_choice != guess_number);

        std::cout << "You are right! It is " << guess_number << "!" << std::endl;
        std::cout << "You found it in " << player_tries << " tries!" << std::endl;

        if (with_computer_)
        {
            if (computer_tries >= player_tries)
            {
                std::cout << "Computer LOOSE! Congratulations!" << std::endl;
            }
            else
            {
                std::cout << "Computer WIN! Try another time!" << std::endl;
            }
        }

        return player_tries;
    }

    void GuessNumberGame::start()
    {
        std::cout << "Welcome to Guess Number Game!" << std::endl;
        
        int choice = 0;
        while (choice != 4)
        {
            choice = print_menu();
            int left = 0;
            int right = 100;

            switch (choice)
            {
            case 1:
                start_game(left, right);
                break;
            case 2:
                {
                    // Требуем максимальное значение
                    int max_number = 100;
                    std::cout << "Enter max number for strange game (>1): ";
                    std:: cin >> max_number;

                    // Если ввели что-то не потребное, пишем об этом и выходим
                    if (max_number < 1) {
                        std::cout << "Number have to be grater then 1" << std::endl;
                        break;
                    }

                    // Получаем верхний и нижний пределы
                    std::tuple<int, int> min_max_tuple = get_min_max_number(max_number);
                    left = std::get<0>(min_max_tuple);
                    right = std::get<1>(min_max_tuple);

                    // Стартуем игру
                    start_game(left, right);
                    break;
                }
            case 3:
                break;
            default:
                break;
            }
        }
    }

    std::tuple<int, int> GuessNumberGame::get_min_max_number(int max_number)
    {
        // Задаем зерно
        srand((unsigned) time(nullptr));

        // Получаем первое значение
        int left = rand() % max_number;

        // Получаем второе значение
        int right = left + rand() % (max_number - left);

        return std::tuple<int, int>{left, right};
    }
} // homework_1_guess_number