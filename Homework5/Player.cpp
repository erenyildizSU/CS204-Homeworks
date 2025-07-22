// Created by Eren on 14.05.2024.

#include "Player.h"
#include "Board.h"


Player::Player(Board & cons_board, char piece)
    : board(cons_board), game_piece(piece)
{}

bool Player::put(int col) {
    return board.put_piece(game_piece, col);
}

void Player::turn_board() {
    board.turn_board_clockwise();
}

bool Player::is_winner() const {
    if(board.get_game_status() == game_piece) {
        return true;
    }
    else{
        return false;
    }
}

char Player::get_symbol() const {
    return game_piece;
}
