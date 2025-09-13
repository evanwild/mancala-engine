#include "mancala.h"
#include <stdlib.h>
#include <stdio.h>

MancalaGame MancalaGame_create(Turn initial_turn) {
  MancalaGame game;

  game.turn = initial_turn;
  game.cur_streak = 0;
  game.max_streak = 0;

  for (int i = 0; i < 14; i++) {
    game.pits[i] = i == 6 || i == 13 ? 0 : 4;
  }

  return game;
}

MancalaGame MancalaGame_play(MancalaGame game, int index) {
  if (game.turn == GAMEOVER) {
    printf("Error: tried to play a move but game is over\n");
    exit(1);
  }

  if (game.turn == ENGINE && (index < 0 || index > 5)) {
    printf("Error: tried to play index %d which is not an engine pit\n", index);
    exit(1);
  }

  if (game.turn == HUMAN && (index < 7 || index > 12)) {
    printf("Error: tried to play index %d which is not a human pit\n", index);
    exit(1);
  }

  // Pick up seeds out of pit
  int seeds = game.pits[index];
  game.pits[index] = 0;

  // Distribute around the board
  while (seeds > 0) {
    index++;
    if (index == 6 && game.turn != ENGINE) index++;
    if (index == 13 && game.turn != HUMAN) index++;
    index %= 14;

    seeds--;

    game.pits[index]++;
  }

  int facing_index = 12 - index;

  int do_steal = 
    ((game.turn == ENGINE && index >= 0 && index <= 5) ||
     (game.turn == HUMAN && index >= 7 && index <= 12)) &&
    (game.pits[index] == 1) &&
    (game.pits[facing_index] > 0);

  if (do_steal) {
    int store = game.turn == ENGINE ? 6 : 13;
    
    game.pits[store] += game.pits[index];
    game.pits[store] += game.pits[facing_index];
    
    game.pits[index] = 0;
    game.pits[facing_index] = 0;
  }

  // End the game if either player has no seeds on their side
  int engine_sum = 0;
  for (int i = 0; i <= 5; i++) {
    engine_sum += game.pits[i];
  }

  int human_sum = 0;
  for (int i = 7; i <= 12; i++) {
    human_sum += game.pits[i];
  }

  if (human_sum == 0) {
    for (int i = 0; i <= 5; i++) {
      game.pits[6] += game.pits[i];
      game.pits[i] = 0;
    }
    game.turn = GAMEOVER;
    return game;
  }

  if (engine_sum == 0) {
    for (int i = 7; i <= 12; i++) {
      game.pits[13] += game.pits[i];
      game.pits[i] = 0;
    }
    game.turn = GAMEOVER;
    return game;
  }

  // If you did not land in a pit, it's now the other players's turn
  if (index != 6 && index != 13) {
    game.turn = game.turn == HUMAN ? ENGINE : HUMAN;
    game.cur_streak = 0;
  }

  game.cur_streak++;
  if (game.cur_streak > game.max_streak) {
    game.max_streak = game.cur_streak;
  }

  return game;
}

void MancalaGame_print(MancalaGame game) {
  if (game.turn == ENGINE) {
    printf("Turn: ENGINE\n");
  } else if (game.turn == HUMAN) {
    printf("Turn: HUMAN\n");
  } else {
    printf("Turn: GAME OVER\n");
  }

  printf("  ");
  for (int i = 12; i >= 7; i--) {
    printf("%02d ", game.pits[i]);
  }
  printf("\n");

  printf("%02d                 %02d\n", game.pits[13], game.pits[6]);

  printf("  ");
  for (int i = 0; i <= 5; i++) {
    printf("%02d ", game.pits[i]);
  }
  printf("\n");
}
