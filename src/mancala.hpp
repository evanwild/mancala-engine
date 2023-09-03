#ifndef MANCALA_HPP
#define MANCALA_HPP

#include <array>
#include <cstddef>
#include <cstdint>

/**
 * @brief Represents a mancala board.
 *
 * The `MancalaBoard` type models the state of a Mancala board used in a
 * two-player game. It is implemented as a fixed-size array of 14 elements, with
 * each element representing one of the 14 pits on the Mancala board.
 *
 * The board is divided into two sides, one for each player:
 *
 * - The first 6 elements (indices 0-5) represent the pits on the engine's side
 * of the board, with the 7th element (index 6) being the engine's store.
 * - The next 6 elements (indices 7-12) represent the pits for the human player,
 * with the 14th element (index 13) being their store.
 *
 * Visual representation of the board (with indices labeled):
 *
 *         <- Player
 *
 *  -----------------------
 *  |  12 11 10 09 08 07  |
 *  |13                 06|
 *  |  00 01 02 03 04 05  |
 *  -----------------------
 *
 *         Engine ->
 *
 * Each element in the array holds the number of stones currently in that pit
 * or store.
 */
using MancalaBoard = std::array<std::uint8_t, 14>;

/**
 * @brief Enum representing the current player's turn in a Mancala game.
 */
enum class PlayerTurn {
    Engine, ///< Represents the engine's turn.
    Human ///< Represents the human player's turn.
};

/**
 * @brief Print a Mancala board in a user-friendly format.
 *
 * This function takes a Mancala board and outputs it in a format that is easy
 * for humans to read and understand.
 *
 * @param[in] board The Mancala board to be printed.
 */
void print_board(const MancalaBoard& board);

/**
 * @brief Make a move on a Mancala board, updating it in place.
 *
 * This function simulates a player's move on the Mancala board by clearing a
 * pit indicated by the given `pit_index` and redistributing its stones to
 * adjacent pits. The function modifies the `board` to reflect the updated state
 * of the game.
 *
 * @param[in,out] board The Mancala board to apply the move to.
 * @param[in] pit_index The index of the pit to make a move from.
 *                      For the engine, `pit_index` should be in the range 0-5.
 *                      For the human player, `pit_index` should be in the range 7-12.
 *
 * @return `true` if the player gets an extra turn after this move, and `false`
 *         otherwise.
 */
bool make_move(MancalaBoard& board, std::size_t pit_index);

/**
 * @brief Compute the index of the next pit based on the current pit index and player's turn.
 *
 * This function calculates the index of the next pit on the Mancala board, considering
 * the current pit index and the player's turn. It handles the logic of skipping the
 * opponent's store and wrapping around to the player's pits when necessary.
 *
 * @param[in] pit_index The index of the current pit.
 * @param[in] turn The player's turn (PlayerTurn::Engine for the engine, PlayerTurn::Human for the human player).
 *
 * @return The index of the next pit based on the game rules.
 */
std::size_t next_pit_index(std::size_t pit_index, PlayerTurn turn);

#endif
