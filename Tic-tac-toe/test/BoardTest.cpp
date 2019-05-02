#include "BoardTest.h"
#include "Board.h"

void BoardTest::testIsWin1() {
    Board board;
    board.move(0, 0, NOUGHT);
    board.move(0, 4, CROSS);
    board.move(1, 1, NOUGHT);
    board.move(1, 4, CROSS);
    board.move(2, 2, NOUGHT);
    board.move(2, 3, CROSS);
    board.move(7, 6, NOUGHT);
    board.move(2, 4, CROSS);
    board.move(7, 7, NOUGHT);
    board.move(2, 5, CROSS);
    board.move(3, 3, NOUGHT);
    board.move(3, 4, CROSS);
    board.move(8, 4, NOUGHT);
    board.move(4, 4, CROSS);
    DO_CHECK(board.isWin() == CROSS_WIN);
}

void BoardTest::testIsWin2() {
    Board board;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if ((i % 2 == 0 && (j % 4 == 0 || j % 4 == 1)) || (i % 2 == 1 && (j % 4 == 2 || j % 4 == 3)))
                board.move(i, j, CROSS);
            else
                board.move(i, j, NOUGHT);
        }
    }
    DO_CHECK(board.isWin() == DRAW);
}

void BoardTest::testIsWin3() {
    Board board;
    board.move(1, 0, NOUGHT);
    board.move(0, 0, CROSS);
    board.move(2, 2, NOUGHT);
    board.move(2, 3, CROSS);
    DO_CHECK(board.isWin() == PLAY);
}

void BoardTest::testMove1() {
    Board board;
    board.move(1, 0, NOUGHT);
    DO_CHECK(board.get_field(1, 0) == NOUGHT);
}

void BoardTest::testMove2() {
    Board board;
    board.move(2, 2, CROSS);
    DO_CHECK(board.get_field(2, 2) == CROSS);
}

void BoardTest::testMove3() {
    Board board;
    board.move(2, 3, EMPTY);
    DO_CHECK(board.get_field(2, 2));
}

void BoardTest::testCanMove1() {
    Board board;
    DO_CHECK(!board.canMove(10, 0));
}

void BoardTest::testCanMove2() {
    Board board;
    board.move(1, 4, CROSS);
    board.move(2, 2, NOUGHT);
    board.move(2, 3, CROSS);
    board.move(7, 6, NOUGHT);
    board.move(2, 4, CROSS);
    board.move(7, 7, NOUGHT);
    board.move(2, 5, CROSS);
    board.move(3, 3, NOUGHT);
    DO_CHECK(!board.canMove(7, 7));
}

void BoardTest::testCanMove3() {
    Board board;
    board.move(0, 0, NOUGHT);
    board.move(1, 1, CROSS);
    DO_CHECK(board.canMove(2, 3));
}

void BoardTest::runAllTests() {
    testIsWin1();
    testIsWin2();
    testIsWin3();
    testMove1();
    testMove2();
    testMove3();
    testCanMove1();
    testCanMove2();
    testCanMove3();
}



