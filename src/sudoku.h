#include <iostream>
#include <fstream>
#include <vector> 
#include <thread>    
#include <chrono>
#include <string>

class sudoku {
private:
    std::vector<std::vector<int>> sudokuBoard;
    
    bool isValidCol(int row, int number);

    bool isValidRow(int col, int number);

    bool isValidSubGrid(int row, int col, int number);

public:
    sudoku() : sudokuBoard(9, std::vector<int>(9, 0)) {}

    bool inputBoard();
    
    void printBoard();

    bool isValid(int row, int col, int number);

    bool solveWithBT(int row, int col, bool flag);
};