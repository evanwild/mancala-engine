#include "minimax.hpp"
#include <algorithm>
#include <array>
#include <cstddef>

int minimax(
    const MancalaBoard& board,
    PlayerTurn turn,
    int depth,
    int* move_out,
    int alpha,
    int beta)
{
    if (depth == 0) {
        // Done recursing, eval is the difference between the players' stores
        return board[6] - board[13];
    }

    auto best_eval
        = turn == PlayerTurn::Engine ? VERY_LOW_EVAL : VERY_HIGH_EVAL;
    auto best_move = -1;
    auto moves = move_order(board, turn);

    if (turn == PlayerTurn::Engine) {
        for (auto i : moves) {
            if (board[i] == 0) {
                continue;
            }

            auto board_copy = board;
            const bool go_again = make_move(board_copy, i);

            const auto next_turn = go_again ? PlayerTurn::Engine : PlayerTurn::Human;
            auto tmp_eval = minimax(board_copy, next_turn, depth - 1, nullptr, alpha, beta);

            if (tmp_eval > best_eval) {
                best_eval = tmp_eval;
                best_move = i;
            }

            alpha = std::max(alpha, tmp_eval);
            if (beta <= alpha) {
                break;
            }
        }
    } else {
        for (auto i : moves) {
            if (board[i] == 0) {
                continue;
            }

            auto board_copy = board;
            const bool go_again = make_move(board_copy, i);

            const auto next_turn = go_again ? PlayerTurn::Human : PlayerTurn::Engine;
            auto tmp_eval = minimax(board_copy, next_turn, depth - 1, nullptr, alpha, beta);

            if (tmp_eval < best_eval) {
                best_eval = tmp_eval;
                best_move = i;
            }

            beta = std::min(beta, tmp_eval);
            if (beta <= alpha) {
                break;
            }
        }
    }

    if (move_out != nullptr) {
        *move_out = best_move;
    }

    // If there were no possible moves, add remaining seeds to store and
    // end the game immediately (returning the evaluation)
    if (best_move == -1) {
        int eval = board[6] - board[13];

        if (turn == PlayerTurn::Engine) {
            for (int i = 7; i <= 12; i++) {
                eval -= board[i];
            }
        } else {
            for (int i = 0; i <= 5; i++) {
                eval -= board[i];
            }
        }
        return eval;
    }

    return best_eval;
}

std::array<std::size_t, 6> move_order(const MancalaBoard& board, PlayerTurn turn)
{
    std::array<std::size_t, 6> moves;
    std::size_t ptr = 0;

    auto hi_index = (turn == PlayerTurn::Engine) ? 5 : 12;
    auto lo_index = (turn == PlayerTurn::Engine) ? 0 : 7;

    auto store_index = (turn == PlayerTurn::Engine) ? 6 : 13;

    // First, push back moves that would let us go again
    for (auto i = hi_index; i >= lo_index; i--) {
        if (i + board[i] == store_index) {
            moves[ptr] = i;
            ptr++;
        }
    }

    // Now push back the rest of the moves
    for (auto i = hi_index; i >= lo_index; i--) {
        if (i + board[i] != store_index) {
            moves[ptr] = i;
            ptr++;
        }
    }

    return moves;
}
