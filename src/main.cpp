#include "mancala.hpp"
#include "minimax.hpp"
#include <cstddef>
#include <format>
#include <iostream>

int main()
{
    const int start_stones = 4;
    const int engine_depth = 24;

    std::cout << "Is the engine playing first (y/n)? ";

    char choice;
    std::cin >> choice;

    auto turn = (choice == 'y') ? PlayerTurn::Engine : PlayerTurn::Human;

    // Initialize board with stones in players' pits
    MancalaBoard board;
    for (int i = 0; i <= 5; i++) {
        board[i] = start_stones;
    }
    for (int i = 7; i <= 12; i++) {
        board[i] = start_stones;
    }
    board[6] = 0;
    board[13] = 0;

    while (true) {
        if (turn == PlayerTurn::Engine) {
            int engine_move;
            auto eval = minimax(board, turn, engine_depth, &engine_move);

            if (engine_move == -1) {
                // Engine had no possible moves, end game loop
                break;
            }

            std::cout << std::format("Engine plays {} (eval = {})\n", engine_move, eval);

            bool go_again = make_move(board, engine_move);
            if (!go_again) {
                turn = PlayerTurn::Human;
            }
        } else {
            print_board(board);

            std::cout << "Human move (0-5): ";
            int column;
            std::cin >> column;

            // Convert column to actual index in the array
            std::size_t pit_index = 12 - column;

            if (pit_index < 7 || pit_index > 12 || board[pit_index] == 0) {
                std::cout << "Invalid move, enter again" << std::endl;
                continue;
            }

            bool go_again = make_move(board, pit_index);
            if (!go_again) {
                turn = PlayerTurn::Engine;
            }
        }
    }

    return 0;
}
