#!/bin/bash
set -e

gcc -Wall -O2 main.c mancala.c

./a.out
