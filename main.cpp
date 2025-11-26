#include "mancala.hpp"
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <unordered_map>

const int GOAL = 500;

std::unordered_map<uint64_t, int> cache;

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
    new_game.make_move(i);

    int upperbound = new_game.move_count + 11*new_game.seeds_left();

    int score;
    if (upperbound < GOAL) {
      score = 0;
    } else {
      uint64_t hash = new_game.hash();

      if (cache.count(hash)) {
        score = cache[hash];
      } else {
        score = search(new_game, nullptr);
        cache[hash] = score;
      }
    }
    
    if (score > best_score) {
      best_score = score;
      if (best_move != nullptr) *best_move = i;
    }

    if (new_game.move_count + score >= GOAL) {
      break;
    }
  }

  return best_score + 1;
}

int main() {
  MancalaGame game{PLAYER1};
  game.print();

  while (game.turn != GAMEOVER) {
    int best_move;
    int eval = search(game, &best_move);

    printf("Best move is %d (eval %d)\n\n", best_move, eval);

    game.make_move(best_move);
    game.print();
  }

  return 0;
}
