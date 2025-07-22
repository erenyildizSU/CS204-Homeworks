// Created by Eren on 14.05.2024.

#ifndef HOMEWORK5_PLAYER_H
#define HOMEWORK5_PLAYER_H

#include "Board.h"

class Player {

private:

    Board& board;
    char game_piece;

public:

    Player(Board&, char);
    bool put(int );
    void turn_board();
    bool is_winner() const;
    char get_symbol() const;

};


#endif //HOMEWORK5_PLAYER_H
