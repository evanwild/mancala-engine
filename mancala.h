#ifndef MANCALA_H
#define MANCALA_H

/*

    <------ HUMAN

  12 11 10 09 08 07
13                 06
  00 01 02 03 04 05

    ENGINE ----->

*/

typedef enum Turn {
  ENGINE,
  HUMAN,
  GAMEOVER
} Turn;

typedef struct MancalaGame {
  Turn turn;
  int turn_count;
  int pits[14];
} MancalaGame;

MancalaGame MancalaGame_create(Turn initial_turn);
MancalaGame MancalaGame_play(MancalaGame game, int index);
void MancalaGame_print(MancalaGame game);

#endif
