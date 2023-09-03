#include "mancala.hpp"

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>

void print_board(const MancalaBoard& board)
{
    constexpr auto fmt = "-----------------------\n"
                         "|  {:02} {:02} {:02} {:02} {:02} {:02}  |\n"
                         "|{:02}                 {:02}|\n"
                         "|  {:02} {:02} {:02} {:02} {:02} {:02}  |\n"
                         "-----------------------\n";

    std::cout << std::format(fmt,
        board[12], board[11], board[10], board[9], board[8], board[7],
        board[13], board[6],
        board[0], board[1], board[2], board[3], board[4], board[5]);
}

bool make_move(MancalaBoard& board, std::size_t pit_index)
{
    assert((pit_index >= 0 && pit_index <= 5)
        || (pit_index >= 7 && pit_index <= 12));

    const auto turn = pit_index <= 5 ? PlayerTurn::Engine : PlayerTurn::Human;

    auto num_stones = board[pit_index];
    board[pit_index] = 0;

    // Distribute stones
    while (num_stones > 0) {
        pit_index = next_pit_index(pit_index, turn);
        ++board[pit_index];
        --num_stones;
    }

    // If the last stone landed in a store, return true because the player gets
    // to make another move
    if (pit_index == 6 || pit_index == 13) {
        return true;
    }

    // Handle stealing when the last stone lands in an empty pit and is facing
    // a non-empty pit of the other player
    if (board[pit_index] == 1) {
        const auto end_side
            = (pit_index <= 5) ? PlayerTurn::Engine : PlayerTurn::Human;
        const auto facing_index = 12 - pit_index;

        if (board[facing_index] > 0 && end_side == turn) {
            const auto store_index = (end_side == PlayerTurn::Engine) ? 6 : 13;

            board[store_index] += board[pit_index] + board[facing_index];

            board[pit_index] = 0;
            board[facing_index] = 0;
        }
    }

    return false;
}

std::size_t next_pit_index(std::size_t pit_index, PlayerTurn turn)
{
    if (pit_index == 5 && turn != PlayerTurn::Engine) {
        // Skip over engine's store
        return 7;
    }

    if (pit_index == 12 && turn != PlayerTurn::Human) {
        // Skip over human's store
        return 0;
    }

    return (pit_index + 1) % 14;
}
