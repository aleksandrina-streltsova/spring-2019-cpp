#include "BoardView.h"
#include <stdio.h>

BoardView::BoardView(Board &board_) {
    board = &board_;
}

void BoardView::showBoard() {
    for (int i = 0; i < board->get_board_size(); i++) {
        for (int j = 0; j < board->get_board_size(); j++) {
            if (board->get_field(i, j) == EMPTY)
                printf(".");
            else if (board->get_field(i, j) == CROSS)
                printf("X");
            else
                printf("O");
        }
        printf("\n");
    }
}

void BoardView::doGameCycle(bool silent) {
    bool cross = false, right_move = true;
    while(true) {
        if (right_move && !silent)
            showBoard();
        if (board->isWin() == PLAY) {
            if (!cross) {
                printf("O move: ");
            } else {
                printf("X move: ");
            }
        }
        else {
            if (silent)
                showBoard();
            if (board->isWin() == CROSS_WIN) {
                printf("X wins!");
                break;
            } else if (board->isWin() == NOUGHT_WIN) {
                printf("O wins!");
                break;
            } else {
                printf("Draw.");
                break;
            }
        }
        int x = 0, y = 0;
        scanf("%d%d", &x, &y);
        if(x == -1 && y == -1) {
            break;
        } else if (board->canMove(x, y)) {
            board->move(x, y, cross);
            cross = !cross;
            right_move = true;
            printf("\n");
        } else {
            right_move = false;
            printf("Bad move!\n");
        }
    }
}

