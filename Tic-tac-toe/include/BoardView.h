#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "Board.h"

class BoardView {
public:
    BoardView(Board &board);
    void showBoard();
    void doGameCycle(bool silent);

private:
    Board* board;
};

#endif
