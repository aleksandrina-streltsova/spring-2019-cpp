#include "Board.h"
#include <utility>
#include <algorithm>

Board::Board(int board_size_, int row_size_) {
    board_size = board_size_;
    row_size = row_size_;
    filled_count = 0;
    last_cross = true;
    last_x = 0, last_y = 0;
    game_board = new board_field *[board_size];
    for (int i = 0; i < board_size; i++) {
        game_board[i] = new board_field[board_size];
        for (int j = 0; j < board_size; j++) {
            game_board[i][j] = EMPTY;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < board_size; i++) {
        delete[] game_board[i];
    }
    delete[] game_board;
}

int Board::get_board_size() const {
    return board_size;
}

board_field Board::get_field(int x, int y) const {
    return game_board[x][y];
}

int Board::count(int dx, int dy) const {
    int result = 0, x = last_x, y = last_y;
    while (x + dx < board_size && x + dx >= 0 && y + dy < board_size && y + dy >= 0) {
        if ((game_board[x + dx][y + dy] == CROSS && last_cross) ||
            (game_board[x + dx][y + dy] == NOUGHT && !last_cross)) {
            result++;
            x += dx;
            y += dy;
        } else {
            break;
        }
    }
    return result;
}

game_state_t Board::isWin() const {
    int max_row = 0;
    const int directions_count = 4;
    std::pair<int, int> dx_dy[directions_count] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (int i = 0; i < directions_count; i++) {
        max_row = std::max(max_row,
                count(dx_dy[i].first, dx_dy[i].second) + count(-dx_dy[i].first, -dx_dy[i].second) + 1);
    }
    if (max_row >= row_size) {
        if (last_cross) {
            return CROSS_WIN;
        } else {
            return NOUGHT_WIN;
        }
    }
    if (filled_count == board_size * board_size)
        return DRAW;
    return PLAY;
}

void Board::move(int x, int y, bool cross) {
    if (cross)
        game_board[x][y] = CROSS;
    else
        game_board[x][y] = NOUGHT;
    filled_count++;
    last_x = x;
    last_y = y;
    last_cross = cross;
}

bool Board::canMove(int x, int y) const {
    return !(x >= board_size || x < 0 || y >= board_size || y < 0 || game_board[x][y] != EMPTY);
}
