#include "mancala.hpp"
#include <cstdio>

const int GOAL = 325;

int search(const MancalaGame &game, int *best_move) {
  if (game.turn == GAMEOVER) {
    return game.move_count;
  }

  int pit_min = game.turn == PLAYER1 ? 0 : 7;
  int pit_max = game.turn == PLAYER1 ? 5 : 12;

  int best_score = -1;

  for (int i = pit_min; i <= pit_max; i++) {
    if (game.pits[i] == 0) continue;

    MancalaGame new_game{game};
    new_game.play(i);

    int seeds_left = 48 - new_game.pits[6] - new_game.pits[13];
    int upperbound = new_game.move_count + 7*seeds_left;

    int score;
   
    if (upperbound < GOAL) {
      score = new_game.move_count;
    } else {
      score = search(new_game, nullptr);
    }

    if (score > best_score) {
      best_score = score;
      if (best_move != nullptr) *best_move = i;
    }

    if (score >= GOAL) {
      break;
    }
  }

  return best_score;
}

int main() {
  MancalaGame game{PLAYER1};
  game.print();

  while (game.turn != GAMEOVER) {
    int best_move;
    int eval = search(game, &best_move);

    printf("Best move is %d (eval %d)\n\n", best_move, eval);

    game.play(best_move);
    game.print();
  }

  return 0;
}
