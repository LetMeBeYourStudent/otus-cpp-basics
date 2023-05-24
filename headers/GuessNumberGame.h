//
// Created by Михаил Адаменко on 24.05.2023.
//

#ifndef HELLO_WORLD_GUESSNUMBERGAME_H
#define HELLO_WORLD_GUESSNUMBERGAME_H

#include <tuple>
#include <string>

namespace homework_1_guess_number {

    class GuessNumberGame {
    public:
        void start();
    private:
        /// Функция получает минимальное и максимальное числа
        /// \param max_number - максимальное число (>0)
        /// \return минимальное и максимальное числа
        std::tuple<int, int> get_min_max_number(int max_number);

        /// Метод выводит меню и возвращает выбор
        /// 1 - Простая игра (от 0 до 100)
        /// 2 - Случайная игра (ввод максимального числа и случайный выбор минимального и максимального)
        /// 3 - Вывод таблицы рекордов
        /// 4 - Выход из игры
        /// \return Выбор пункта меню
        int print_menu();

        /// Меню выбора режима игры: с компьютером или нет.
        /// \return Результат выбора
        bool play_with_computer_menu();

        /// Ввод имени игрока
        void choose_name();

        /// Старт простой игры
        /// \return
        int start_simple_game();

        /// Старт странной игры
        /// \return
        int start_strange_game();

        /// Имя игрока
        std::string player_name_ = "";

        /// Играть с компьютером или нет?
        bool with_computer_ = false;
    };

} // homework_1_guess_number

#endif //HELLO_WORLD_GUESSNUMBERGAME_H
