#include "mancala.h"
#include <limits.h>
#include <stdio.h>

int search(MancalaGame game, int depth, int *best_move) {
  if (depth == 0 || game.turn == GAMEOVER) {
    return game.max_streak;
  }

  int pit_min = game.turn == ENGINE ? 0 : 7;
  int pit_max = game.turn == ENGINE ? 5 : 12;

  int best_score = INT_MIN;

  for (int i = pit_min; i <= pit_max; i++) {
    if (game.pits[i] == 0) continue;

    MancalaGame new_game = MancalaGame_play(game, i);

    int new_depth = new_game.turn == game.turn ? depth : depth - 1;
    int score;

    if (game.cur_streak >= 5 && new_game.cur_streak == 1) {
      // Optimization: if a long streak is ongoing don't consider moves that end it
      score = game.cur_streak;
    } else {
      score = search(new_game, new_depth, NULL);
    }

    if (score > best_score) {
      best_score = score;
      if (best_move != NULL) *best_move = i;
    }
  }

  return best_score;
}

int main() {
  MancalaGame game = MancalaGame_create(ENGINE);
  MancalaGame_print(game);

  while (game.turn != GAMEOVER) {
    int best_move;
    int eval = search(game, 8, &best_move);

    printf("Best move is %d (eval %d)\n\n", best_move, eval);

    game = MancalaGame_play(game, best_move);

    MancalaGame_print(game);
  }

  return 0;
}
