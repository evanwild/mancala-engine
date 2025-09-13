# Mancala Engine

The goal of this program is to compute strong moves in the strategy board game [Mancala](https://en.wikipedia.org/wiki/Mancala).

Although the game is relatively simple it's possible to execute strategies that last over a dozen turns (e.g. preparing a steal or finding a way to stall out the other player). I was curious to see how much better a computer could be than a human since it can reliably use these strategies.

## Longest Move Streak

Another interesting thing you can do is get two engines to cooperate on a goal, for example playing the longest game or shortest game. I recently reworked it so two engines try to achieve the longest move streak, and it found one that is 20 moves long:

https://github.com/user-attachments/assets/976bb4ba-c8e7-4aa4-bdd5-6e2bec170260

## Usage

Requires a C compiler:

```sh
git clone https://github.com/evanwild/mancala-engine.git
cd mancala-engine
./run.sh
```

Currently it's set up to find the longest move streak, so it will play two cooperating engines against each other.
