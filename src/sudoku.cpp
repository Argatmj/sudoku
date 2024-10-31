#include "sudoku.h"

bool sudoku::inputBoard(){
    std::ifstream boardText("src/board.txt");

    if(!boardText.is_open()){
        std::cerr << "Board text failed to open!";
        return false;
    }

    std::string line;
    int counter {0};

    while(std::getline(boardText,line)){
        for(int i = 0; i < 9; i++){
            sudokuBoard[counter][i] = line[i] - '0';
        }
        counter++;
    }

    return true;
}

void sudoku::printBoard() {
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0) {
            std::cout << "------+-------+------" << std::endl;
        }
        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0 && col != 0) {
                std::cout << " |";
            }
            std::cout << " " << sudokuBoard[row][col];
        }
        std::cout << std::endl;
    }
}
