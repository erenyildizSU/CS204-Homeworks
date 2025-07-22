// Created by Eren on 14.05.2024

#ifndef HOMEWORK5_BOARD_H
#define HOMEWORK5_BOARD_H

class Board {

private:

    char** matrix;
    int size;
    int N;
    bool check1(const char &) const;
    bool full_check() const;

public:

    Board(int size, int N);
    ~Board();
    void print_board() const;
    bool put_piece(const char &, const int & );
    void turn_board_clockwise();
    char get_game_status() const;

};

#endif //HOMEWORK5_BOARD_H
