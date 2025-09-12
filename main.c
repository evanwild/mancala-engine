#include "mancala.h"
#include <stdio.h>

int search(MancalaGame game, int depth, int *best_move) {
  if (depth == 0 || game.turn == GAMEOVER) {
    return game.pits[6] - game.pits[13];
  }

  if (game.turn == ENGINE) {
    int best_score = -999;

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
    int best_score = 999;

    for (int i = 7; i <= 12; i++) {
      if (game.pits[i] == 0) continue;

      int score = search(MancalaGame_play(game, i), depth - 1, NULL);
      if (score < best_score) {
        best_score = score;
        if (best_move != NULL) *best_move = i;
      }
    }

    return best_score;
  }
}

int main() {
  printf("Is engine playing first? (y/n): ");

  char reply;
  scanf("%c", &reply);

  MancalaGame game = MancalaGame_create(reply == 'y' ? ENGINE : HUMAN);

  for (;;) {
    if (game.turn == GAMEOVER) {
      break;
    }

    if (game.turn == ENGINE) {
      int best_move;
      int eval = search(game, 9, &best_move);

      printf("Best move is %d (eval %d)\n", best_move, eval);

      game = MancalaGame_play(game, best_move);
      continue;
    }

    if (game.turn == HUMAN) {
      printf("\n");
      MancalaGame_print(game);

      printf("Human move: ");

      int human_move;
      scanf("%d", &human_move);

      game = MancalaGame_play(game, human_move);

      continue;
    }
  }

  MancalaGame_print(game);

  return 0;
}
