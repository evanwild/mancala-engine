#include "mancala.hpp"
#include <cstdio>

int search(const MancalaGame &game, int *best_move) {
  if (game.turn == GAMEOVER) {
    return 0;
  }

  int pit_min = game.turn == PLAYER1 ? 0 : 7;
  int pit_max = game.turn == PLAYER1 ? 5 : 12;

  int best_score = -1;

  for (int i = pit_min; i <= pit_max; i++) {
    if (game.pits[i] == 0) continue;

    MancalaGame new_game{game};
    new_game.play(i);

    int score = 1 + search(new_game, nullptr);

    if (score > best_score) {
      best_score = score;
      if (best_move != nullptr) *best_move = i;
    }
  }

  return best_score;
}

int main() {
  MancalaGame game{PLAYER1};
  game.print();

  int move_count = 0;

  while (game.turn != GAMEOVER) {
    int best_move;
    int eval = search(game, &best_move);

    printf("Best move is %d (eval %d)\n\n", best_move, eval);

    game.play(best_move);
    game.print();

    ++move_count;
  }

  printf("===========================\n");
  printf("Total moves: %d\n", move_count);

  return 0;
}
