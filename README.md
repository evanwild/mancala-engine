# Mancala Engine

## Overview

This program was created for the purpose of finding strong moves in the strategy board game [Mancala](https://en.wikipedia.org/wiki/Mancala).

It uses the minimax algorithm with alpha-beta pruning to search the tree of possible game states up to a certain depth (default 20) and return the best move along with an evaluation number. When this number is positive the engine is winning, and when it is negative the human player is winning.

## Build Instructions

Make sure you have CMake and a C++ Compiler installed.

```sh
cd mancala-engine
mkdir build
cd build
cmake ..
cmake --build .
./MancalaEngine
```

## Testing

This project uses the [GoogleTest](https://github.com/google/googletest) framework. After following the build commands above, you can simply run
```sh
ctest
```
while in the build directory.


## Example Output

A snippet from a game against the engine.

```
Engine plays 2 (eval = 19)
-----------------------
|  00 06 00 09 01 00  |
|03                 19|
|  00 07 00 01 01 01  |
-----------------------
Human move (0-5): 1
Engine plays 5 (eval = 21)
Engine plays 4 (eval = 21)
-----------------------
|  01 00 00 09 01 00  |
|04                 20|
|  01 08 01 02 00 01  |
-----------------------
Human move (0-5): 0
-----------------------
|  00 00 00 09 01 00  |
|05                 20|
|  01 08 01 02 00 01  |
-----------------------
Human move (0-5): 3
Engine plays 5 (eval = 20)
Engine plays 3 (eval = 20)
Engine plays 5 (eval = 20)
Engine plays 4 (eval = 19)
Engine plays 5 (eval = 18)
Engine plays 2 (eval = 18)
-----------------------
|  01 01 01 00 00 00  |
|06                 27|
|  02 09 00 01 00 00  |
-----------------------

...
```
