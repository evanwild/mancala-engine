#include "mancala.h"
#include <limits.h>
#include <stdio.h>

int search(MancalaGame game, int depth, int *best_move) {
  if (depth == 0 || game.turn == GAMEOVER) {
    return game.max_streak;
  }

  if (depth <= 20 && game.cur_streak == 1) {
    // Optimization: Prune branches where a streak
    // hasn't started with 20 moves left
    return 0;
  }

  if (game.turn == ENGINE) {
    int best_score = INT_MIN;

    for (int i = 0; i <= 5; i++) {
      if (game.pits[i] == 0) continue;

      int score = search(MancalaGame_play(game, i), depth - 1, NULL);
      if (score > best_score) {
        best_score = score;
        if (best_move != NULL) *best_move = i;
      }
    }

    return best_score;
  }

  if (game.turn == HUMAN) {
    int best_score = INT_MIN;

    for (int i = 7; i <= 12; i++) {
      if (game.pits[i] == 0) continue;

      int score = search(MancalaGame_play(game, i), depth - 1, NULL);
      if (score > best_score) {
        best_score = score;
        if (best_move != NULL) *best_move = i;
      }
    }

    return best_score;
  }
}

int main() {
  MancalaGame game = MancalaGame_create(ENGINE);
  MancalaGame_print(game);

  while (game.turn != GAMEOVER) {
    int best_move;
    int eval = search(game, 30, &best_move);

    printf("Best move is %d (eval %d)\n\n", best_move, eval);

    game = MancalaGame_play(game, best_move);

    MancalaGame_print(game);
  }

  return 0;
}
