#ifndef BOARD_H
#define BOARD_H

enum game_state_t {NOUGHT_WIN, CROSS_WIN, DRAW, PLAY};
enum board_field {NOUGHT, EMPTY, CROSS};

class Board {
public:
    Board(int board_size = 10, int row_size = 5);
    ~Board();
    void move(int x, int y, bool cross);
    bool canMove(int x, int y) const;
    game_state_t isWin() const;
    board_field get_field(int x, int y) const;
    int get_board_size() const;
    int count(int dx, int dy) const;

private:
    board_field** game_board;
    int board_size, row_size;
    int last_x, last_y;
    bool last_cross;
    int filled_count;
};

#endif
