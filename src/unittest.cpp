#include <gtest/gtest.h>

#include "mancala.hpp"
#include "minimax.hpp"

TEST(GeneralTest, NextPit)
{
    EXPECT_EQ(next_pit_index(0, PlayerTurn::Engine), 1);
    EXPECT_EQ(next_pit_index(0, PlayerTurn::Human), 1);

    EXPECT_EQ(next_pit_index(5, PlayerTurn::Engine), 6);
    EXPECT_EQ(next_pit_index(5, PlayerTurn::Human), 7);

    EXPECT_EQ(next_pit_index(9, PlayerTurn::Engine), 10);
    EXPECT_EQ(next_pit_index(9, PlayerTurn::Human), 10);

    EXPECT_EQ(next_pit_index(12, PlayerTurn::Engine), 0);
    EXPECT_EQ(next_pit_index(12, PlayerTurn::Human), 13);
}

TEST(EngineTest, Steal)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 0;
    }
    board[1] = 3;
    board[8] = 80;

    bool go_again = make_move(board, 1);
    EXPECT_EQ(go_again, false);

    MancalaBoard expected = { 0, 0, 1, 1, 0, 0, 81, 0, 0, 0, 0, 0, 0, 0 };
    EXPECT_EQ(board, expected);
}

TEST(HumanTest, Steal)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 0;
    }
    board[1] = 50;
    board[9] = 2;

    bool go_again = make_move(board, 9);
    EXPECT_EQ(go_again, false);

    MancalaBoard expected = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 51 };
    EXPECT_EQ(board, expected);
}

TEST(EngineTest, BigLoopAround)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 0;
    }
    board[1] = 27;

    bool go_again = make_move(board, 1);
    EXPECT_EQ(go_again, false);

    MancalaBoard expected = { 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 };
    EXPECT_EQ(board, expected);
}

TEST(HumanTest, BigLoopAround)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 0;
    }
    board[11] = 33;

    bool go_again = make_move(board, 11);
    EXPECT_EQ(go_again, false);

    MancalaBoard expected = { 3, 3, 3, 3, 3, 2, 0, 2, 2, 2, 2, 2, 3, 3 };
    EXPECT_EQ(board, expected);
}

TEST(EngineTest, GoAgainChain)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 0;
    }
    board[0] = 6;
    board[2] = 3;
    board[4] = 1;

    bool go_again = make_move(board, 0);
    EXPECT_EQ(go_again, true);

    go_again = make_move(board, 5);
    EXPECT_EQ(go_again, true);

    go_again = make_move(board, 4);
    EXPECT_EQ(go_again, true);

    go_again = make_move(board, 5);
    EXPECT_EQ(go_again, true);

    go_again = make_move(board, 2);
    EXPECT_EQ(go_again, true);

    go_again = make_move(board, 5);
    EXPECT_EQ(go_again, true);

    go_again = make_move(board, 3);
    EXPECT_EQ(go_again, false);

    MancalaBoard expected = { 0, 1, 0, 0, 2, 1, 6, 0, 0, 0, 0, 0, 0, 0 };
    EXPECT_EQ(board, expected);
}

TEST(EngineTest, LoopAroundWithSteal)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 0;
    }
    board[2] = 13;
    board[10] = 50;

    bool go_again = make_move(board, 2);
    EXPECT_EQ(go_again, false);

    MancalaBoard expected = { 1, 1, 0, 1, 1, 1, 53, 1, 1, 1, 0, 1, 1, 0 };
    EXPECT_EQ(board, expected);
}

TEST(EngineTest, LoopAroundAndGoAgain)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 0;
    }
    board[3] = 16;

    bool go_again = make_move(board, 3);
    EXPECT_EQ(go_again, true);

    go_again = make_move(board, 5);
    EXPECT_EQ(go_again, false);

    MancalaBoard expected = { 1, 1, 1, 1, 2, 0, 3, 2, 1, 1, 1, 1, 1, 0 };
    EXPECT_EQ(board, expected);
}

TEST(GeneralTest, MinimaxDepthOne)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 4;
    }
    board[6] = 0;
    board[13] = 0;

    int best_move;
    auto eval = minimax(board, PlayerTurn::Engine, 1, &best_move);

    EXPECT_EQ(best_move, 5);
    EXPECT_EQ(eval, 1);
}

TEST(GeneralTest, MinimaxDepthTwo)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 4;
    }
    board[6] = 0;
    board[13] = 0;

    int best_move;
    auto eval = minimax(board, PlayerTurn::Engine, 2, &best_move);

    EXPECT_EQ(best_move, 2);
    EXPECT_EQ(eval, 2);

    bool go_again = make_move(board, best_move);
    EXPECT_EQ(go_again, true);
}

TEST(GeneralTest, MinimaxDepthThree)
{
    MancalaBoard board;
    for (int i = 0; i < 14; i++) {
        board[i] = 4;
    }
    board[6] = 0;
    board[13] = 0;

    int best_move;
    auto eval = minimax(board, PlayerTurn::Engine, 3, &best_move);

    EXPECT_EQ(best_move, 2);
    EXPECT_EQ(eval, 1);

    bool go_again = make_move(board, best_move);
    EXPECT_EQ(go_again, true);
}
