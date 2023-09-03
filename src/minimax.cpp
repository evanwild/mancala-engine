#include "minimax.hpp"
#include <algorithm>

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

    if (turn == PlayerTurn::Engine) {
        for (int i = 5; i >= 0; i--) {
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
        for (int i = 12; i >= 7; i--) {
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
