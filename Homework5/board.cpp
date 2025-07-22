// Huseyin Eren YILDIZ, 31047
// Homework 5

/******************************************************************************
Purpose: In this homework, I implement a simple board game using the object sharing concept of C++
Author: HUSEYIN EREN YILDIZ - 31047
Date: 14/05/2024
******************************************************************************/


#include "Board.h"
#include <iostream>

using namespace std;

Board::Board(int size, int N) : size(size), N(N) {
// constructor, dynamically create the matrix with the given size and initialize it by assigning '-' character to every cell

/* Start: I took these code part from CS204 - 2.2-pointer-linkedlists page.28 and I updated it   */
    // Memory allocation for dynamic matrix
    matrix = new char *[size];

    for (int i=0; i < size; i++){
        matrix[i] = new char[size];  // For each row, we have columns in 'size' number
/* End: I took these code part from CS204 - 2.2-pointer-linkedlists page.28 and I updated it */
        for (int j=0; j < size; j++) {
            matrix[i][j]='-';
        }
    }
}


Board::~Board() {  // Destructor of the Board Class

    for(int i=0; i<size; i++) {  // returning memory to free heap for reuse
        delete [] matrix[i];   // delete each row individually
    }

    // After removing all the rows, delete the pointer array as well
    delete [] matrix;
}


void Board::print_board() const {
// It displays the current state of the board.
    cout << endl;

    for(int row=0; row<size; row++) {  // Loop through each row of the matrix
        for (int col=0; col<size; col++) {  // Loop through each column of the matrix
            cout << matrix[row][col];  // display the value of the current cell
        }
        cout << endl;  // After each row, move to the next line
    }
    cout << endl;
}

bool Board::put_piece (const char & ch, const int & col) {
// This function takes char and int as parameters
// It basically adds a game piece on the board

    if (col < size) {  // check if the column index is within the valid range

        if (matrix[0][col] == '-') {  // check whether the uppermost cell in the given column is empty
            matrix[0][col] = ch;  // Insert the piece into the top of the column

            // Apply gravity to the entire board to let all pieces fall to the lowest possible position
            for (int column = 0; column < size; column++) {  // iterate over all columns
                for (int row = size - 1; row > 0; row--) {   // from bottom to top within each column
                    for (int check = 0; check < row; check++) {  // check each cell above the current bottom cell
                        if (matrix[check][column] != '-' && matrix[check + 1][column] == '-') {  //  If the cell above is filled and the cell below is empty

                            matrix[check + 1][column] = matrix[check][column];   // Move object one bottom
                            matrix[check][column] = '-';   // put '-' previous cell
                        }
                    }
                }
            }
            return true;  //  return true if the piece is successfully dropped through the column of the board
        }
    }
    return false;  // if the piece is not successfully dropped through the column of the board
}

void Board::turn_board_clockwise() {
// This function will rotate the board 90 degrees clockwise
// After the rotation, the game pieces will automatically drop down as if there is gravity.

    // creat a matrix to hold clockwise board
    char ** new_mat = new char * [size];

    for (int i = 0; i < size; i++) {
        new_mat[i] = new char[size];
    }

    for (int k = 0; k < size; k++) {
        for (int l = 0; l < size; l++) {
            new_mat[l][size - 1 - k] = matrix[k][l];
        }
    }

/* Start: I took these code part from CS204 - 2.2-pointer-linkedlists page.28 and I updated it   */
    // Deallocate the old matrix
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
/* End: I took these code part from CS204 - 2.2-pointer-linkedlists page.28 and I updated it   */

    // gravity process
    matrix = new_mat;

    // Apply gravity to the entire board to let all pieces fall to the lowest possible position
    for (int column = 0; column < size; column++) {  // iterate over all columns
        for (int row = size - 1; row > 0; row--) {   // from bottom to top within each column
            for (int check = 0; check < row; check++) {  // check each cell above the current bottom cell
                if (matrix[check][column] != '-' && matrix[check + 1][column] == '-') {  //  If the cell above is filled and the cell below is empty

                    matrix[check + 1][column] = matrix[check][column];   // Move object one bottom
                    matrix[check][column] = '-';   // put '-' previous cell
                }
            }
        }
    }
}

