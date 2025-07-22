// HUSEYIN EREN YILDIZ, 31047,
// Homework 1

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool testFile(string &file) {

    ifstream readFile;
    string line;
    int firstLine=0, len=0;
    readFile.open(file);

    while(getline(readFile, line)) {
        for(int k=0; k<line.length(); k++){
            if (!((line[k] == 'l') || (line[k] == 'r') || (line[k] == 'u') || (line[k] == 'd') || (line[k] == '-'))){
                return false;
            }
        }

        if (firstLine == 0) {
            len = line.length();
            firstLine = len;
        }

        if (len != line.length()) {
            return false;
        }

        else if (line.empty()) {
            return false;
        }
    }
    return true;
}

bool IsMovingPossible(vector<vector<char>>& matrix) {
    for(int row=0; row < matrix.size(); row++){
        for(int column=0; column < matrix[row].size(); column++) {

            if(matrix[row][column] == 'r') {
                if(matrix[row][column+1] == '-' || ( (column+1) == matrix[row].size() )) {
                    return true;
                }
            }

            else if(matrix[row][column] == 'l') {
                if(matrix[row][column-1] == '-' || ( (column-1) == -1 )) {
                    return true;
                }
            }

            else if(matrix[row][column] == 'u') {
                if(matrix[row-1][column] == '-' || ( (row-1) == -1 )) {
                    return true;
                }
            }

            else if(matrix[row][column] == 'd') {
                if(matrix[row+1][column] == '-' || ( (row+1) == matrix.size() ) ) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool matrixEmpty (vector<vector<char>>& matrix) {
    for (int row=0; row < matrix.size(); row++){
        for (int column=0; column < matrix[0].size(); column++) {
            if (matrix[row][column] != '-') {
                return false;
            }
        }
    }
    return true;
}

void printMatrix( /* const */ vector<vector<char>> &matrix) {
    for (int row=0; row < matrix.size(); row++) {
        for (int column=0; column < matrix[0].size(); column++) {
            cout << matrix[row][column];
        }
        cout << endl;
    }
}

void moveInMatrix(vector<vector<char>> &matrix, int row, int column) {

    int counter=0;

    if ( ((matrix[row][column] == 'r') && (column == matrix[0].size()-1)) || ((matrix[row][column] == 'l') && (column == 0)) || ((matrix[row][column] == 'u') && (row == 0)) || ((matrix[row][column] == 'd') && (row == matrix.size()-1)) ) {
        matrix[row][column] = '-';
        cout << "Tile at " << "(" << row << "," << column << ")"<<" has been moved."<< endl;
    }

    else if (matrix[row][column] == 'r') {

        while (matrix[row][column+1] == '-') {
            matrix[row][column] = '-';
            column++;
            counter++;
        }

        if (matrix[row][column+1] != '-') {
            cout << "No tiles have been moved." << endl;
        }
        else {
            cout << "Tile at " << "(" << row << "," << (column - counter) << ")" << " has been moved." << endl;
        }

        if (matrix[row][column+1] != '-' && (column+1 != matrix[0].size())){  // && kısmı sonradan eklendi
            matrix[row][column] = 'r';
        }

//        else if (matrix[row][column+1] != '-') {
//            cout << "No tiles have been moved." << endl;
//        }
    }

    else if (matrix[row][column] == 'l') {

        while (matrix[row][column-1] == '-' ) {
            matrix[row][column] = '-';
            column--;
            counter++;
        }

        //cout << "Tile at " << "(" << row << "," << (column + counter) << ")"<<" has been moved."<< endl;

        if (matrix[row][column-1] != '-') {
            cout << "No tiles have been moved." << endl;
        }
        else {
            cout << "Tile at " << "(" << row << "," << (column + counter) << ")"<<" has been moved."<< endl;
        }

        if (matrix[row][column-1] != '-' && (column-1 != -1)){
            matrix[row][column] = 'l';
        }

//        else if (matrix[row][column-1] != '-') {
//            cout << "No tiles have been moved." << endl;
//        }
    }

    else if (matrix[row][column] == 'u') {
        cout << "Tile at " << "(" << row << "," << column << ")"<<" has been moved."<< endl;

        while (matrix[row-1][column] == '-') {
            matrix[row][column] = '-';
            row--;
            counter ++;
        }

        if (matrix[row][column] != '-') {
            cout << "No tiles have been moved." << endl;
        }
        else {
            cout << "Tile at " << "(" << (row + counter) << "," << column << ")" << " has been moved." << endl;
        }

        if (matrix[row-1][column] != '-' && (row-1 != -1 )){
            matrix[row][column] = 'u';
        }

//        else if (matrix[row][column] != '-') {
//            cout << "No tiles have been moved." << endl;
//        }
    }

    else if (matrix[row][column] == 'd') {
        cout << "Tile at " << "(" << row << "," << column << ")"<<" has been moved."<< endl;

        while (matrix[row+1][column] == '-') {
            matrix[row][column] = '-';
            row++;
            counter++;
        }

        if (matrix[row][column] != '-') {
            cout << "No tiles have been moved." << endl;
        }

        else {
            cout << "Tile at " << "(" << (row - counter) << "," << column << ")" << " has been moved." << endl;
        }

        if (matrix[row+1][column] != '-' && (row+1 != matrix.size())){
            matrix[row][column] = 'd';
        }

//        else if (matrix[row][column] != '-') {
//            cout << "No tiles have been moved." << endl;
//        }
    }

    else if (matrix[row][column] == '-'){
        cout << "No tiles have been moved." << endl;
    }
}

void create_matrix (ifstream &readFile, vector<vector<char>>& matrix ) {

    string row;
    vector <char> empty;

    while(getline(readFile,row)){
        for (unsigned int i=0; i < row.length(); i++){
            empty.push_back(row.at(i));
        }
        matrix.push_back(empty);
        empty.clear();
    }
}

int main() {

    ifstream readFile;
    //string row,column,fileName;
    string line, fileName;
    int row,column;
    vector <vector<char>> mat;

    cout << "Please enter the file name: " << endl;
    cin >> fileName;

    readFile.open(fileName);

    while(!readFile.is_open()) {    //değiştir
        cout << "Could not open the file. Please enter a valid file name:" << endl;
        cin >> fileName;
        readFile.open(fileName);
    }

    if(!testFile(fileName)) {
        cout << "Erroneous file content. Program terminates.";
        return 0;
    }

    cout << "The matrix file contains: " << endl;

    create_matrix(readFile,mat);
    printMatrix(mat);

    while(IsMovingPossible(mat)) {
        cout << "Please enter the row and column of the tile that you want to move:" << endl;
        cin >> row >> column;

        if ((row>-1 && row <mat.size()) && (column > -1 && column < mat[0].size())) {
            moveInMatrix(mat,row,column);
            printMatrix(mat);
        }
        else {
            cout << "Invalid row or column index."<< endl;
        }

    }

    if (matrixEmpty(mat)) {
        cout << "The matrix is empty.";
    }

    else if(!IsMovingPossible(mat)) {
        cout << "No more moves are possible.";
    }

    return 0;
}


//    if (!readFile.is_open()) {
//        do {
//            cout << "Could not open the file. Please enter a valid file name:" << endl;
//            cin >> fileName;
//            readFile.open(fileName);
//        } while (!readFile.is_open());
//    }


/*
#include<iostream>
#include<vector>

using namespace std;
int main()
{

    vector<vector<int>> matrix(3, vector<int>(5,1));

    for (int i =0; i < matrix.size(); i++){
        for(int k =0; k < matrix[0].size(); k++){
            cout << matrix [i][k];
        }
        cout << endl;
    }

    matrix [2][2] = 5;
    matrix [3][2] = 5;

    cout << endl;

    for (int i =0; i < matrix.size(); i++){
        for(int k =0; k < matrix[0].size(); k++){
            cout << matrix [i][k];
        }
        cout << endl;
    }

    return 0;
}
*/


/*
    while(getline(readFile,row)) {

        counter1 = row.length();
        counter2 = row.length();

        cout << counter1 << " ";
    }
*/