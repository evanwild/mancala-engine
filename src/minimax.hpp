#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include "mancala.hpp"

const int VERY_LOW_EVAL = -999;
const int VERY_HIGH_EVAL = 999;

/**
 * @brief Uses the minimax algorithm to evaluate a Mancala board position and find the best move.
 *
 * This function applies the minimax algorithm to analyze the current Mancala board position
 * and determine the best move for the given player. It recursively explores the game tree
 * to a specified depth to evaluate the potential outcomes.
 *
 * @param[in] board The current Mancala board configuration.
 * @param[in] turn The player's turn (PlayerTurn::Engine or PlayerTurn::Human).
 * @param[in] depth The depth of the search tree to explore.
 * @param[out] move_out If not nullptr, this parameter will be set to the best found move.
 * @param[in] alpha The alpha value for alpha-beta pruning optimization.
 * @param[in] beta The beta value for alpha-beta pruning optimization.
 *
 * @return An integer representing the evaluation of the board position:
 *         - A positive value indicates the engine is winning.
 *         - A negative value indicates the human player is winning.
 *         - Zero represents a balanced position.
 */
int minimax(
    const MancalaBoard& board,
    PlayerTurn turn,
    int depth,
    int* move_out,
    int alpha = VERY_LOW_EVAL,
    int beta = VERY_HIGH_EVAL);

#endif