char Board::get_game_status() const {
// check whether the game is over or not, and also it checks the winner, if any

    if (check1('X')) {       // Check for winner 'X'
        if(check1('O')) {    // Check for winner 'O'
            return 'D';          // If both players win at the same time, then return 'D'
        }
        else {                   // If only winner is 'X'
            return 'X';
        }
    }

    else {                        // If 'X' is not winner
        if(check1('O')) {    // If 'X' is not winner and 'O' is winner
            return 'O';          // return 'O'

        }
        else if (full_check()) {  // All of the cells are full, but no one has won
            return 'D';           // return 'D'
        }

        else{                     // If the game is not over, then this function returns dash '-'
            return '-';
        }
    }
}


bool Board::check1(const char & ch) const {
// This function takes char as a parameter
// It searches for N consecutive pieces (ch) in multiple directions: horizontally (left and right), vertically (up and down), and diagonally (up-left, up-right, down-left, and down-right)
// from every position on the board that contains the piece character ch.

    // loop through every cell in the matrix
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if(matrix[r][c] == ch){  // only check from cells that contain the character 'ch'

                // check horizontally to the left
                int row = r;
                int col = c;
                int count = N - 1; // we should look for N-1 pieces since the first one is 'ch'

                while( col-1 > -1 && matrix[row][col-1] == ch) {
                    count--;  // decrease count for every matching piece found
                    col--;    // move left
                }
                if (count == 0) {  // If the required number of pieces are met to win
                    return true;
                }

                // check horizontally to the right
                // reset variables again for each direction
                row = r;
                col = c;
                count = N - 1;

                while(col + 1 < size && matrix[row][col + 1] == ch) {
                    count--;  // decrease count for every matching piece found
                    col++;    // move right
                }
                if (count == 0) {  // If the required number of pieces are met to win
                    return true;
                }

                // check vertically upwards
                // reset variables again for each direction
                row = r;
                col = c;
                count = N - 1;

                while(row - 1 >= 0 && matrix[row - 1][col] == ch) {
                    count--;  // decrease count for every matching piece found
                    row--;    // move up
                }
                if (count == 0) {  // If the required number of pieces are met to win
                    return true;
                }

                // check for downwards
                // reset variables again for each direction
                row = r;
                col = c;
                count = N - 1;

                while(row + 1 < size && matrix[row + 1][col] == ch) {
                    count--;  // decrease count for every matching piece found
                    row++;    // move down
                }
                if (count == 0) {    // If the required number of pieces are met to win
                    return true;
                }

                // check diagonally down-right
                // reset variables again for each direction
                row = r;
                col = c;
                count = N - 1;

                while(row + 1 < size && col + 1 < size && matrix[row + 1][col + 1] == ch) {
                    count--;   // decrease count for every matching piece found
                    row++;     // move down
                    col++;     // move right
                }
                if (count == 0) {    // If the required number of pieces are met to win
                    return true;
                }

                // check diagonally down-left
                // reset variables again for each direction
                row = r;
                col = c;
                count = N - 1;

                while(row + 1 < size && col - 1 >= 0 && matrix[row + 1][col - 1] == ch) {
                    count--;    // decrease count for every matching piece found
                    row++;      // move down
                    col--;      // move left
                }
                if (count == 0) {    // If the required number of pieces are met to win
                    return true;
                }

                // check diagonally up-left
                // reset variables again for each direction
                row = r;
                col = c;
                count = N - 1;

                while(row - 1 >= 0 && col - 1 >= 0 && matrix[row - 1][col - 1] == ch) {
                    count--;    // decrease count for every matching piece found
                    row--;      // move up
                    col--;      // move left
                }
                if (count == 0) {     // If the required number of pieces are met to win
                    return true;
                }

                // check diagonally up-right
                // reset variables again for each direction
                row = r;
                col = c;
                count = N - 1;

                while(row - 1 >= 0 && col + 1 < size && matrix[row - 1][col + 1] == ch) {
                    count--;    // decrease count for every matching piece found
                    row--;      // move up
                    col++;      // move right
                }
                if (count == 0) {     // If the required number of pieces are met to win
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::full_check() const {
// This function does not take parameters
// It checks if the board is full. If there is an empty cell, it will return false. Otherwise, it will return true

    for(int r=0; r < size; r++) {   // loop through each row of the matrix
        for(int c=0; c < size; c++) {   // loop for each column of the matrix
            if(matrix[r][c] == '-'){  // check if the current cell is empty. If '-' is found, the board is not full
                return false;   // return false, because at least one cell is empty
            }
        }
    }
    return true;    // If no empty cells are found after checking the entire board, then return true
}
