//
// Created by Михаил Адаменко on 24.05.2023.
//

#include "../headers/GuessNumberGame.h"
#include <iostream>

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
            std::cout << "2. Start simple game. Numbers from random range with max number parameter.\n";
            std::cout << "3. High score table.\n";
            std::cout << "4. Exit game." << std::endl;

            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cout << std::endl;
            if (choice > 4 || choice <=0)
            {
                std::cout << "Unaviable choice!" << std::endl;
            }
        }
        return choice;
    }

    bool GuessNumberGame::play_with_computer_menu()
    {
        return false;
    }

    void GuessNumberGame::choose_name()
    {
    }

    int GuessNumberGame::start_game(int left, int right)
    {
        return 0;
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
                    int max_number = 0;
                    std::cout << "Enter max number for strange game: ";
                    std:: cin >> max_number;
                    std::cout << std::endl;
                    std::tuple<int, int> min_max_tuple = get_min_max_number(max_number);
                    left = std::get<0>(min_max_tuple);
                    right = std::get<1>(min_max_tuple);
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
        return std::tuple<int, int>();
    }
} // homework_1_guess_number