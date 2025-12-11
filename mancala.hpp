#ifndef MANCALA_HPP
#define MANCALA_HPP

#include <cassert>
#include <cstdio>
#include <cstdint>
#include <cstring>

/*

  <-------- PLAYER2

  12 11 10 09 08 07
13                 06
  00 01 02 03 04 05

  PLAYER1 ------->

*/

enum Turn {
  PLAYER1,
  PLAYER2,
  GAMEOVER
};

const int PLAYER1_STORE = 6;
const int PLAYER2_STORE = 13;

const int zeros[6] = {0, 0, 0, 0, 0, 0};

struct MancalaGame {
  Turn turn;
  int move_count;
  int pits[14];

  MancalaGame(Turn initial_turn) : turn{initial_turn}, move_count{0} {
    for (int i = 0; i < 14; i++) {
      pits[i] = 4;
    }
    pits[PLAYER1_STORE] = 0;
    pits[PLAYER2_STORE] = 0;
  }

  MancalaGame(const MancalaGame &other) {
    turn = other.turn;
    move_count = other.move_count;
    memcpy(pits, other.pits, sizeof(pits));
  }

  void make_move(int index) {
    assert(turn != GAMEOVER);
    if (turn == PLAYER1) assert(index >= 0 && index <= 5);
    if (turn == PLAYER2) assert(index >= 7 && index <= 12);
    assert(pits[index] > 0);

    ++move_count;

    int seeds = pits[index];
    pits[index] = 0;
    
    while (seeds > 0) {
      ++index;
      if (turn == PLAYER1 && index == PLAYER2_STORE) ++index;
      if (turn == PLAYER2 && index == PLAYER1_STORE) ++index;
      index %= 14;

      ++pits[index];
      --seeds;
    }

    int facing_index = 12 - index;

    bool do_steal = 
      ((turn == PLAYER1 && index >= 0 && index <= 5) ||
       (turn == PLAYER2 && index >= 7 && index <= 12)) &&
      (pits[index] == 1) &&
      (pits[facing_index] > 0);

    if (do_steal) {
      int store = turn == PLAYER1 ? PLAYER1_STORE : PLAYER2_STORE;
      
      pits[store] += pits[index];
      pits[store] += pits[facing_index];

      pits[index] = 0;
      pits[facing_index] = 0;
    }

    if (memcmp(pits, zeros, sizeof(zeros)) == 0) {
      for (int i = 7; i <= 12; i++) {
        pits[PLAYER2_STORE] += pits[i];
        pits[i] = 0;
      }
      turn = GAMEOVER;
      return;
    }

    if (memcmp(pits+7, zeros, sizeof(zeros)) == 0) {
      for (int i = 0; i <= 5; i++) {
        pits[PLAYER1_STORE] += pits[i];
        pits[i] = 0;
      }
      turn = GAMEOVER;
      return;
    }

    if (index != PLAYER1_STORE && index != PLAYER2_STORE) {
      turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;
    }
  }

  uint64_t hash() const {
    uint64_t result = 0;

    auto encode_pit = [&](int i) {
      result |= 1;
      result <<= pits[i] + 1;
    };

    if (turn == PLAYER1) {
      for (int i = 0; i < 6; i++) encode_pit(i);
      for (int i = 7; i < 13; i++) encode_pit(i);
    } else if (turn == PLAYER2) {
      for (int i = 7; i < 13; i++) encode_pit(i);
      for (int i = 0; i < 6; i++) encode_pit(i);
    }

    return result;
  }

  int seeds_left() const {
    return 48 - pits[PLAYER1_STORE] - pits[PLAYER2_STORE];
  }

  void print() {
    if (turn == PLAYER1) printf("PLAYER 1\n");
    if (turn == PLAYER2) printf("PLAYER 2\n");
    if (turn == GAMEOVER) printf("GAME OVER\n");

    printf("  ");
    for (int i = 12; i >= 7; i--) {
      printf("%02d ", pits[i]);
    }
    printf("\n");

    printf("%02d                 %02d\n", pits[13], pits[6]);

    printf("  ");
    for (int i = 0; i <= 5; i++) {
      printf("%02d ", pits[i]);
    }
    printf("\n"); 
  }
};

#endif
