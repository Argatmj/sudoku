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
            std::cout << "-------+-------+------" << std::endl;
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

bool sudoku::isValidCol(int row, int number){
    for(int c = 0; c < 9; c++){
        if(sudokuBoard[row][c] == number) return false;
    }
    return true;
}

bool sudoku::isValidRow(int col, int number){
    for(int r = 0; r < 9; r++){
        if(sudokuBoard[r][col] == number) return false;
    }
    return true;
}

bool sudoku::isValidSubGrid(int startRow, int startCol, int number){
    for (int r = startRow; r < startRow + 3; r++) {
        for (int c = startCol; c < startCol + 3; c++) {
            if (sudokuBoard[r][c] == number) return false;
        }
    }
    return true;
}

bool sudoku::isValid(int row, int col, int number){
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);
    
    return isValidRow(col,number) && isValidCol(row,number) && isValidSubGrid(startRow,startCol,number);
}

bool sudoku::solveWithBT(int row, int col, bool flag){
    if (row == 9) {
        return true; 
    }
   
    if (col == 9) {
        return solveWithBT(row + 1, 0, flag); 
    }
    
    if (sudokuBoard[row][col] != 0) {
        return solveWithBT(row, col + 1, flag); 
    }

    for (int num = 1; num <= 9; num++) {
        if (this->isValid(row, col, num)) {
            sudokuBoard[row][col] = num; 
            if (solveWithBT(row, col + 1, flag)) {
                return true; 
            }
            sudokuBoard[row][col] = 0; 
        }
        if(flag){
            printBoard();
            std::cout << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    return false; 
}

void sudoku::clearBoard(){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            sudokuBoard[row][col] = 0;
        }
    }
}
