#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class sudoku {
private:
      std::vector<std::vector<int>> sudokuBoard;
public:
    sudoku() : sudokuBoard(9, std::vector<int>(9, 0)) {}

    bool inputBoard();
    
    void printBoard();
};