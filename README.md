# Mancala Engine

The goal of this program is to compute strong moves in the strategy board game [Mancala](https://en.wikipedia.org/wiki/Mancala).

Although the game is relatively simple it's possible to execute strategies that last over a dozen turns (e.g. preparing a steal or finding a way to stall out the other player). I was curious to see how much better a computer could be than a human since it can reliably use these strategies.

## Usage

Requires a C compiler:

```sh
git clone https://github.com/evanwild/mancala-engine.git
cd mancala-engine
./run.sh
```

It will prompt you for whether the engine or the human should play first.
