//
// Created by Михаил Адаменко on 24.05.2023.
//

#include "../headers/GuessNumberGame.h"
#include "../headers/binary_search.h"
#include <fstream>
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
            std::cout << "2. Start strange game. Numbers from random range with max number parameter.\n";
            std::cout << "3. High score table.\n";
            std::cout << "4. Exit game." << std::endl;

            std::cout << "Please, enter your choice, " << player_name_ << ": ";
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

        add_new_high_score(player_tries);

        return player_tries;
    }

    bool GuessNumberGame::load_high_score_table_from_file()
    {
        std::ifstream score_file{"high_score_table.data"};
        
        // Если не открыт, то выводим ошибку и выходим
        if (!score_file.is_open())
        {
            std::cout << "No high score table file found!" << std::endl;
            return false;
        }

        // Передаем начальные значения
        int line_number = 1;
        std::string player_name = "";
        int player_score = 0;
        
        // Читаем файл
        while (score_file)
        {
            // Получаем имя игрока, которое записано на нечетных строках
            if (line_number % 2 == 1)
            {
                // Игнорируем следующий символ, если это не первая строка
                //  иначе не переводит строку
                if (line_number != 1)
                    score_file.ignore();
                
                // Получаем имя игрока
                std::getline(score_file, player_name);
                
                // Если имя игрока пустое, то выходим
                if (player_name == "")
                    break;
            }
            // Получаем счет игрока на четных строках
            else
            {
                // Получаем
                score_file >> player_score;
                // Если такого игрока еще нет, или его счет в переменной больше, чем полученный,
                //  то заносим новое значение
                if (score_table_.count(player_name) == 0 ||
                    (score_table_.count(player_name) == 1 && score_table_[player_name] > player_score))
                {
                    score_table_[player_name] = player_score;
                }
            }

            // Читаем следующую строку
            line_number++;
        }

        return true;
    }

    void GuessNumberGame::add_new_high_score(int player_score)
    {
        if (score_table_.count(player_name_) == 0 ||
            (score_table_.count(player_name_) == 1 && score_table_[player_name_] > player_score))
        {
            score_table_[player_name_] = player_score;
            refresh_high_score_table_file();
        }
    }

    void GuessNumberGame::refresh_high_score_table_file()
    {
        std::ofstream score_file{"high_score_table.data"};

        // Если не открыт, то выводим ошибку и выходим
        if (!score_file.is_open())
        {
            std::cout << "Can't open high score table!" << std::endl;
            return ;
        }

        for (auto const&[player_name, player_score] : score_table_)
        {
            score_file << player_name << "\n";
            score_file << player_score << "\n";
        }
    }

    void GuessNumberGame::print_high_score_table()
    {
        if (score_table_.size() == 0)
        {
            std::cout << "No high scores! Be first!" << std::endl;
            return;
        }

        for (auto const&[player_name, player_score] : score_table_)
        {
            std::cout << player_name << " - ";
            std::cout << player_score << std::endl;
        }
    }

    void GuessNumberGame::start()
    {
        std::cout << "Welcome to Guess Number Game!" << std::endl;
        
        std::cout << "Before start please, enter your name: ";
        std::getline(std::cin, player_name_);

        load_high_score_table_from_file();

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
                print_high_score_table();
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