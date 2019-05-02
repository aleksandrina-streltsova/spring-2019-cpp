#include <iostream>
#include <cstring>
#include "BoardView.h"

int main(int argc, char * argv[]) {
    Board board;
    BoardView view(board);
    bool silent = false;
    if (argc == 2 && strcmp(argv[1], "silent") == 0) 
        silent = true;
    view.doGameCycle(silent);
    return 0;
}